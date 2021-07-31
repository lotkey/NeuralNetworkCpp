#ifndef VECTORFUNCTIONS_H
#define VECTORFUNCTIONS_H

#include <iostream>
#include <vector>

namespace Vector {
	// Returns the index of an element in a vector, or -1 if not found
	template <typename T>
	int indexOf(const std::vector<T>&, const T&);
	// Returns true if the vector contains the element, false otherwise
	template <typename T>
	bool contains(const std::vector<T>&, const T&);

	// Returns a vector of vectors, each with one item in it
	template <typename T>
	std::vector<std::vector<T>> matrixify(const std::vector<T>&);

	template <typename T>
	void print(const std::vector<T>&);

	namespace Math {
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

}

#include "Vector.cpp"

#endif