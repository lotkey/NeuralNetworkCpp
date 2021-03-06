#include <cassert>
#include <iostream>
#include <vector>
#include "Loss.h"

#pragma region Mean Squared Error

double Loss::meanSquaredError(const double& target, const double& output) {
	return (output - target) * (output - target);
}

std::vector<double> Loss::meanSquaredError(const std::vector<double>& target, const std::vector<double>& actual) {
	assert(target.size() == actual.size());
	std::vector<double> output;
	for (unsigned i = 0; i < target.size(); i++) {
		output.push_back(meanSquaredError(target[i], actual[i]));
	}
	return output;
}

double Loss::meanSquaredErrorPrime(const double& target, const double& output) {
	return 2.0 * (target - output);
}

std::vector<double> Loss::meanSquaredErrorPrime(const std::vector<double>& target, const std::vector<double>& observed) {
	if (target.size() != observed.size()) {
		std::cout << "Target size: " << target.size() << ", observed size: " << observed.size() << std::endl;
	}
	assert(target.size() == observed.size());
	std::vector<double> output;
	for (unsigned i = 0; i < target.size(); i++) {
		double d = target[i];
		output.push_back(meanSquaredErrorPrime(target[i], observed[i]));
	}
	return output;
}

#pragma endregion

double Loss::f(const double& target, const double& output, const Function& func) {
	switch (func) {
	case(Function::MEANSQUAREDERROR):
		return meanSquaredError(target, output);
	default:
		return meanSquaredError(target, output);
	}
}

std::vector<double> Loss::f(const std::vector<double>& target, const std::vector<double>& output, const Function& func) {
	switch (func) {
	case(Function::MEANSQUAREDERROR):
		return meanSquaredError(target, output);
	default:
		return meanSquaredError(target, output);
	}
}

double Loss::fPrime(const double& target, const double& output, const Function& func) {
	switch (func) {
	case(Function::MEANSQUAREDERROR):
		return meanSquaredErrorPrime(target, output);
	default:
		return meanSquaredErrorPrime(target, output);
	}
}

std::vector<double> Loss::fPrime(const std::vector<double>& target, const std::vector<double>& output, const Function& func) {
	switch (func) {
	case(Function::MEANSQUAREDERROR):
		return meanSquaredErrorPrime(target, output);
	default:
		return meanSquaredErrorPrime(target, output);
	}
}