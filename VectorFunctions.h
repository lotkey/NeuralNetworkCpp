#ifndef VECTORFUNCTIONS_H
#define VECTORFUNCTIONS_H

#include <iostream>
#include <vector>

namespace VectorFunctions {
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
}

// Returns the index of an element in a vector, or -1 if not found
template <typename T>
int VectorFunctions::indexOf(const std::vector<T>& v, const T& t) {
	// Element-by-element comparison
	for (unsigned i = 0; i < v.size(); i++) {
		if (v[i] == t) return i;
	}
	return -1;
}

// Returns true if the vector contains the element, false otherwise
template <typename T>
bool VectorFunctions::contains(const std::vector<T>& v, const T& t) {
	// Element-by-element comparison
	for (T var : v) {
		if (var == t) return true;
	}
	return false;
}

template <typename T>
std::vector<std::vector<T>> VectorFunctions::matrixify(const std::vector<T>& v) {
	std::vector<std::vector<T>> result;
	for (T t : v) {
		result.push_back(std::vector<T>());
		result.back().push_back(t);
	}
	return result;
}

template <typename T>
void VectorFunctions::print(const std::vector<T>& v) {
	for (T t : v) {
		std::cout << t << " ";
	}
	std::cout << "\n";
}

#endif