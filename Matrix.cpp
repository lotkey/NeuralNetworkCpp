#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <random>
#include <string>
#include "Matrix.h"

#pragma region Private
void Matrix::releaseMemory() {
	if (m != NULL) {
		for (unsigned i = 0; i < x; i++) {
			delete[] m[i];
		}
		delete[] m;
		m = NULL;
	}
	x = 0;
	y = 0;
}
#pragma endregion

#pragma region Public
#pragma region Constructors/Destructors

Matrix::Matrix() {
	x = 0;
	y = 0;
	m = NULL;
	return;
}

Matrix::Matrix(const unsigned& numRows, const unsigned& numCols) {
	x = numRows;
	y = numCols;
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			m[i][j] = 0.0;
		}
	}
}

Matrix::Matrix(const unsigned& numRows, const unsigned& numCols, const double& val) {
	x = numRows;
	y = numCols;
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			m[i][j] = val;
		}
	}
}

Matrix::Matrix(const unsigned& numRows, const unsigned& numCols, const double& lowerBound, const double& upperBound) {
	assert(upperBound > lowerBound);
	x = numRows;
	y = numCols;
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			double randomDouble = rand() / (double)RAND_MAX;
			m[i][j] = randomDouble;
		}
	}
}

Matrix::Matrix(const unsigned& x, const unsigned& y, const double**& arr) {
	this->x = x;
	this->y = y;
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			m[i][j] = arr[i][j];
		}
	}
}

Matrix::Matrix(const std::vector<std::vector<double>>& v) {
	x = v.size();
	y = v.front().size();
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			m[i][j] = v[i][j];
		}
	}
}

Matrix::Matrix(const Matrix& matrix) {
	x = matrix.x;
	y = matrix.y;
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			m[i][j] = matrix(i, j);
		}
	}
}

void Matrix::operator=(const Matrix& matrix) {
	releaseMemory();
	x = matrix.x;
	y = matrix.y;
	m = new double*[x];
	
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			m[i][j] = matrix(i, j);
		}
	}
}

Matrix::~Matrix() {
	releaseMemory();
}

#pragma endregion

#pragma region Information

unsigned Matrix::size(const unsigned& dimension) const {
	assert(dimension == 0 || dimension == 1);
	return (dimension == 0) ? x : y;
}

std::string Matrix::to_string() const {
	std::string result = "";
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			result += std::to_string(m[i][j]);
			if (i != x - 1 || j != y - 1) result += ", ";
		}
		if (i != x - 1) result += "\n";
	}
	return result;
}

bool Matrix::operator==(const Matrix& m) const {
	if (x != m.x || y != m.y) return false;
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			if (m.m[i][j] != m[i][j]) return false;
		}
	}
	return true;
}

#pragma endregion

#pragma region Accessors

double* const Matrix::operator[](const unsigned& i) {
	return m[i];
}

double* Matrix::operator[](const unsigned& i) const {
	double* arr = new double[y];
	for (unsigned j = 0; j < y; j++) {
		arr[j] = m[i][j];
	}
	return arr;
}

double& Matrix::operator()(const unsigned& i, const unsigned& j) {
	return m[i][j];
}

double Matrix::operator()(const unsigned& i, const unsigned& j) const {
	return m[i][j];
}

#pragma endregion

#pragma region Conversions

double** Matrix::to_array() const {
	double** arr = new double* [x];
	for (unsigned i = 0; i < x; i++) {
		arr[i] = new double[y];
		for (unsigned j = 0; j < y; j++) {
			arr[i][j] = m[i][j];
		}
	}
	return arr;
}

std::vector<std::vector<double>> Matrix::to_vector() const {
	std::vector<std::vector<double>> v = std::vector<std::vector<double>>();
	for (unsigned i = 0; i < x; i++) {
		v.push_back(std::vector<double>());
		for (unsigned j = 0; j < y; j++) {
			v.back().push_back(m[i][j]);
		}
	}
	return v;
}

#pragma endregion

#pragma region Mutators

Matrix Matrix::transpose() const {
	Matrix t = Matrix(y, x);
	for (unsigned i = 0; i < y; i++) {
		for (unsigned j = 0; j < x; j++) {
			t.m[i][j] = m[j][i];
		}
	}
	return t;
}

void Matrix::appendRow(const std::vector<double>& v) {
	assert(v.size() == y);
	double** newM = new double* [x + 1];
	for (unsigned i = 0; i < x; i++) {
		newM[i] = m[i];
		m[i] = NULL;
	}

	newM[x] = new double[y];
	for (unsigned j = 0; j < y; j++) {
		newM[x][j] = v[j];
	}
	x++;
	delete[] m;
	m = newM;
}

