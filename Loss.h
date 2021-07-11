#ifndef LOSS_H
#define LOSS_H

#include <vector>

// Loss functions and their derivatives
namespace Loss {
#pragma region Mean Squared Error

	double meanSquaredError(const double&, const double&);
	std::vector<double> meanSquaredError(const std::vector<double>&, const std::vector<double>&);
	double meanSquaredErrorPrime(const double&, const double&);
	std::vector<double> meanSquaredErrorPrime(const std::vector<double>&, const std::vector<double>&);

#pragma endregion
}

#endif