#ifndef LOSS_H
#define LOSS_H

#include <vector>

// Loss functions and their derivatives
class Loss {
private:

	static double meanSquaredError(const double&, const double&);
	static std::vector<double> meanSquaredError(const std::vector<double>&, const std::vector<double>&);
	static double meanSquaredErrorPrime(const double&, const double&);
	static std::vector<double> meanSquaredErrorPrime(const std::vector<double>&, const std::vector<double>&);

public:

	enum class Function {
		MEANSQUAREDERROR
	};

	static double f(const double&, const double&, const Function&);
	static std::vector<double> f(const std::vector<double>&, const std::vector<double>&, const Function&);
	static double fPrime(const double&, const double&, const Function&);
	static std::vector<double> fPrime(const std::vector<double>&, const std::vector<double>&, const Function&);

};

#endif