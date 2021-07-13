#ifndef DATAREADER_H
#define DATAREADER_H

#include <string>
#include <vector>
#include "DataTuple.h"

class DataReader {
private:
	// List of all strings that are features (republican, democrat)
	std::vector<std::string> featureStrings;
	// List of all strings that are labels (y, n, ?)
	std::vector<std::string> labelStrings;
	// All feature data stored as a matrix where each row is a different entry and each column is a different feature
	std::vector<std::vector<double>> features;
	// All labels stored as one-hot vectors
	std::vector<std::vector<double>> labelsOneHot;
	// All labels stored as doubles
	std::vector<double> labels;
	std::vector<std::vector<double>> featureOutput;

	static std::vector<std::vector<double>> calculateOneHot(const std::vector<double>&, const std::vector<std::string>&);
	static std::vector<std::vector<double>> calculateOneHot(const std::vector<std::vector<double>>&, const std::vector<std::string>&);
public:
	// Constructor
	DataReader();
	// Print all data
	void print() const;
	// Print all label strings
	void printLabels() const;
	// Print all feature strings
	void printFeatures() const;
	// Read a file from a filename and separator
	void read(const std::string&, const std::string&, const bool&, const bool&);
	void readLabelInBack(const std::string&, const std::string&, const bool&, const bool&);
	std::vector<std::vector<double>> featuresForOutput() { return featureOutput; }
	// Shuffle all data
	void shuffle();
	// Return a portion of the data from the front
	DataTuple spliceFront(const double&, const bool&, const bool&);
	// Return a portion of the data from the back
	DataTuple spliceBack(const double&, const bool&, const bool&);
	// Return the vector of features
	std::vector<std::vector<double>> getFeatures() const { return features; }
	// Return the vector of labels
	std::vector<double> getLabels() const { return labels; }
};

#endif