void Matrix::appendRow(const double*& arr) {
	double** newM = new double* [x + 1];
	for (unsigned i = 0; i < x; i++) {
		newM[i] = m[i];
		m[i] = NULL;
	}

	newM[x] = new double[y];
	for (unsigned j = 0; j < y; j++) {
		newM[x][j] = arr[j];
	}
	x++;
	delete[] m;
	m = newM;
}

void Matrix::appendColumn(const std::vector<double>& v) {
	assert(v.size() == x);
	unsigned newX = x;
	unsigned newY = y + 1;
	double** newM = new double* [newX];

	for (unsigned i = 0; i < newX; i++) {
		newM[i] = new double[newY];
		for (unsigned j = 0; j < newY; j++) {
			if (j == y) {
				newM[i][j] = v[i];
			}
			else {
				newM[i][j] = m[i][j];
			}
		}
	}

	releaseMemory();
	x = newX;
	y = newY;
	m = newM;
}

void Matrix::appendColumn(const double*& arr) {
	unsigned newX = x;
	unsigned newY = y + 1;
	double** newM = new double* [newX];

	for (unsigned i = 0; i < newX; i++) {
		newM[i] = new double[newY];
		for (unsigned j = 0; j < newY; j++) {
			if (j == y) {
				newM[i][j] = arr[i];
			}
			else {
				newM[i][j] = m[i][j];
			}
		}
	}

	releaseMemory();
	x = newX;
	y = newY;
	m = newM;
}

void Matrix::insertRow(const std::vector<double>& v, const unsigned& index) {
	assert(v.size() == y);
	assert(index <= x);
	if (index == x) return appendRow(v);

	double** newM = new double* [x + 1];
	for (unsigned i = 0; i <= x; i++) {
		if (i < index) {
			newM[i] = m[i];
			m[i] = NULL;
		}
		else if (i == index) {
			newM[i] = new double[y];
			for (unsigned j = 0; j < y; j++) {
				newM[i][j] = v[j];
			}
		}
		else {
			newM[i] = m[i - 1];
			m[i - 1] = NULL;
		}
	}
	x++;
	delete[] m;
	m = newM;
}

void Matrix::insertRow(const double*& arr, const unsigned& index) {
	assert(index <= x);
	if (index == x) return appendRow(arr);

	double** newM = new double* [x + 1];
	for (unsigned i = 0; i <= x; i++) {
		if (i < index) {
			newM[i] = m[i];
			m[i] = NULL;
		}
		else if (i == index) {
			newM[i] = new double[y];
			for (unsigned j = 0; j < y; j++) {
				newM[i][j] = arr[j];
			}
		}
		else {
			newM[i] = m[i - 1];
			m[i - 1] = NULL;
		}
	}
	x++;
	delete[] m;
	m = newM;
}

void Matrix::insertColumn(const std::vector<double>& v, const unsigned& index) {
	assert(v.size() == x);
	assert(index <= y);
	if (index == y) return appendColumn(v);

	unsigned newX = x;
	unsigned newY = y + 1;
	double** newM = new double* [newX];

	for (unsigned i = 0; i < newX; i++) {
		newM[i] = new double[newY];
		for (unsigned j = 0; j < newY; j++) {
			if (j < index) {
				newM[i][j] = m[i][j];
			}
			else if (j == index) {
				newM[i][j] = v[i];
			}
			else {
				newM[i][j] = m[i][j - 1];
			}
		}
	}

	releaseMemory();
	x = newX;
	y = newY;
	m = newM;
}

void Matrix::insertColumn(const double*& arr, const unsigned& index) {
	assert(index <= y);
	if (index == y) return appendColumn(arr);

	unsigned newX = x;
	unsigned newY = y + 1;
	double** newM = new double* [newX];

	for (unsigned i = 0; i < newX; i++) {
		newM[i] = new double[newY];
		for (unsigned j = 0; j < newY; j++) {
			if (j < index) {
				newM[i][j] = m[i][j];
			}
			else if (j == index) {
				newM[i][j] = arr[i];
			}
			else {
				newM[i][j] = m[i][j - 1];
			}
		}
	}

	releaseMemory();
	x = newX;
	y = newY;
	m = newM;
}

void Matrix::removeBackRow() {
	return removeRow(x - 1);
}

void Matrix::removeBackColumn() {
	return removeColumn(y - 1);
}

void Matrix::removeRow(const unsigned& index) {
	assert(index < x);
	double** newM = new double* [x - 1];
	for (unsigned i = 0; i < x; i++) {
		if (i < index) {
			newM[i] = m[i];
		}
		else if (i > index) {
			newM[i - 1] = m[i];
		}
		m[i] = NULL;
	}
	x--;
	delete[] m[index];
	delete[] m;
	m = newM;
}

