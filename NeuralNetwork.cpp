#include <cassert>
#include <fstream>
#include <iostream>
#include <random>
#include <tuple>
#include <vector>
#include "Loss.h"
#include "NeuralNetwork.h"
#include "Synapse.h"
#include "VectorMath.h"

// Create a network from a topology of the layers
NeuralNetwork::NeuralNetwork(const std::vector<unsigned>& topology) {
	inputSize = topology[0];
	outputSize = topology.back();
	for (unsigned i = 0; i < topology.size() - 1; i++) {
		synapses.push_back(Synapse(topology[i], topology[i + 1]));
	}
}

// Print each synapse
void NeuralNetwork::print() {
	for (unsigned i = 0; i < synapses.size(); i++) {
		synapses[i].print();
		std::cout << "\n";
	}
}

// Train with provided data, learning rate, number of epochs, and batch size
void NeuralNetwork::train(const std::vector<std::vector<double>>& features, const std::vector<std::vector<double>>& labels, const double& learningRate, const unsigned& epochs, const unsigned& batchSize) {
	assert(features.size() == labels.size());
	// Vector to store prediction
	std::vector<double> prediction;
	// Average of the predictions over the entire batch
	std::vector<double> predictionAverage = std::vector<double>(outputSize);
	// Average of the correct answers over the entire batch
	std::vector<double> answerAverage = std::vector<double>(outputSize);
	// Size of the loading bar in number of characters
	unsigned barSize = 50;
	// Counter for printing the loading bar
	unsigned barCounter = 0;
	// Counter for batch size
	unsigned batchCounter = 0;

	// Print status
	std::cout << "Training...\n";
	// Print bar size indicator
	for (unsigned i = 0; i < barSize; i++) std::cout << "_";
	std::cout << "\n";
	// Loop over each epoch
	for (unsigned e = 0; e < epochs; e++) {
		// Loop over the data once per epoch
		for (unsigned i = 0; i < features.size(); i++) {
			assert(features[i].size() == inputSize);
			assert(labels[i].size() == outputSize);
			// Gather prediction from features
			std::vector<double> prediction = predict(features[i]);
			// Add prediction to the average (currently just a sum, will divide later)
			VectorMath::operator+=(predictionAverage, prediction);
			// Add answer to the average (currently just a sum, will divide later)
			VectorMath::operator+=(answerAverage, labels[i]);
			// If the end of the batch has been reached...
			if (batchCounter++ % batchSize == 0) {
				// Divide the sums into averages
				VectorMath::operator/=(predictionAverage, (double)batchSize);
				VectorMath::operator/=(answerAverage, (double)batchSize);
				// Propagate loss backwards
				backPropagate(predictionAverage, answerAverage);
				updateWeights(learningRate);
				// Reset the averages
				predictionAverage = std::vector<double>(outputSize);
				answerAverage = std::vector<double>(outputSize);
			}
		}
		// Update progress bar
		if ((int)(e * barSize / epochs) > barCounter) {
			std::cout << (char)(219);
			barCounter++;
		}
	}
	// Print status
	std::cout << (char)(219) << "\n\nFinished training.\n";
}

// Propagate the loss backwards and update the synapses accordingly
void NeuralNetwork::backPropagate(const std::vector<double>& observed, const std::vector<double>& actual) {
	/*std::vector<double> error = synapses.back().correctWeights(observed, actual, learningRate);
	for (int i = (unsigned)synapses.size() - 2; i >= 0; i--) {
		error = synapses[i].correctWeights(error, learningRate);
	}*/
	std::vector<double> error = synapses.back().propagateError(observed, actual);
	for (int i = (int)synapses.size() - 2; i >= 0; i--) {
		error = synapses[i].propagateError(error);
	}
}

void NeuralNetwork::updateWeights(const double& learningRate) {
	for (Synapse s : synapses) {
		s.correctWeights(learningRate);
	}
}

// Test the loss of the network with provided data
double NeuralNetwork::test(const std::vector<std::vector<double>>& features, const std::vector<std::vector<double>>& labels) {
	assert(features.size() == labels.size());
	double loss = 0.0;
	for (unsigned i = 0; i < features.size(); i++) {
		std::vector<double> lossVector = Loss::meanSquaredError(predict(features[i]), labels[i]);
		for (double d : lossVector) {
			loss += d;
		}
	}
	loss /= features.size();
	return loss;
}

// Test the network with provided data and one-hot encoded output
double NeuralNetwork::testDiscrete(const std::vector<std::vector<double>>& features, const std::vector<std::vector<double>>& labels) {
	std::vector<double> prediction;
	int guess, answer;
	int correct = 0;
	for (unsigned i = 0; i < features.size(); i++) {
		prediction = predict(features[i]);
		guess = std::max_element(prediction.begin(), prediction.end()) - prediction.begin();
		answer = std::max_element(labels[i].begin(), labels[i].end()) - labels[i].begin();
		if (guess == answer) correct++;
	}
	return (double)correct / (double)features.size();
}

// Make a prediction based on input
std::vector<double> NeuralNetwork::predict(const std::vector<double>& input) {
	assert(input.size() == inputSize);
	std::vector<double> output = input;
	for (unsigned i = 0; i < synapses.size(); i++) {
		output = synapses[i].activate(output);
	}
	return output;
}

void NeuralNetwork::exportOutput(const std::vector<std::vector<double>>& features, const std::string& filename) {
	std::ofstream outfile;
	outfile.open(filename);
	std::vector<double> output;
	for (std::vector<double> v : features) {
		output = predict(v);
		for (double d : output) {
			outfile << d << " ";
		}
		outfile << "\n";
	}
	outfile.close();
}