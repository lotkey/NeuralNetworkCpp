#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include "Activation.h"
#include "Loss.h"
#include "Synapse.h"
#include "VectorMath.h"

// Construct a synapse from a starting layer and end layer size
Synapse::Synapse(const unsigned& startLayer, const unsigned& endLayer) {
	startLayerSize = startLayer + 1;
	endLayerSize = endLayer;

	for (unsigned i = 0; i <= startLayer; i++) {
		weights.push_back(std::vector<double>());
		for (unsigned j = 0; j < endLayer; j++) {
			// Initialize the weights to random doubles between -1 and 1
			weights.back().push_back(((double)rand() / (double)RAND_MAX) * 2.0 - 1.0);
		}
	}
}

// Print the synapse's weights (including bias)
void Synapse::print() const {
	for (unsigned i = 0; i < weights.size(); i++) {
		if (i == weights.size() - 1) std::cout << "[ ";
		for (unsigned j = 0; j < weights[i].size(); j++) {
			std::cout << weights[i][j];
			if (j != weights[i].size() - 1) std::cout << " ";
		}
		if (i == weights.size() - 1) std::cout << " ]";
		std::cout << "\n";
	}
}

// Get output from input
std::vector<double> Synapse::getOutput(const std::vector<double>& input) {
	std::vector<double> input2 = input;
	input2.push_back(1.0); // adding bias
	assert(input2.size() == startLayerSize);	
	std::vector<double> output = std::vector<double>();
	double sum;

	for (unsigned i = 0; i < endLayerSize; i++) {
		sum = 0;
		for (unsigned j = 0; j < startLayerSize; j++) {
			sum += input2[j] * weights[j][i];
		}
		output.push_back(sum);
	}

	lastInput = input2;
	preActivation = output;
	return output;
}

// Get activated output from input
// Activated output can allow for nonlinear models
std::vector<double> Synapse::activate(const std::vector<double>& input) {
	lastOutput = Activation::wideSigmoid(getOutput(input));
	return lastOutput;
}

// Correct the weights based on target and observed values
std::vector<double> Synapse::correctWeights(const std::vector<double>& targets, const std::vector<double>& observed, const double& learningRate) {
	std::vector<double> error;
	std::vector<double> lossPrime = Loss::meanSquaredErrorPrime(targets, observed);
	for (unsigned i = 0; i < weights.size(); i++) {
		if (i != weights.size() - 1) error.push_back(0);
		for (unsigned j = 0; j < weights[i].size(); j++) {
			if (i != weights.size() - 1) error.back() += weights[i][j] * lossPrime[j];
			weights[i][j] -= learningRate * lastInput[i] * lossPrime[j];
		}
	}
	return error;
}

std::vector<double> Synapse::correctWeights(const std::vector<double>& prevError, const double& learningRate) {
	std::vector<double> error;
	for (unsigned i = 0; i < weights.size(); i++) {
		if (i != weights.size() - 1) error.push_back(0);
		for (unsigned j = 0; j < weights[i].size(); j++) {
			if (i != weights.size() - 1) error.back() += weights[i][j] * prevError[j];
			weights[i][j] += learningRate * lastInput[i] * prevError[j];
		}
	}
	return error;
}