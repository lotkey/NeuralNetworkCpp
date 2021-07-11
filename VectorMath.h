#ifndef VECTORMATH_H
#define VECTORMATH_H

#include <cassert>
#include <vector>

namespace VectorMath {

#pragma region Add/Subtract
	// Add a scalar to each element of a vector and return the solution
	template <typename T>
	std::vector<T> operator+(const std::vector<T>&, const T&);
	// Add two vectors together, element-by-element, and return the solution
	template <typename T>
	std::vector<T> operator+(const std::vector<T>&, const std::vector<T>&);
	// Add a scalar to each element of a vector and set the vector to the solution
	template <typename T>
	void operator+=(std::vector<T>&, const T&);
	// Add two vectors together, element-by-element, and set the vector to the solution
	template <typename T>
	void operator+=(std::vector<T>&, const std::vector<T>&);

	// Subtract a scalar from each element of a vector and return the solution
	template <typename T>
	std::vector<T> operator-(const std::vector<T>&, const T&);
	// Subtract two vectors, element-by-element, and return the solution
	template <typename T>
	std::vector<T> operator-(const std::vector<T>&, const std::vector<T>&);
	// Subtract a scalar from each element of a vector and set the vector to the solution
	template <typename T>
	void operator-=(std::vector<T>&, const T&);
	// Subtract two vectors, element-by-element, and set the vector to the solution
	template <typename T>
	void operator-=(std::vector<T>&, const std::vector<T>&);
#pragma endregion

#pragma region Multiply/Divide
	// Multiply each element of a vector by a scalar and return the solution
	template <typename T>
	std::vector<T> operator*(const std::vector<T>&, const T&);
	template <typename T>
	std::vector<T> operator*(const std::vector<T>&, const std::vector<std::vector<T>>&);
	// Multiply each element of a vector by a scalar and set the vector to the solution
	template <typename T>
	void operator*=(std::vector<T>&, const T&);	
	template <typename T>
	void operator*=(std::vector<T>&, const std::vector<std::vector<T>>&);

	// Divide each element of a vector by a scalar and return the solution
	template <typename T>
	std::vector<T> operator/(const std::vector<T>&, const T&);
	// Divide each element of a vector by a scalar and set the vector to the solution
	template <typename T>
	void operator/=(std::vector<T>&, const T&);
#pragma endregion

}

#pragma region Add/Subtract

// Add a scalar to each element of a vector and return the solution
template <typename T>
std::vector<T> VectorMath::operator+(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] + b);
	}
	return c;
}

// Add two vectors together, element-by-element, and return the solution
template <typename T>
std::vector<T> VectorMath::operator+(const std::vector<T>& a, const std::vector<T>& b) {
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
void VectorMath::operator+=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] += b;
	}
}

// Add two vectors together, element-by-element, and set the vector to the solution
template <typename T>
void VectorMath::operator+=(std::vector<T>& a, const std::vector<T>& b) {
	assert(a.size() == b.size());
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] += b[i];
	}
}

// Subtract a scalar from each element of a vector and return the solution
template <typename T>
std::vector<T> VectorMath::operator-(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] - b);
	}
	return c;
}

// Subtract two vectors, element-by-element, and return the solution
template <typename T>
std::vector<T> VectorMath::operator-(const std::vector<T>& a, const std::vector<T>& b) {
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
void VectorMath::operator-=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] -= b;
	}
}

// Subtract two vectors, element-by-element, and set the vector to the solution
template <typename T>
void VectorMath::operator-=(std::vector<T>& a, const std::vector<T>& b) {
	assert(a.size() == b.size());
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] -= b[i];
	}
}

#pragma endregion

#pragma region Multiply/Divide

// Multiply each element of a vector by a scalar and return the solution
template <typename T>
std::vector<T> VectorMath::operator*(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] * b);
	}
	return c;
}

template <typename T>
std::vector<T> VectorMath::operator*(const std::vector<T>& v, const std::vector<std::vector<T>>& m) {
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
void VectorMath::operator*=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] *= b;
	}
}

template <typename T>
void VectorMath::operator*=(std::vector<T>& v, const std::vector<std::vector<T>>& m) {
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
std::vector<T> VectorMath::operator/(const std::vector<T>& a, const T& b) {
	std::vector<T> c;
	for (unsigned i = 0; i < a.size(); i++) {
		c.push_back(a[i] / b);
	}
	return c;
}

// Divide each element of a vector by a scalar and set the vector to the solution
template <typename T>
void VectorMath::operator/=(std::vector<T>& a, const T& b) {
	for (unsigned i = 0; i < a.size(); i++) {
		a[i] /= b;
	}
}

#pragma endregion

#endif