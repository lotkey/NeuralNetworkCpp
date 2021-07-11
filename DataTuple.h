#ifndef DATATUPLE_H
#define DATATUPLE_H

#include <vector>

class DataTuple {
private:
	unsigned iSize;
	unsigned oSize;
	std::vector<std::vector<double>> features;
	std::vector<std::vector<double>> labels;
public:
	
	DataTuple(const std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&);
	DataTuple();
	unsigned inputSize() const;
	unsigned outputSize() const;
	std::vector<std::vector<double>> getFeatures() const { return features; }
	std::vector<std::vector<double>> getLabels() const { return labels; }
	void setFeatures(const std::vector<std::vector<double>>&);
	void setLabels(const std::vector<std::vector<double>>&);
};

#endif