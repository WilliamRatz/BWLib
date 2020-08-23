//
//  Vector.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18
//  Copyright © 2018 William Ratz. All rights reserved.
//
#ifndef Vector_H
#define Vector_H

#include <stdexcept>
#include <iostream>
#include <type_traits>
#include "Math_Macros.h"

VectorTemplate class Vector {

private:
	T m_elements[N];

public:
	inline Vector()
	{
		for (std::size_t i = 0; i < N; ++i) {
			m_elements[i] = NULL;
		}
	}
	inline Vector(T value)
	{
		for (std::size_t i = 0; i < N; ++i) {
			m_elements[i] = value;
		}
	}
	inline Vector(const Vector<T, N>& vec)
	{
		for (std::size_t i = 0; i < N; ++i) {
			m_elements[i] = vec.m_elements[i];
		}
	}
	inline ~Vector() {};

	std::size_t inline size() { return N; }

	T& operator[](const std::size_t index) {
		if (index >= N) {
			throw std::out_of_range("Index out of Range");
		}
		return m_elements[index];
	}

	const T& operator[](const std::size_t index) const {
		if (index >= N) {
			throw std::out_of_range("Index out of Range");
		}
		return m_elements[index];
	}
};
#endif