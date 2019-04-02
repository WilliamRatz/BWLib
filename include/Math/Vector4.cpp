//
//  Vector4.cpp
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#include "BWMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"

Vector4::Vector4()
{
	vec4[0] = NULL;
	vec4[1] = NULL;
	vec4[2] = NULL;
}
Vector4::Vector4(float p_x, float p_y, float p_z, float p_w)
{
	vec4[0] = p_x;
	vec4[1] = p_y;
	vec4[2] = p_z;
	vec4[3] = p_w;
}
Vector4::Vector4(const Vector4& vec)
{
	vec4 = vec.vec4;
}

#pragma region Methods
Vector4 Vector4::normalize()
{
	vec4[0] /= Vector4::length(*this);
	vec4[1] /= Vector4::length(*this);
	vec4[2] /= Vector4::length(*this);

	return *this;
}
unsigned int Vector4::getHashCode() {
	unsigned int hash = 17;

	hash *= static_cast<unsigned int>(23 + std::hash<float>()(vec4[0]));
	hash *= static_cast<unsigned int>(23 + std::hash<float>()(vec4[1]));
	hash *= static_cast<unsigned int>(23 + std::hash<float>()(vec4[2]));

	return hash;
}

float Vector4::length(const Vector4& vec)
{
	return static_cast<float>(BWMath::sqrt(BWMath::pow(Vector4::x(vec), 2) + BWMath::pow(Vector4::y(vec), 2) + BWMath::pow(Vector4::z(vec), 2)));
}
float  Vector4::dot(const Vector4& vec1, const Vector4& vec2)
{
	return Vector4::x(vec1) * Vector4::x(vec2) + Vector4::y(vec1) * Vector4::y(vec2) + Vector4::z(vec1) * Vector4::z(vec2);
}
Vector4 Vector4::normalized(const Vector4& vec) {

	return Vector4(Vector4::x(vec) / Vector4::length(vec), Vector4::y(vec) / Vector4::length(vec), Vector4::z(vec) / Vector4::length(vec), Vector4::w(vec) / Vector4::length(vec));
}
Vector4  Vector4::One()
{
	return Vector4(1, 1, 1, 1);
}
Vector4  Vector4::Zero()
{
	return Vector4(0, 0, 0, 0);
}
#pragma endregion

#pragma region castOperations
Vector4::operator Vector2()
{
	return Vector2(x(), y());
}
Vector4::operator Vector3()
{
	return Vector3(x(), y(), z());
}
Vector4::operator Quaternion()
{
	return Quaternion(x(), y(), z(), w());
}
Vector4::operator Matrix<float, 4, 4>()
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
void Vector4::operator=(const Vector4& vec) {

	vec4[0] = vec.vec4[0];
	vec4[1] = vec.vec4[1];
	vec4[2] = vec.vec4[2];
	vec4[3] = vec.vec4[3];
}
Vector4 Vector4::operator-()
{
	vec4[0] = -vec4[0];
	vec4[1] = -vec4[1];
	vec4[2] = -vec4[2];
	vec4[3] = -vec4[3];

	return *this;
}
Vector4& Vector4::operator+=(const Vector4& vec) {
	vec4[0] = vec4[0] + vec.vec4[0];
	vec4[1] = vec4[1] + vec.vec4[1];
	vec4[2] = vec4[2] + vec.vec4[2];
	vec4[3] = vec4[3] + vec.vec4[3];

	return *this;
}
Vector4& Vector4::operator-=(const Vector4& vec) {
	vec4[0] = vec4[0] - vec.vec4[0];
	vec4[1] = vec4[1] - vec.vec4[1];
	vec4[2] = vec4[2] - vec.vec4[2];
	vec4[3] = vec4[3] - vec.vec4[3];

	return *this;
}
Vector4& Vector4::operator/=(const Vector4& vec) {
	vec4[0] = vec4[0] / vec.vec4[0];
	vec4[1] = vec4[1] / vec.vec4[1];
	vec4[2] = vec4[2] / vec.vec4[2];
	vec4[3] = vec4[3] / vec.vec4[3];

	return *this;
}
Vector4 Vector4::operator+(const Vector4& vec) {

	Vector4 temp(*this);
	return temp += vec;
}
Vector4 Vector4::operator-(const Vector4& vec) {

	Vector4 temp(*this);
	return temp -= vec;
}
Vector4 Vector4::operator/(const Vector4& vec) {

	Vector4 temp(*this);
	return temp /= vec;
}

