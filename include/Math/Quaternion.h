//
//  Quaternion.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright � 2019 William Ratz. All rights reserved.
//

#ifndef Quaternion_H
#define Quaternion_H
#include "Vector.h"

class Vector2;
class Vector3;
class Vector4;

class Quaternion {
private:
	Vector<float, 4> m_quad;

public:
	static float x(Quaternion p_quad) { return p_quad.m_quad[0]; }
	static float y(Quaternion p_quad) { return p_quad.m_quad[1]; }
	static float z(Quaternion p_quad) { return p_quad.m_quad[2]; }
	static float w(Quaternion p_quad) { return p_quad.m_quad[3]; }

	float x() const { return m_quad[0]; }
	float y() const { return m_quad[1]; }
	float z() const { return m_quad[2]; }
	float w() const { return m_quad[3]; }

	void x(float p_x) { m_quad[0] = p_x; }
	void y(float p_y) { m_quad[1] = p_y; }
	void z(float p_z) { m_quad[2] = p_z; }
	void w(float p_w) { m_quad[3] = p_w; }

	Quaternion();
	Quaternion(const float p_x, const float p_y, const float p_z, const float p_w);
	Quaternion(const Quaternion&);

#pragma region Methods
	
	void conjugate();
	void normalize();
	void inverse();
	unsigned int getHashCode() const;
	//returns rotated Vector
	void rotateVector3(Vector3& v);
	static Quaternion conjugated(const Quaternion&);
	static Quaternion normalized(const Quaternion&);
	static Quaternion inversed(const Quaternion&);
	static float length(const Quaternion&);

#pragma endregion

#pragma region castOperations
	operator Vector2();
	operator Vector3();
	operator Vector4();
#pragma endregion

#pragma region arithmeticOperations
	void operator=(const Quaternion&);
	Quaternion operator-();

	Quaternion operator+(const Quaternion&) const;
	Quaternion operator-(const Quaternion&) const;
	Quaternion operator*(const Quaternion&) const;
	Quaternion& operator+=(const Quaternion&);
	Quaternion& operator-=(const Quaternion&);
	Quaternion& operator*=(const Quaternion&);

	Quaternion& operator*=(const float&);
	Quaternion& operator/=(const float&);
	Quaternion operator*(const float&) const;
	Quaternion operator/(const float&) const;
#pragma endregion

#pragma region comparisonOperations
	bool operator==(Quaternion&);
	bool operator!=(Quaternion&);
#pragma endregion

};

template<typename T, std::size_t M, std::size_t N>
Quaternion operator*(Matrix<T, M, N>& p_mat, Quaternion& p_quad) {

	T a1 = p_mat[0][0] * (T)p_quad.x() + p_mat[0][1] * (T)p_quad.y() + p_mat[0][2] * (T)p_quad.z() + p_mat[0][3] * (T)p_quad.w();
	T a2 = p_mat[1][0] * (T)p_quad.x() + p_mat[1][1] * (T)p_quad.y() + p_mat[1][2] * (T)p_quad.z() + p_mat[1][3] * (T)p_quad.w();
	T a3 = p_mat[2][0] * (T)p_quad.x() + p_mat[2][1] * (T)p_quad.y() + p_mat[2][2] * (T)p_quad.z() + p_mat[2][3] * (T)p_quad.w();
	T a4 = p_mat[3][0] * (T)p_quad.x() + p_mat[3][1] * (T)p_quad.y() + p_mat[3][2] * (T)p_quad.z() + p_mat[3][3] * (T)p_quad.w();

	Quaternion result((float)a1, (float)a2, (float)a3, (float)a4);

	return result;
}

std::ostream& operator<<(std::ostream&, Quaternion&);
std::ostream& operator<<(std::ostream&, Quaternion);

#endif /* Quaternion.h */
