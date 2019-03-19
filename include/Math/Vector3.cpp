//
//  Vector3.cpp
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


Vector3::Vector3()
{
	vec3[0] = NULL;
	vec3[1] = NULL;
	vec3[2] = NULL;
}
Vector3::Vector3(float p_x, float p_y, float p_z)
{
	vec3[0] = p_x;
	vec3[1] = p_y;
	vec3[2] = p_z;
}
Vector3::Vector3(const Vector3& vec)
{
	vec3 = vec.vec3;
}

#pragma region Methods
Vector3 Vector3::normalize()
{
	vec3[0] /= Vector3::length(*this);
	vec3[1] /= Vector3::length(*this);
	vec3[2] /= Vector3::length(*this);

	return *this;
}
unsigned int Vector3::getHashCode() {
	unsigned int hash = 17;

	hash *= static_cast<unsigned int>(23 + std::hash<float>()(vec3[0]));
	hash *= static_cast<unsigned int>(23 + std::hash<float>()(vec3[1]));
	hash *= static_cast<unsigned int>(23 + std::hash<float>()(vec3[2]));

	return hash;
}

float Vector3::length(const Vector3& vec)
{
	return static_cast<float>(BWMath::Sqrt(BWMath::pow(Vector3::x(vec), 2) + BWMath::pow(Vector3::y(vec), 2) + BWMath::pow(Vector3::z(vec), 2)));
}
float Vector3::dot(const Vector3& vec1, const Vector3& vec2)
{
	return Vector3::x(vec1) * Vector3::x(vec2) + Vector3::y(vec1) * Vector3::y(vec2) + Vector3::z(vec1) * Vector3::z(vec2);
}
Vector3 Vector3::cross(const Vector3& vec1, const Vector3& vec2)
{

	return Vector3((Vector3::y(vec1) * Vector3::z(vec2)) - (Vector3::z(vec1) * Vector3::y(vec2)),
		(Vector3::z(vec1) * Vector3::x(vec2)) - (Vector3::x(vec1) * Vector3::z(vec2)),
		(Vector3::x(vec1) * Vector3::y(vec2)) - (Vector3::y(vec1) * Vector3::x(vec2)));
}
Vector3 Vector3::normalized(const Vector3& vec) {

	return Vector3(Vector3::x(vec) / Vector3::length(vec), Vector3::y(vec) / Vector3::length(vec), Vector3::z(vec) / Vector3::length(vec));
}
Vector3 Vector3::One()
{
	return Vector3(1, 1, 1);
}
Vector3 Vector3::Zero()
{
	return Vector3(0, 0, 0);
}
#pragma endregion

#pragma region castOperations
Vector3::operator Vector2()
{
	return Vector2(x(), y());
}
Vector3::operator Vector4()
{
	return Vector4(x(), y(), z(), 0);
}
Vector3::operator Quaternion()
{
	return Quaternion(x(), y(), z(), 0);
}
Vector3::operator Matrix<float, 4, 4>()
{
	Matrix<float, 4, 4> mat;
	mat[0][3] = x();
	mat[1][3] = y();
	mat[2][3] = z();
	return mat;
}
#pragma endregion

