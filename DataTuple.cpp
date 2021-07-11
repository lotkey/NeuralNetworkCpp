#include <vector>
#include "DataTuple.h"

DataTuple::DataTuple(const std::vector<std::vector<double>>& features, const std::vector<std::vector<double>>& labels) {
	this->features = features;
	this->labels = labels;
	iSize = features[0].size();
	oSize = labels[0].size();
}

DataTuple::DataTuple() {
	iSize = 0;
	oSize = 0;
}

unsigned DataTuple::inputSize() const {
	return iSize;
}

unsigned DataTuple::outputSize() const {
	return oSize;
}

void DataTuple::setFeatures(const std::vector<std::vector<double>>& v) {
	features = v;
	iSize = v[0].size();
}

void DataTuple::setLabels(const std::vector<std::vector<double>>& v) {
	labels = v;
	oSize = v[0].size();
}