#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <random>
#include <tuple>
#include <vector>
#include "Synapse.h"

class NeuralNetwork {
private:
	// Vector of each connection between two layers
	std::vector<Synapse> synapses;
	// Size of the input layer (without the bias)
	unsigned inputSize;
	// Size of the output vector (there is no bias in the output)
	unsigned outputSize;

	// Propagate backwards
	void backPropagate(const std::vector<double>&, const std::vector<double>&, const double&);
public:
	// Constructor
	NeuralNetwork(const std::vector<unsigned>&);
	// Print function
	void print();
	// Train on data
	void train(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&, const double&, const unsigned&, const unsigned&);
	// Test on data
	double test(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	// Test on data with output being a one-hot encoded vector
	double testDiscrete(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	// Gather a prediction based on input
	std::vector<double> predict(const std::vector<double>&);
	void exportOutput(const std::vector<std::vector<double>>&, const std::string&);
};

#endif