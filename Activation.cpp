#include <cmath>
#include <vector>
#include "Activation.h"

#pragma region Sigmoid function and derivatives

double Activation::sigmoid(const double& d) {
	return 1.0 / (1.0 + exp(d));
}

std::vector<double> Activation::sigmoid(const std::vector<double>& v) {
	std::vector<double> output = std::vector<double>();
	for (double d : v) {
		output.push_back(sigmoid(d));
	}
	return output;
}

double Activation::sigmoidPrime(const double& d) {
	return sigmoid(d) * (1.0 - sigmoid(d));
}

std::vector<double> Activation::sigmoidPrime(const std::vector<double>& v) {
	std::vector<double> output = std::vector<double>();
	for (double d : v) {
		output.push_back(sigmoidPrime(d));
	}
	return output;
}

#pragma endregion

#pragma region Wide sigmoid and derivatives

double Activation::wideSigmoid(const double& d) {
	return sigmoid(d) * 2.0 - 1.0;
}

std::vector<double> Activation::wideSigmoid(const std::vector<double>& v) {
	std::vector<double> result;
	for (double d : v) {
		result.push_back(wideSigmoid(d));
	}
	return result;
}

double Activation::wideSigmoidPrime(const double& d) {
	return sigmoidPrime(d);
}

std::vector<double> Activation::wideSigmoidPrime(const std::vector<double>& v) {
	return sigmoidPrime(v);
}

#pragma endregion

#pragma region Fast sigmoid approximation and derivatives

double Activation::fastSigmoid(const double& d) {
	return d / (1 + abs(d));
}

std::vector<double> Activation::fastSigmoid(const std::vector<double>& v) {
	std::vector<double> output = std::vector<double>();
	for (double d : v) {
		output.push_back(fastSigmoid(d));
	}
	return output;
}

double Activation::fastSigmoidPrime(const double& d) {
	return (1.0 / ((abs(d) + 1.0) * (abs(d) + 1.0)));
}

std::vector<double> Activation::fastSigmoidPrime(const std::vector<double>& v) {
	std::vector<double> output = std::vector<double>();
	for (double d : v) {
		output.push_back(fastSigmoidPrime(d));
	}
	return output;
}

#pragma endregion