//
//  Vector3.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Vector3_H
#define Vector3_H
#include "Vector.h"

class Vector2;
class Vector4;
class Quaternion;

class Vector3 {

private:
	Vector<float, 3> m_vec3;

public:

	static float x(Vector3 m_vec3) { return m_vec3.m_vec3[0]; } 
	static float y(Vector3 m_vec3) { return m_vec3.m_vec3[1]; } 
	static float z(Vector3 m_vec3) { return m_vec3.m_vec3[2]; } 

	float x() const { return m_vec3[0]; }
	float y() const { return m_vec3[1]; }
	float z() const { return m_vec3[2]; }

	void x(float p_x) { m_vec3[0] = p_x; }
	void y(float p_y) { m_vec3[1] = p_y; }
	void z(float p_z) { m_vec3[2] = p_z; }

	Vector3();
	Vector3(float p_x, float p_y, float p_z);
	Vector3(const Vector3&);

#pragma region Methods
	
	void normalize();
	unsigned __int64 getHashCode() const;

	static Vector3 normalized(const Vector3&);
	static float length(const Vector3&); 
	static float dot(const Vector3&, const Vector3&); 
	static Vector3 cross(const Vector3&, const Vector3&); 

	static Vector3 One();
	static Vector3 Zero();
	
#pragma endregion

#pragma region castOperations
	operator Vector2();
	operator Vector4();
	operator Quaternion();
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const Vector3&);
	Vector3& operator-();

	Vector3& operator+=(const Vector3&);
	Vector3& operator-=(const Vector3&);
	Vector3 operator+(const Vector3&) const;
	Vector3 operator-(const Vector3&) const;
	
	Vector3& operator*=(const float&);
	Vector3& operator/=(const float&);
	Vector3 operator*(const float&) const;
	Vector3 operator/(const float&) const;
#pragma endregion

#pragma region comparisonOperator
	bool operator==(const Vector3&) const;
	bool operator!=(const Vector3&) const;
#pragma endregion

};

template<typename T, std::size_t M, std::size_t N>
Vector3 operator*(const Matrix<T, M, N>& p_mat, const Vector3& p_vec3);

Vector3 operator*(const float& p_f, const Vector3& p_vec3);

std::ostream& operator<<(std::ostream&, const Vector3&);
std::ostream& operator<<(std::ostream&, const Vector3);


#endif /* Vector3_h */