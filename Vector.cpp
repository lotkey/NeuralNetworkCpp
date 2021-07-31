#ifndef VECTOR_CPP
#define VECTOR_CPP

#include "Vector.h"

// Returns the index of an element in a vector, or -1 if not found
template <typename T>
int Vector::indexOf(const std::vector<T>& v, const T& t) {
	// Element-by-element comparison
	for (unsigned i = 0; i < v.size(); i++) {
		if (v[i] == t) return i;
	}
	return -1;
}

// Returns true if the vector contains the element, false otherwise
template <typename T>
bool Vector::contains(const std::vector<T>& v, const T& t) {
	// Element-by-element comparison
	for (T var : v) {
		if (var == t) return true;
	}
	return false;
}

template <typename T>
std::vector<std::vector<T>> Vector::matrixify(const std::vector<T>& v) {
	std::vector<std::vector<T>> result;
	for (T t : v) {
		result.push_back(std::vector<T>());
		result.back().push_back(t);
	}
	return result;
}

template <typename T>
void Vector::print(const std::vector<T>& v) {
	for (T t : v) {
		std::cout << t << " ";
	}
	std::cout << "\n";
}

#pragma region Math

#pragma region Add/Subtract

// Add a scalar to each element of a vector and return the solution
template <typename T>
std::vector<T> Vector::Math::operator+(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] + b);
	}
	return c;
}

// Add two vectors together, element-by-element, and return the solution
template <typename T>
std::vector<T> Vector::Math::operator+(const std::vector<T>& a, const std::vector<T>& b) {
	assert(a.size() == b.size());
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] + b[i]);
	}
	std::cout << c.size() << std::endl;
	return c;
}

// Add a scalar to each element of a vector and set the vector to the solution
template <typename T>
void Vector::Math::operator+=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] += b;
	}
}

// Add two vectors together, element-by-element, and set the vector to the solution
template <typename T>
void Vector::Math::operator+=(std::vector<T>& a, const std::vector<T>& b) {
	assert(a.size() == b.size());
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] += b[i];
	}
}

// Subtract a scalar from each element of a vector and return the solution
template <typename T>
std::vector<T> Vector::Math::operator-(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] - b);
	}
	return c;
}

// Subtract two vectors, element-by-element, and return the solution
template <typename T>
std::vector<T> Vector::Math::operator-(const std::vector<T>& a, const std::vector<T>& b) {
	assert(a.size() == b.size());
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] - b[i]);
	}
	std::cout << c.size() << std::endl;
	return c;
}

// Subtract a scalar from each element of a vector and set the vector to the solution
template <typename T>
void Vector::Math::operator-=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] -= b;
	}
}

// Subtract two vectors, element-by-element, and set the vector to the solution
template <typename T>
void Vector::Math::operator-=(std::vector<T>& a, const std::vector<T>& b) {
	assert(a.size() == b.size());
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] -= b[i];
	}
}

#pragma endregion

#pragma region Multiply/Divide

// Multiply each element of a vector by a scalar and return the solution
template <typename T>
std::vector<T> Vector::Math::operator*(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] * b);
	}
	return c;
}

template <typename T>
std::vector<T> Vector::Math::operator*(const std::vector<T>& v, const std::vector<std::vector<T>>& m) {
	std::cout << m.size() << ", " << m[0].size() << ": " << v.size() << std::endl;
	assert(m.size() == v.size() || m[0].size() == v.size());
	std::vector<T> product;
	if (m.size() == v.size()) {
		for (unsigned i = 0; i < m[0].size(); i++) {
			product.push_back(0);
			for (unsigned j = 0; j < m.size(); j++) {
				product.back() += v[j] * m[j][i];
			}
		}
	}
	else {
		for (unsigned i = 0; i < m.size(); i++) {
			product.push_back(0);
			for (unsigned j = 0; j < m[i].size(); j++) {
				product.back() += v[i] * m[j][i];
			}
		}
	}

	return product;
}

// Multiply each element of a vector by a scalar and set the vector to the solution
template <typename T>
void Vector::Math::operator*=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] *= b;
	}
}

template <typename T>
void Vector::Math::operator*=(std::vector<T>& v, const std::vector<std::vector<T>>& m) {
	assert(m.size() == v.size() || m[0].size(0) == v.size());
	std::vector<T> product;
	if (m.size() == v.size()) {
		for (unsigned i = 0; i < m.size(); i++) {
			product.push_back(0);
			for (unsigned j = 0; j < m[i].size(); j++) {
				product.back() += v[i] * m[i][j];
			}
		}
	}
	else {
		for (unsigned i = 0; i < m[0].size(); i++) {
			product.push_back(0);
			for (unsigned j = 0; j < m.size(); j++) {
				product.back() += v[i] * m[j][i];
			}
		}
	}

	v = product;
}

// Divide each element of a vector by a scalar and return the solution
template <typename T>
std::vector<T> Vector::Math::operator/(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] / b);
	}
	return c;
}

// Divide each element of a vector by a scalar and set the vector to the solution
template <typename T>
void Vector::Math::operator/=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] /= b;
	}
}

#pragma endregion


#pragma endregion

#endif