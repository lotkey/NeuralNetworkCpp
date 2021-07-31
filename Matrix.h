#ifndef MATRIX_H
#define MATRIX_H

#include <cstdarg>
#include <iostream>
#include <string>
#include <vector>

class Matrix {
private:
	double** m = NULL;
	unsigned x = 0;
	unsigned y = 0;

	void releaseMemory();
public:
#pragma region Constructors/Destructors
	Matrix();
	Matrix(const unsigned&, const unsigned&);
	Matrix(const unsigned&, const unsigned&, const double&);
	Matrix(const unsigned&, const unsigned&, const double&, const double&);
	Matrix(const unsigned&, const unsigned&, const double**&);
	Matrix(const std::vector<std::vector<double>>&);
	Matrix(const Matrix&);
	void operator=(const Matrix&);
	~Matrix();
#pragma endregion

#pragma region Information
	unsigned size(const unsigned&) const;
	std::string to_string() const;
	bool operator==(const Matrix&) const;
#pragma endregion

#pragma region Accessors
	double* const operator[](const unsigned&);
	double* operator[](const unsigned&) const;
	double& operator()(const unsigned&, const unsigned&);
	double operator()(const unsigned&, const unsigned&) const;
#pragma endregion

#pragma region Conversions

	double** to_array() const;
	std::vector<std::vector<double>> to_vector() const;

#pragma endregion

#pragma region Mutators

	Matrix transpose() const;

	void appendRow(const std::vector<double>&);
	void appendRow(const double*&);
	void appendColumn(const std::vector<double>&);
	void appendColumn(const double*&);

	void insertRow(const std::vector<double>&, const unsigned&);
	void insertRow(const double*&, const unsigned&);
	void insertColumn(const std::vector<double>&, const unsigned&);
	void insertColumn(const double*&, const unsigned&);

	void removeBackRow();
	void removeBackColumn();

	void removeRow(const unsigned&);	
	void removeColumn(const unsigned&);

#pragma endregion

#pragma region Matrix/Scalar math

	Matrix operator+(const double&) const;
	void operator+=(const double&);
	Matrix operator-(const double&) const;
	void operator-=(const double&);
	Matrix operator*(const double&) const;
	void operator*=(const double&);
	Matrix operator/(const double&) const;
	void operator/=(const double&);

#pragma endregion

#pragma region Matrix/Vector math

	std::vector<double> operator*(const std::vector<double>&) const;
	double* times(const unsigned&, const double*&) const;
	void operator*=(const std::vector<double>&);
	void timesEquals(const unsigned&, const double*&);

#pragma endregion

#pragma region Matrix/Matrix math
	Matrix operator+(const Matrix&) const;
	void operator+=(const Matrix&);
	Matrix operator-(const Matrix&) const;
	void operator-=(const Matrix&) const;
	Matrix operator*(const Matrix&) const;
	void operator*=(const Matrix&);
#pragma endregion
};

std::ostream& operator<<(std::ostream&, const Matrix&);

#endif