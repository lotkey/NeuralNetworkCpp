#ifndef SYNAPSE_H
#define SYNAPSE_H

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
public:
	// Constructor
	Synapse(const unsigned&, const unsigned&);
	// Print the synapse's weights
	void print() const;
	// Starting layer size getter
	unsigned sizeStart() const { return startLayerSize; };
	// Ending layer size getter
	unsigned sizeEnd() const { return endLayerSize; };
	// Get the output of the synapse from an input
	std::vector<double> getOutput(const std::vector<double>&);
	// Get the activated output of the synapse from an input
	std::vector<double> activate(const std::vector<double>&);
	// Correct weights based on target and observed values
	std::vector<double> correctWeights(const std::vector<double>&, const std::vector<double>&, const double&);
	std::vector<double> correctWeights(const std::vector<double>&, const double&);
};

#endif