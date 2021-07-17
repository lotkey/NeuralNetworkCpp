#ifndef ACTIVATION_H
#define ACTIVATION_H

#include <vector>

class Activation {
private:

	static double sigmoid(const double&);
	static std::vector<double> sigmoid(const std::vector<double>&);
	static double sigmoidPrime(const double&);
	static std::vector<double> sigmoidPrime(const std::vector<double>&);

	static double wideSigmoid(const double&);
	static std::vector<double> wideSigmoid(const std::vector<double>&);
	static double wideSigmoidPrime(const double& d);
	static std::vector<double> wideSigmoidPrime(const std::vector<double>& d);

public:

	enum class Function {
		SIGMOID,
		WIDESIGMOID,
		FASTSIGMOID
	};

	static double f(const double&, const Function&);
	static std::vector<double> f(const std::vector<double>&, const Function&);
	static double fPrime(const double&, const Function&);
	static std::vector<double> fPrime(const std::vector<double>&, const Function&);

};

#endif