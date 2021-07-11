#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <vector>

namespace Activation {
#pragma region Sigmoid activation function and derivatives

	double sigmoid(const double&);
	std::vector<double> sigmoid(const std::vector<double>&);
	double sigmoidPrime(const double&);
	std::vector<double> sigmoidPrime(const std::vector<double>&);

#pragma endregion

#pragma region Wide sigmoid, between -1.0 and 1.0

	double wideSigmoid(const double&);
	std::vector<double> wideSigmoid(const std::vector<double>&);
	double wideSigmoidPrime(const double& d);
	std::vector<double> wideSigmoidPrime(const std::vector<double>& d);

#pragma endregion

#pragma region Fast sigmoid function approximation and derivatives

	double fastSigmoid(const double&);
	std::vector<double> fastSigmoid(const std::vector<double>&);
	double fastSigmoidPrime(const double&);
	std::vector<double> fastSigmoidPrime(const std::vector<double>&);

#pragma endregion
}

#endif