Vector4& Vector4::operator*=(const int& value)
{
	vec4[0] = vec4[0] * static_cast<float>(value);
	vec4[1] = vec4[1] * static_cast<float>(value);
	vec4[2] = vec4[2] * static_cast<float>(value);
	vec4[3] = vec4[3] * static_cast<float>(value);

	return *this;
}
Vector4& Vector4::operator/=(const int& value)
{
	vec4[0] = vec4[0] / static_cast<float>(value);
	vec4[1] = vec4[1] / static_cast<float>(value);
	vec4[2] = vec4[2] / static_cast<float>(value);
	vec4[3] = vec4[3] / static_cast<float>(value);

	return *this;
}
Vector4 Vector4::operator*(const int& value)
{
	Vector4 temp(*this);
	return temp *= value;
}
Vector4 Vector4::operator/(const int& value)
{
	Vector4 temp(*this);
	return temp /= value;
}

Vector4& Vector4::operator*=(const float& value)
{
	vec4[0] = vec4[0] * static_cast<float>(value);
	vec4[1] = vec4[1] * static_cast<float>(value);
	vec4[2] = vec4[2] * static_cast<float>(value);
	vec4[3] = vec4[3] * static_cast<float>(value);

	return *this;
}
Vector4& Vector4::operator/=(const float& value)
{
	vec4[0] = vec4[0] / static_cast<float>(value);
	vec4[1] = vec4[1] / static_cast<float>(value);
	vec4[2] = vec4[2] / static_cast<float>(value);
	vec4[3] = vec4[3] / static_cast<float>(value);

	return *this;
}
Vector4 Vector4::operator*(const float& value)
{
	Vector4 temp(*this);
	return temp *= value;
}
Vector4 Vector4::operator/(const float& value)
{
	Vector4 temp(*this);
	return temp /= value;
}

Vector4& Vector4::operator*=(const double& value)
{
	vec4[0] = vec4[0] * static_cast<float>(value);
	vec4[1] = vec4[1] * static_cast<float>(value);
	vec4[2] = vec4[2] * static_cast<float>(value);
	vec4[3] = vec4[3] * static_cast<float>(value);

	return *this;
}
Vector4& Vector4::operator/=(const double& value)
{
	vec4[0] = vec4[0] / static_cast<float>(value);
	vec4[1] = vec4[1] / static_cast<float>(value);
	vec4[2] = vec4[2] / static_cast<float>(value);
	vec4[3] = vec4[3] / static_cast<float>(value);

	return *this;
}
Vector4 Vector4::operator*(const double& value)
{
	Vector4 temp(*this);
	return temp *= value;
}
Vector4 Vector4::operator/(const double& value)
{
	Vector4 temp(*this);
	return temp /= value;
}
#pragma endregion

#pragma region comparisonOperator
bool Vector4::operator==(Vector4& vec) {

	if (vec4[0] == vec.vec4[0] &&
		vec4[1] == vec.vec4[1] &&
		vec4[2] == vec.vec4[2] &&
		vec4[3] == vec.vec4[3]) {

		return true;
	}
	else {

		return false;
	}

}
bool Vector4::operator!=(Vector4& vec) {

	if (vec4[0] != vec.vec4[0] ||
		vec4[1] != vec.vec4[1] ||
		vec4[2] != vec.vec4[2] ||
		vec4[3] != vec.vec4[3]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& ausgabe, Vector4& a)
{
	ausgabe << '(' << a.x() << '/' << a.y() << '/' << a.z() << '/' << a.w() << ')';
	return ausgabe;
}

