//
//  Vector4.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Vector4_H
#define Vector4_H
#include "Vector.h"


class Vector2;
class Vector3;
class Quaternion;


class Vector4 {

private:
	Vector<float, 4> m_vec4;

public:

	static float x(Vector4 p_vec4) { return p_vec4.m_vec4[0]; } 
	static float y(Vector4 p_vec4) { return p_vec4.m_vec4[1]; } 
	static float z(Vector4 p_vec4) { return p_vec4.m_vec4[2]; } 
	static float w(Vector4 p_vec4) { return p_vec4.m_vec4[3]; } 

	float x() const { return m_vec4[0]; }
	float y() const { return m_vec4[1]; }
	float z() const { return m_vec4[2]; }
	float w() const { return m_vec4[3]; }

	void x(float p_x) { m_vec4[0] = p_x; }
	void y(float p_y) { m_vec4[1] = p_y; }
	void z(float p_z) { m_vec4[2] = p_z; }
	void w(float p_w) { m_vec4[3] = p_w; }

	Vector4();
	Vector4(float p_x, float p_y, float p_z, float p_w);
	Vector4(const Vector4&);

#pragma region Methods
	Vector4 normalize();
	unsigned __int64 getHashCode() const;

	static Vector4 normalized(const Vector4&);
	static float length(const Vector4&);
	static float dot(const Vector4&, const Vector4&);

	static Vector4 One();
	static Vector4 Zero();
#pragma endregion

#pragma region castOperations
	operator Vector2();
	operator Vector3();
	operator Quaternion();
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector4&);
	Vector4& operator-();

	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	Vector4	operator+(const Vector4&) const;
	Vector4	operator-(const Vector4&) const;
	
	Vector4& operator*=(const float&);
	Vector4& operator/=(const float&);
	Vector4	operator*(const float&) const;
	Vector4	operator/(const float&) const;

#pragma endregion

#pragma region comparisonOperator
	bool operator==(Vector4&) const;
	bool operator!=(Vector4&) const;
#pragma endregion

};

template<typename T, std::size_t R, std::size_t C>
Vector4 operator*(const Matrix<T, R, C>& p_mat, const Vector4& p_vec4);

Vector4 operator*(const float& p_f, const Vector4& p_vec3);

std::ostream& operator<<(std::ostream&, Vector4&);
std::ostream& operator<<(std::ostream&, Vector4);


#endif /* Vector4_h */