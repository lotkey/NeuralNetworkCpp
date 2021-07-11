#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include "DataReader.h"
#include "VectorFunctions.h"

// Convert a vector of doubles (integers, really) to a vector of one-hot vectors
std::vector<std::vector<double>> DataReader::calculateOneHot(const std::vector<double>& values, const std::vector<std::string>& strings) {
	std::vector<std::vector<double>> oneHot;
	for (unsigned i = 0; i < values.size(); i++) {
		oneHot.push_back(std::vector<double>());
		for (unsigned j = 0; j < strings.size(); j++) {
			if (j == (int)values[i]) oneHot.back().push_back(1.0);
			else oneHot.back().push_back(0.0);
		}
	}
	return oneHot;
}

// Static class function
// Takes a list of vectors of doubles (should be integers, though) and a list of strings
// Returns a list of vectors
// Input: values = { { 0, 2, 1 }, { 0, 0, 1 } }, strings = { 'y', 'n', '?' }
// Output: { { 1, 0, 0,  0, 0, 1,  0, 1, 0 }, { 1, 0, 0,  1, 0, 0,  0, 1, 0 } }
std::vector<std::vector<double>> DataReader::calculateOneHot(const std::vector<std::vector<double>>& values, const std::vector<std::string>& strings) {
	std::vector<std::vector<double>> oneHot;
	for (unsigned i = 0; i < values.size(); i++) {
		oneHot.push_back(std::vector<double>());
		for (unsigned j = 0; j < values[i].size(); j++) {
			for (unsigned k = 0; k < strings.size(); k++) {
				if (k == (int)values[i][j]) oneHot.back().push_back(1.0);
				else oneHot.back().push_back(0.0);
			}
		}
	}
	return oneHot;
}

// Constructor
// Empty for now
DataReader::DataReader() {

}

// Print all data using the feature/label string vectors
void DataReader::print() const {
	for (unsigned i = 0; i < features.size(); i++) {
		//std::cout << labelStrings[(int)labels[i]] << "\t";
		std::cout << "[ " << labels[i] << " ]" << "\t";
		for (unsigned j = 0; j < features[i].size(); j++) {
			//std::cout << featureStrings[(int)features[i][j]] << " ";
			std::cout << features[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

// Print all label strings
void DataReader::printLabels() const {
	for (std::string s : labelStrings) {
		std::cout << s << " ";
	}
	std::cout << "\n";
}

// Print all feature strings
void DataReader::printFeatures() const {
	for (std::string s : featureStrings) {
		std::cout << s << " ";
	}
	std::cout << "\n";
}

// Read in a file from a filename using a separator
void DataReader::read(const std::string& filename, const std::string& separator, const bool& numericalFeatures, const bool& numericalLabels) {
	std::ifstream infile;
	std::string line;
	std::cout << "Reading in data from \"" << filename << "\" separated by \"" << separator << "\"..." << std::endl;
	infile.open(filename);

	while (std::getline(infile, line)) {

		std::string label = line.substr(0, line.find(separator));
		if (!numericalLabels && !VectorFunctions::contains(labelStrings, label)) {
			labelStrings.push_back(label);
		}
		if (numericalLabels) labels.push_back(std::atof(label.c_str()));
		else labels.push_back(VectorFunctions::indexOf(labelStrings, label));
		line = line.substr(line.find(separator) + 1, line.length() - line.find(separator));

		features.push_back(std::vector<double>());
		featureOutput.push_back(std::vector<double>());
		while (line != "") {
			std::string feature = line.substr(0, line.find(separator));
			if (!numericalFeatures && !VectorFunctions::contains(featureStrings, feature)) {
				featureStrings.push_back(feature);
			}
			if (numericalFeatures) {
				features.back().push_back(std::atof(feature.c_str()));
				featureOutput.back().push_back(std::atof(feature.c_str()));
			}
			else {
				features.back().push_back(VectorFunctions::indexOf(featureStrings, feature));
				featureOutput.back().push_back(VectorFunctions::indexOf(featureStrings, feature));
			}
			if (line.length() == 1) line = "";
			line = line.substr(line.find(separator) + 1, line.length() - line.find(separator));
		}
	}
	std::cout << "Finished reading in \"" << filename << "\".\n";
	std::cout << "Number of features: " << features.size() << "\n";
	std::cout << "Number of labels: " << labels.size() << "\n";
	infile.close();
}

// Shuffle all data
void DataReader::shuffle() {
	std::cout << "Joining labels and features...\n";
	std::vector<std::vector<double>> data;
	for (unsigned i = 0; i < labels.size(); i++) {
		data.push_back(std::vector<double>());
		for (unsigned j = 0; j < features[i].size(); j++) {
			data.back().push_back(features[i][j]);
		}
		data.back().push_back(labels[i]);
	}
	std::cout << "Finished joining.\n";

	std::cout << "Shuffling data...\n";
	std::random_shuffle(data.begin(), data.end());
	std::cout << "Finished shuffling.\n";
	features.clear();
	labels.clear();

	std::cout << "Separating features and labels...\n";
	for (unsigned i = 0; i < data.size(); i++) {
		features.push_back(std::vector<double>(data[i].begin(), data[i].end() - 1));
		labels.push_back(data[i][data[i].size() - 1]);
	}
	std::cout << "Finished separating data.\n";
}

// Return a portion of the data from the front
DataTuple DataReader::spliceFront(const double& portion, const bool& oneHotFeatures, const bool& oneHotLabels) {
	assert(portion >= 0 && portion <= 1.0);
	std::cout << "Splicing " << portion * 100.0 << "% off of the front end...\n";
	unsigned end = (unsigned)(features.size() * (1.0 - portion));
	std::vector<std::vector<double>> featureSplice = std::vector<std::vector<double>>(features.begin(), features.end() - end);
	std::vector<double> labelSplice = std::vector<double>(labels.begin(), labels.end() - end);

	DataTuple data = DataTuple();
	if (oneHotFeatures) data.setFeatures(calculateOneHot(featureSplice, featureStrings));
	else data.setFeatures(featureSplice);
	if (oneHotLabels) data.setLabels(calculateOneHot(labelSplice, labelStrings));
	else data.setLabels(VectorFunctions::matrixify(labelSplice));
	std::cout << "Finished splicing.\n";
	return data;
}

// Return a portion of the data from the back
DataTuple DataReader::spliceBack(const double& portion, const bool& oneHotFeatures, const bool& oneHotLabels) {
	assert(portion >= 0 && portion <= 1.0);
	std::cout << "Splicing " << portion * 100.0 << "% off of the back end...\n";
	unsigned start = (unsigned)(features.size() * (1.0 - portion));
	std::vector<std::vector<double>> featureSplice = std::vector<std::vector<double>>(features.begin() + start, features.end());
	std::vector<double> labelSplice = std::vector<double>(labels.begin() + start, labels.end());

	DataTuple data = DataTuple();
	if (oneHotFeatures) data.setFeatures(calculateOneHot(featureSplice, featureStrings));
	else data.setFeatures(featureSplice);
	if (oneHotLabels) data.setLabels(calculateOneHot(labelSplice, labelStrings));
	else data.setLabels(VectorFunctions::matrixify(labelSplice));
	std::cout << "Finished splicing.\n";
	return data;
}