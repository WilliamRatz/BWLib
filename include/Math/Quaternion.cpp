//
//  Vector4.cpp
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"

Quaternion::Quaternion()
{
	quad4[0] = NULL;
	quad4[1] = NULL;
	quad4[2] = NULL;
	quad4[3] = NULL;
}
Quaternion::Quaternion(float p_x, float p_y, float p_z, float p_w)
{
	quad4[0] = p_x;
	quad4[1] = p_y;
	quad4[2] = p_z;
	quad4[3] = p_w;
}
Quaternion::Quaternion(const Quaternion& quad)
{
	quad4 = quad.quad4;
}

#pragma region Methods
unsigned int Quaternion::getHashCode()
{
	unsigned int hash = 17;

	hash *= static_cast<unsigned int>(23 + std::hash<float>()(quad4[0]));
	hash *= static_cast<unsigned int>(23 + std::hash<float>()(quad4[1]));
	hash *= static_cast<unsigned int>(23 + std::hash<float>()(quad4[2]));
	hash *= static_cast<unsigned int>(23 + std::hash<float>()(quad4[3]));

	return hash;
}
#pragma endregion

#pragma region castOperations
Quaternion::operator Vector2()
{
	return Vector2(x(), y());
}
Quaternion::operator Vector3()
{
	return Vector3(x(), y(), z());
}
Quaternion::operator Vector4()
{
	return Vector4(x(), y(), z(), w());
}
Quaternion::operator Matrix<float, 4, 4>()
{
	Matrix<float, 4, 4> mat;
	mat[0][3] = x();
	mat[1][3] = y();
	mat[2][3] = z();
	mat[3][3] = w();
	return mat;
}
#pragma endregion

#pragma region arithmeticOperator
void Quaternion::operator=(const Quaternion& quad) {

	quad4[0] = quad.quad4[0];
	quad4[1] = quad.quad4[1];
	quad4[2] = quad.quad4[2];
	quad4[3] = quad.quad4[3];
}
Quaternion Quaternion::operator-()
{
	quad4[0] = -quad4[0];
	quad4[1] = -quad4[1];
	quad4[2] = -quad4[2];
	quad4[3] = -quad4[3];

	return *this;
}
Quaternion Quaternion::operator+(const Quaternion& quad) {

	Quaternion temp(*this);
	return temp += quad;
}
Quaternion Quaternion::operator-(const Quaternion& quad) {

	Quaternion temp(*this);
	return temp -= quad;
}
Quaternion Quaternion::operator*(const Quaternion& quad) {

	Quaternion temp(*this);
	return temp *= quad;
}
Quaternion& Quaternion::operator+=(const Quaternion& quad) {
	quad4[0] = quad4[0] + quad.quad4[0];
	quad4[1] = quad4[1] + quad.quad4[1];
	quad4[2] = quad4[2] + quad.quad4[2];
	quad4[3] = quad4[3] + quad.quad4[3];

	return *this;
}
Quaternion& Quaternion::operator-=(const Quaternion& quad) {
	quad4[0] = quad4[0] - quad.quad4[0];
	quad4[1] = quad4[1] - quad.quad4[1];
	quad4[2] = quad4[2] - quad.quad4[2];
	quad4[3] = quad4[3] - quad.quad4[3];

	return *this;
}
Quaternion& Quaternion::operator*=(const Quaternion& quad) {
	quad4[0] = (quad4[0] * quad.quad4[0]) - (quad4[1] * quad.quad4[1]) - (quad4[2] * quad.quad4[2]) - (quad4[3] * quad.quad4[3]);
	quad4[1] = (quad4[0] * quad.quad4[1]) + (quad4[1] * quad.quad4[0]) + (quad4[2] * quad.quad4[3]) - (quad4[3] * quad.quad4[2]);
	quad4[2] = (quad4[0] * quad.quad4[2]) - (quad4[1] * quad.quad4[3]) + (quad4[2] * quad.quad4[0]) + (quad4[3] * quad.quad4[1]);
	quad4[3] = (quad4[0] * quad.quad4[3]) + (quad4[1] * quad.quad4[2]) - (quad4[2] * quad.quad4[1]) - (quad4[3] * quad.quad4[0]);

	return *this;
}
#pragma endregion

#pragma region comparisonOperator
bool Quaternion::operator==(Quaternion& quad) {

	if (quad4[0] == quad.quad4[0] &&
		quad4[1] == quad.quad4[1] &&
		quad4[2] == quad.quad4[2] &&
		quad4[3] == quad.quad4[3]) {

		return true;
	}
	else {

		return false;
	}

}
bool Quaternion::operator!=(Quaternion& quad) {

	if (quad4[0] != quad.quad4[0] ||
		quad4[1] != quad.quad4[1] ||
		quad4[2] != quad.quad4[2] ||
		quad4[3] != quad.quad4[3]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& ausgabe, Quaternion& a)
{
	ausgabe << '(' << a.x() << '/' << a.y() << '/' << a.z() << '/' << a.w() << ')';
	return ausgabe;
}