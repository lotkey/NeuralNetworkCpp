#include <cassert>
#include <cstdarg>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>
#include "Activation.h"
#include "Loss.h"
#include "NeuralNetwork.h"
#include "Synapse.h"
#include "VectorFunctions.h"
#include "VectorMath.h"

// Create a network from a topology of the layers
NeuralNetwork::NeuralNetwork(const std::vector<unsigned>& topology) {
	this->topology = topology;
	inputSize = topology.front();
	outputSize = topology.back();
	for (unsigned i = 0; i < topology.size() - 1; i++) {
		synapses.push_back(Synapse(topology[i], topology[i + 1]));
	}
	activationFunction = Activation::Function::SIGMOID;
	lossFunction = Loss::Function::MEANSQUAREDERROR;
}

NeuralNetwork::NeuralNetwork(unsigned numLayers, ...) {
	va_list ap;
	va_start(ap, numLayers);
	for (unsigned j = 0; j < numLayers; j++) {
		topology.push_back(va_arg(ap, unsigned));
	}
	va_end(ap);

	inputSize = topology.front();
	outputSize = topology.back();
	for (unsigned i = 0; i < topology.size() - 1; i++) {
		synapses.push_back(Synapse(topology[i], topology[i + 1]));
	}
	activationFunction = Activation::Function::SIGMOID;
	lossFunction = Loss::Function::MEANSQUAREDERROR;
}

NeuralNetwork::NeuralNetwork(const Activation::Function& a, const Loss::Function& l, const std::vector<unsigned>& topology) {
	this->topology = topology;
	inputSize = topology.front();
	outputSize = topology.back();
	for (unsigned i = 0; i < topology.size() - 1; i++) {
		synapses.push_back(Synapse(topology[i], topology[i + 1]));
	}
	activationFunction = a;
	lossFunction = l;
}

NeuralNetwork::NeuralNetwork(const Activation::Function& a, const Loss::Function& l, unsigned numLayers, ...) {
	va_list ap;
	va_start(ap, numLayers);
	for (unsigned j = 0; j < numLayers; j++) {
		topology.push_back(va_arg(ap, unsigned));
	}
	va_end(ap);

	inputSize = topology.front();
	outputSize = topology.back();
	for (unsigned i = 0; i < topology.size() - 1; i++) {
		synapses.push_back(Synapse(topology[i], topology[i + 1]));
	}
	activationFunction = a;
	lossFunction = l;
}

NeuralNetwork::NeuralNetwork(const std::string& filename) {
	std::vector<unsigned> topo;
	std::vector<std::vector<std::vector<double>>> w;

	std::ifstream infile;
	std::string line = "";
	infile.open(filename);

	int a, l;
	infile >> a;
	infile >> l;
	activationFunction = static_cast<Activation::Function>(a);
	lossFunction = static_cast<Loss::Function>(l);

	while (line.empty()) std::getline(infile, line);
	while (!line.empty()) {
		unsigned i;
		unsigned index;
		if (line.find_first_of(" ") != std::string::npos) {
			index = line.find_first_of(" ");
			i = std::stoi(line.substr(0, index));
			line = line.substr(index + 1, line.length() - index - 1);
		}
		else {
			i = std::stoi(line);
			line = "";
		}
		topo.push_back(i);
	}

	for (unsigned i = 0; i < topo.size() - 1; i++) {
		w.push_back(std::vector<std::vector<double>>());
		for (unsigned j = 0; j < topo[i] + 1; j++) {
			w[i].push_back(std::vector<double>());
			for (unsigned k = 0; k < topo[i + 1]; k++) {
				double d;
				infile >> d;
				w[i][j].push_back(d);
			}
		}
	}

	topology = topo;
	inputSize = topology.front();
	outputSize = topology.back();
	for (std::vector<std::vector<double>> v : w) {
		synapses.push_back(Synapse(v));
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
				correctWeights(learningRate);
				// Reset the averages
				predictionAverage = std::vector<double>(outputSize);
				answerAverage = std::vector<double>(outputSize);
			}
		}
		// Update progress bar
		while ((int)(e * barSize / epochs) > barCounter) {
			std::cout << (char)(219);
			barCounter++;
		}
	}

	// Finish progress bar
	while (barCounter < barSize) {
		std::cout << (char)219;
		barCounter++;
	}

	// Print status
	std::cout << "\n\nFinished training.\n";
}

// Propagate the loss backwards
void NeuralNetwork::backPropagate(const std::vector<double>& observed, const std::vector<double>& actual) {
	std::vector<double> error = synapses.back().propagateError(observed, actual, activationFunction, lossFunction);
	for (int i = (int)synapses.size() - 2; i >= 0; i--) {
		error = synapses[i].propagateError(error, activationFunction);
	}
}

// Correct the weights in each synapse
void NeuralNetwork::correctWeights(const double& learningRate) {
	for (unsigned i = 0; i < synapses.size(); i++) {
		synapses[i].correctWeights(learningRate);
	}
}

// Test the loss of the network with provided data
double NeuralNetwork::test(const std::vector<std::vector<double>>& features, const std::vector<std::vector<double>>& labels) {
	assert(features.size() == labels.size());
	double loss = 0.0;
	for (unsigned i = 0; i < features.size(); i++) {
		std::vector<double> lossVector = Loss::f(predict(features[i]), labels[i], lossFunction);
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

// Make a prediction with provided input
std::vector<double> NeuralNetwork::predict(const std::vector<double>& input) {
	assert(input.size() == inputSize);
	std::vector<double> output = input;
	for (unsigned i = 0; i < synapses.size(); i++) {
		output = synapses[i].activate(output, activationFunction);
	}
	return output;
}

// Take in features and export predictions to an output file
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

void NeuralNetwork::save(const std::string& filename) const {
	std::ofstream outfile;
	outfile.open(filename);

	outfile << (int)activationFunction << " " << (int)lossFunction << "\n\n";

	for (unsigned u : topology) {
		outfile << u << " ";
	}
	outfile << "\n";
	for (unsigned i = 0; i < synapses.size(); i++) {
		outfile << synapses[i].toString() << "\n";
	}
	outfile.close();
}

void NeuralNetwork::setWeights(const unsigned& startLayer, const std::vector<std::vector<double>>& weights) {
	synapses[startLayer].setWeights(weights);
}

void NeuralNetwork::setWeights(const std::vector<std::vector<std::vector<double>>>& weights) {
	assert(weights.size() == synapses.size());
	for (unsigned i = 0; i < synapses.size(); i++) {
		synapses[i].setWeights(weights[i]);
	}
}