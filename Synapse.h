#ifndef SYNAPSE_H
#define SYNAPSE_H

#include <iostream>
#include <vector>

class Synapse {
private:
	// Matrix of weights from the starting layer to the ending layer
	std::vector<std::vector<double>> weights;
	// Store the last input for correcting weights
	std::vector<double> lastInput;
	// Store the last output for correcting weights
	std::vector<double> lastOutput;
	// Store the output pre-activation function to save time on calculating derivatives (cost of space)
	std::vector<double> preActivation;
	// Starting layer size
	unsigned startLayerSize;
	// Ending layer size
	unsigned endLayerSize;
	std::vector<double> error;
public:
	// Constructor
	Synapse(const unsigned&, const unsigned&);
	Synapse(const std::vector<std::vector<double>>&);
	// Print the synapse's weights
	void print() const;
	// Starting layer size getter
	unsigned sizeStart() const { return startLayerSize; };
	// Ending layer size getter
	unsigned sizeEnd() const { return endLayerSize; };
	// Get the output of the synapse from an input
	std::vector<double> getOutput(const std::vector<double>&);
	// Get the activated output of the synapse from an input
	std::vector<double> activate(const std::vector<double>&, const Activation::Function&);
	std::vector<double> propagateError(const std::vector<double>&, const std::vector<double>&, const Activation::Function&, const Loss::Function&);
	std::vector<double> propagateError(const std::vector<double>&, const Activation::Function&);
	void correctWeights(const double&);
	void setWeights(const std::vector<std::vector<double>>&);
	std::string toString() const;
};

#endif