void Matrix::removeColumn(const unsigned& index) {
	assert(index < y);
	unsigned newX = x;
	unsigned newY = y - 1;
	double** newM = new double* [newX];
	
	for (unsigned i = 0; i < newX; i++) {
		newM[i] = new double[newY];
		for (unsigned j = 0; j < newY; j++) {
			if (j < index) {
				newM[i][j] = m[i][j];
			}
			else {
				newM[i][j] = m[i][j + 1];
			}
		}
	}

	releaseMemory();
	x = newX;
	y = newY;
	m = newM;
}

#pragma endregion

#pragma region Matrix/Scalar math

Matrix Matrix::operator+(const double& t) const {
	Matrix matrix = Matrix(x, y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			matrix.m[i][j] = t + m[i][j];
		}
	}
	return matrix;
}

void Matrix::operator+=(const double& t) {
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			m[i][j] += t;
		}
	}
}

Matrix Matrix::operator-(const double& t) const {
	Matrix matrix = Matrix(x, y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			matrix.m[i][j] = m[i][j] - t;
		}
	}
	return matrix;
}

void Matrix::operator-=(const double& t) {
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			m[i][j] -= t;
		}
	}
}

Matrix Matrix::operator*(const double& t) const {
	Matrix matrix = Matrix(x, y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			matrix.m[i][j] = m[i][j] * t;
		}
	}
	return matrix;
}

void Matrix::operator*=(const double& t) {
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			m[i][j] *= t;
		}
	}
}

Matrix Matrix::operator/(const double& t) const {
	Matrix matrix = Matrix(x, y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			matrix.m[i][j] = m[i][j] / t;
		}
	}
	return matrix;
}

void Matrix::operator/=(const double& t) {
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			m[i][j] /= t;
		}
	}
}

#pragma endregion

#pragma region Matrix/Vector math

std::vector<double> Matrix::operator*(const std::vector<double>& v) const {
	assert(v.size() == y);
	std::vector<double> result = std::vector<double>(x);
	for (unsigned i = 0; i < x; i++) {
		result[i] = 0;
		for (unsigned j = 0; j < y; j++) {
			result[i] += m[i][j] * v[j];
		}
	}
	return result;
}

double* Matrix::times(const unsigned& len, const double*& arr) const {
	assert(len == y);
	double* result = new double[x];
	for (unsigned i = 0; i < x; i++) {
		result[i] = 0;
		for (unsigned j = 0; j < y; j++) {
			result[i] += m[i][j] * arr[j];
		}
	}
	return result;
}

void Matrix::operator*=(const std::vector<double>& v) {
	std::vector<double> result = *this * v;
	releaseMemory();
	x = result.size();
	y = 1;
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		m[i][0] = result[i];
	}
}

void Matrix::timesEquals(const unsigned& len, const double*& arr) {
	double* result = this->times(len, arr);
	releaseMemory();
	x = len;
	y = 1;
	m = new double*[x];
	for (unsigned i = 0; i < x; i++) {
		m[i] = new double[y];
		m[i][0] = result[i];
	}
}

#pragma endregion

#pragma region Matrix/Matrix math

Matrix Matrix::operator+(const Matrix& matrix) const {
	assert(matrix.x == x && matrix.y == y);
	Matrix result = Matrix(x, y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			result.m[i][j] = m[i][j] + matrix.m[i][j];
		}
	}
	return result;
}

void Matrix::operator+=(const Matrix& matrix) {
	assert(matrix.x == x && matrix.y == y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			m[i][j] += matrix.m[i][j];
		}
	}
}

Matrix Matrix::operator-(const Matrix& matrix) const {
	assert(matrix.x == x && matrix.y == y);
	Matrix result = Matrix(x, y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			result.m[i][j] = m[i][j] - matrix.m[i][j];
		}
	}
	return result;
}

void Matrix::operator-=(const Matrix& matrix) const {
	assert(matrix.x == x && matrix.y == y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < y; j++) {
			m[i][j] -= matrix.m[i][j];
		}
	}
}

Matrix Matrix::operator*(const Matrix& matrix) const {
	assert(y == matrix.x);
	Matrix product = Matrix(x, matrix.y);
	for (unsigned i = 0; i < x; i++) {
		for (unsigned j = 0; j < matrix.y; j++) {
			product[i][j] = (double)0.0;
			for (unsigned k = 0; k < y; k++) {
				product[i][j] += m[i][k] * matrix.m[k][j];
			}
		}
	}
	return product;
}

void Matrix::operator*=(const Matrix& matrix) {
	assert(y == matrix.x);
	Matrix product = *this * matrix;
	*this = product;
}

#pragma endregion
#pragma endregion

#pragma region Non-Member
std::ostream& operator<<(std::ostream& os, const Matrix& m) {
	os << m.to_string();
	return os;
}
#pragma endregion