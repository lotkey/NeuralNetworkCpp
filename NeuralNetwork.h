#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <cstdarg>
#include <random>
#include <tuple>
#include <vector>
#include "Activation.h"
#include "Loss.h"
#include "Synapse.h"

class NeuralNetwork {
private:
	std::vector<unsigned> topology;
	// Vector of each connection between two layers
	std::vector<Synapse> synapses;
	// Size of the input layer (without the bias)
	unsigned inputSize;
	// Size of the output vector (there is no bias in the output)
	unsigned outputSize;

	// Propagate backwards
	void backPropagate(const std::vector<double>&, const std::vector<double>&);
	void correctWeights(const double&);

	Activation::Function activationFunction;
	Loss::Function lossFunction;
public:
	// Constructor
	NeuralNetwork(const std::vector<unsigned>&);
	NeuralNetwork(unsigned, ...);
	NeuralNetwork(const Activation::Function&, const Loss::Function&, const std::vector<unsigned>&);
	NeuralNetwork(const Activation::Function&, const Loss::Function&, unsigned, ...);
	NeuralNetwork(const std::string&);
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
	void save(const std::string&) const;
	void setWeights(const std::vector<std::vector<std::vector<double>>>&);
	void setWeights(const unsigned&, const std::vector<std::vector<double>>&);
};

#endif