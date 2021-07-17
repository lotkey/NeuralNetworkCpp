#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "Activation.h"
#include "Loss.h"
#include "Synapse.h"
#include "VectorFunctions.h"
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

Synapse::Synapse(const std::vector<std::vector<double>>& w) {
	startLayerSize = w.size();
	endLayerSize = w.front().size();
	for (unsigned i = 0; i < w.size(); i++) {
		weights.push_back(std::vector<double>());
		for (unsigned j = 0; j < w[i].size(); j++) {
			weights.back().push_back(w[i][j]);
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

std::vector<double> Synapse::propagateError(const std::vector<double>& observed, const std::vector<double>& actual, const Activation::Function& activation, const Loss::Function& loss) {
	assert(endLayerSize == observed.size() && endLayerSize == actual.size());
	std::vector<double> nextError;
	error.clear();
	error = Loss::fPrime(actual, observed, loss);

	for (unsigned i = 0; i < weights.size() - 1; i++) {
		nextError.push_back(0.0);
		for (unsigned j = 0; j < weights[i].size(); j++) {
			nextError[i] += weights[i][j] * error[j];
		}
	}

	for (unsigned i = 0; i < error.size(); i++) {
		error[i] *= Activation::fPrime(lastOutput[i], activation);
	}

	return nextError;
}

std::vector<double> Synapse::propagateError(const std::vector<double>& previousError, const Activation::Function& function) {
	assert(endLayerSize == previousError.size());
	std::vector<double> nextError;
	error.clear();
	error = previousError;

	for (unsigned i = 0; i < weights.size() - 1; i++) {
		nextError.push_back(0.0);
		for (unsigned j = 0; j < weights[i].size(); j++) {
			nextError[i] += weights[i][j] * error[j];
		}
	}

	for (unsigned i = 0; i < error.size(); i++) {
		error[i] *= Activation::fPrime(lastOutput[i], function);
	}

	return nextError;
}

// Get activated output from input
// Activated output can allow for nonlinear models
std::vector<double> Synapse::activate(const std::vector<double>& input, const Activation::Function& function) {
	lastOutput = Activation::f(getOutput(input), function);
	return lastOutput;
}

void Synapse::correctWeights(const double& learningRate) {
	for (unsigned i = 0; i < weights.size(); i++) {
		for (unsigned j = 0; j < weights[i].size(); j++) {
			weights[i][j] += learningRate * error[j] * lastInput[i];
 		}
	}
}

void Synapse::setWeights(const std::vector<std::vector<double>>& newWeights) {
	assert(newWeights.size() == weights.size());
	for (unsigned i = 0; i < weights.size(); i++) {
		assert(newWeights[i].size() == weights[i].size());
		for (unsigned j = 0; j < weights[i].size(); j++) {
			weights[i][j] = newWeights[i][j];
		}
	}
}

std::string Synapse::toString() const {
	std::string str = "";
	for (std::vector<double> v : weights) {
		for (double d : v) {
			str += std::to_string(d) + " ";
		}
		str += "\n";
	}
	return str;
}