#pragma region arithmeticOperator
void Vector3::operator=(const Vector3& vec) {

	vec3[0] = vec.vec3[0];
	vec3[1] = vec.vec3[1];
	vec3[2] = vec.vec3[2];
}
Vector3 Vector3::operator-()
{
	vec3[0] = -vec3[0];
	vec3[1] = -vec3[1];
	vec3[2] = -vec3[2];

	return *this;
}
Vector3& Vector3::operator+=(const Vector3& vec) {
	vec3[0] = vec3[0] + vec.vec3[0];
	vec3[1] = vec3[1] + vec.vec3[1];
	vec3[2] = vec3[2] + vec.vec3[2];

	return *this;
}
Vector3& Vector3::operator-=(const Vector3& vec) {
	vec3[0] = vec3[0] - vec.vec3[0];
	vec3[1] = vec3[1] - vec.vec3[1];
	vec3[2] = vec3[2] - vec.vec3[2];

	return *this;
}
Vector3& Vector3::operator/=(const Vector3& vec) {
	vec3[0] = vec3[0] / vec.vec3[0];
	vec3[1] = vec3[1] / vec.vec3[1];
	vec3[2] = vec3[2] / vec.vec3[2];

	return *this;
}
Vector3 Vector3::operator+(const Vector3& vec) {

	Vector3 temp(*this);
	return temp += vec;
}
Vector3 Vector3::operator-(const Vector3& vec) {

	Vector3 temp(*this);
	return temp -= vec;
}
Vector3 Vector3::operator/(const Vector3& vec) {

	Vector3 temp(*this);
	return temp /= vec;
}

Vector3& Vector3::operator*=(const int& value)
{
	vec3[0] = vec3[0] * static_cast<float>(value);
	vec3[1] = vec3[1] * static_cast<float>(value);
	vec3[2] = vec3[2] * static_cast<float>(value);

	return *this;
}
Vector3& Vector3::operator/=(const int& value) 
{
	vec3[0] = vec3[0] / static_cast<float>(value);
	vec3[1] = vec3[1] / static_cast<float>(value);
	vec3[2] = vec3[2] / static_cast<float>(value);

	return *this;
}
Vector3 Vector3::operator*(const int& value) 
{
	Vector3 temp(*this);
	return temp *= value;
}
Vector3 Vector3::operator/(const int& value) 
{
	Vector3 temp(*this);
	return temp /= value;
}

Vector3& Vector3::operator*=(const float& value) 
{
	vec3[0] = vec3[0] * static_cast<float>(value);
	vec3[1] = vec3[1] * static_cast<float>(value);
	vec3[2] = vec3[2] * static_cast<float>(value);

	return *this;
}
Vector3& Vector3::operator/=(const float& value) 
{
	vec3[0] = vec3[0] / static_cast<float>(value);
	vec3[1] = vec3[1] / static_cast<float>(value);
	vec3[2] = vec3[2] / static_cast<float>(value);

	return *this;
}
Vector3 Vector3::operator*(const float& value) 
{
	Vector3 temp(*this);
	return temp *= value;
}
Vector3 Vector3::operator/(const float& value) 
{
	Vector3 temp(*this);
	return temp /= value;
}

Vector3& Vector3::operator*=(const double& value) 
{
	vec3[0] = vec3[0] * static_cast<float>(value);
	vec3[1] = vec3[1] * static_cast<float>(value);
	vec3[2] = vec3[2] * static_cast<float>(value);

	return *this;
}
Vector3& Vector3::operator/=(const double& value) 
{
	vec3[0] = vec3[0] / static_cast<float>(value);
	vec3[1] = vec3[1] / static_cast<float>(value);
	vec3[2] = vec3[2] / static_cast<float>(value);

	return *this;
}
Vector3 Vector3::operator*(const double& value) 
{
	Vector3 temp(*this);
	return temp *= value;
}
Vector3 Vector3::operator/(const double& value) 
{
	Vector3 temp(*this);
	return temp /= value;
}
#pragma endregion

#pragma region comparisonOperator
bool Vector3::operator==(Vector3& vec) {

	if (vec3[0] == vec.vec3[0] &&
		vec3[1] == vec.vec3[1] &&
		vec3[2] == vec.vec3[2]) {

		return true;
	}
	else {

		return false;
	}

}
bool Vector3::operator!=(Vector3& vec) {

	if (vec3[0] != vec.vec3[0] ||
		vec3[1] != vec.vec3[1] ||
		vec3[2] != vec.vec3[2]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& ausgabe, Vector3& a)
{
	ausgabe << '(' << a.x() << '/' << a.y() << '/' << a.z() << ')';
	return ausgabe;
}

