//
//  Vector2.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Vector2_H
#define Vector2_H
#include "Vector.h"

class Vector3;
class Vector4;
class Quaternion;

class Vector2 {
private:
	Vector<float, 2> m_vec2;

public:

	static float x(Vector2 p_vec2) { return p_vec2.m_vec2[0]; }
	static float y(Vector2 p_vec2) { return p_vec2.m_vec2[1]; }

	float x() const { return m_vec2[0]; }
	float y() const { return m_vec2[1]; }

	void x(float p_x) { m_vec2[0] = p_x; }
	void y(float p_y) { m_vec2[1] = p_y; }

	Vector2();
	Vector2(float p_x, float p_y);
	Vector2(const Vector2&);

#pragma region Methods
	void normalize();
	unsigned __int64 getHashCode() const;

	static Vector2 normalized(const Vector2&);
	static float length(const Vector2&);
	static float dot(const Vector2&, const Vector2&);

	static Vector2 One();
	static Vector2 Zero();
#pragma endregion

#pragma region castOperations
	operator Vector3();
	operator Vector4();
	operator Quaternion();
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector2&);
	Vector2& operator-();

	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2 operator+(const Vector2&) const;
	Vector2 operator-(const Vector2&) const;

	Vector2& operator*=(const float&);
	Vector2& operator/=(const float&);
	Vector2 operator*(const float&) const;
	Vector2 operator/(const float&) const;
#pragma endregion

#pragma region comparisonOperator
	bool operator==(Vector2&) const;
	bool operator!=(Vector2&) const;
#pragma endregion
};

template<typename T, std::size_t M, std::size_t N>
Vector2 operator*(const Matrix<T, M, N>& p_mat, const Vector2& p_vec2);

Vector2 operator*(const float& p_f, const Vector2& p_vec3);

std::ostream& operator<<(std::ostream&, const Vector2&);
std::ostream& operator<<(std::ostream&, const Vector2);


#endif /* Vector2_h */
