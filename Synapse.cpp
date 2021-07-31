#include <cassert>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "Activation.h"
#include "Loss.h"
#include "Matrix.h"
#include "Synapse.h"
#include "Vector.h"

// Construct a synapse from a starting layer and end layer size
Synapse::Synapse(const unsigned& startLayer, const unsigned& endLayer) {
	startLayerSize = startLayer + 1;
	endLayerSize = endLayer;
	weights = Matrix(startLayerSize, endLayerSize, -1, 1);
}

Synapse::Synapse(const std::vector<std::vector<double>>& w) {
	weights = Matrix(w);

	startLayerSize = w.size();
	endLayerSize = w.front().size();
}

// Print the synapse's weights (including bias)
void Synapse::print() const {
	std::cout << weights;
}

// Get output from input
std::vector<double> Synapse::getOutput(const std::vector<double>& input) {
	std::vector<double> input2 = input;
	input2.push_back(1.0); // adding bias
	std::vector<double> output = weights.transpose() * input2;
	lastInput = input2;
	preActivation = output;
	return output;
}

std::vector<double> Synapse::propagateError(const std::vector<double>& observed, const std::vector<double>& actual, const Activation::Function& activation, const Loss::Function& loss) {
	assert(endLayerSize == observed.size() && endLayerSize == actual.size());
	error.clear();
	error = Loss::fPrime(actual, observed, loss);
	Matrix tempWeights = weights;
	tempWeights.removeBackRow();
	std::vector<double> nextError = tempWeights * error;

	for (unsigned i = 0; i < error.size(); i++) {
		error[i] *= Activation::fPrime(lastOutput[i], activation);
	}

	return nextError;
}

std::vector<double> Synapse::propagateError(const std::vector<double>& previousError, const Activation::Function& function) {
	assert(endLayerSize == previousError.size());
	error.clear();
	error = previousError;
	std::vector<double> nextError = weights * error;

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
	for (unsigned i = 0; i < weights.size(0); i++) {
		for (unsigned j = 0; j < weights.size(1); j++) {
			weights[i][j] += learningRate * error[j] * lastInput[i];
		}
	}
}

void Synapse::setWeights(const std::vector<std::vector<double>>& newWeights) {
	weights = Matrix(newWeights);
}

std::string Synapse::to_string() const {
	return weights.to_string();
}