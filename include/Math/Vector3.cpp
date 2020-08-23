
#include "BWMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"


Vector3::Vector3()
{
	m_vec3[0] = NULL;
	m_vec3[1] = NULL;
	m_vec3[2] = NULL;
}
Vector3::Vector3(float p_x, float p_y, float p_z)
{
	m_vec3[0] = p_x;
	m_vec3[1] = p_y;
	m_vec3[2] = p_z;
}
Vector3::Vector3(const Vector3& p_vec3)
{
	m_vec3 = p_vec3.m_vec3;
}

#pragma region Methods
void Vector3::normalize()
{
	*this = Vector3(this->x() / Vector3::length(*this), this->y() / Vector3::length(*this), this->z() / Vector3::length(*this));
}
unsigned __int64 Vector3::getHashCode() const
{
	return (((static_cast<unsigned __int64>(m_vec3[0]) * 397) ^ static_cast<unsigned __int64>(m_vec3[1])) * 397) ^ static_cast<unsigned __int64>(m_vec3[2]);
}

float Vector3::length(const Vector3& p_vec3)
{
	return static_cast<float>(BWMath::sqrt(BWMath::pow(Vector3::x(p_vec3), 2) + BWMath::pow(Vector3::y(p_vec3), 2) + BWMath::pow(Vector3::z(p_vec3), 2)));
}
float Vector3::dot(const Vector3& p_vec3_1, const Vector3& p_vec3_2)
{
	return Vector3::x(p_vec3_1) * Vector3::x(p_vec3_2) + Vector3::y(p_vec3_1) * Vector3::y(p_vec3_2) + Vector3::z(p_vec3_1) * Vector3::z(p_vec3_2);
}
Vector3 Vector3::cross(const Vector3& p_vec3_1, const Vector3& p_vec3_2)
{
	return Vector3((Vector3::y(p_vec3_1) * Vector3::z(p_vec3_2)) - (Vector3::z(p_vec3_1) * Vector3::y(p_vec3_2)),
		(Vector3::z(p_vec3_1) * Vector3::x(p_vec3_2)) - (Vector3::x(p_vec3_1) * Vector3::z(p_vec3_2)),
		(Vector3::x(p_vec3_1) * Vector3::y(p_vec3_2)) - (Vector3::y(p_vec3_1) * Vector3::x(p_vec3_2)));
}
Vector3 Vector3::normalized(const Vector3& p_vec3) {

	return Vector3(Vector3::x(p_vec3) / Vector3::length(p_vec3), Vector3::y(p_vec3) / Vector3::length(p_vec3), Vector3::z(p_vec3) / Vector3::length(p_vec3));
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
#pragma endregion

#pragma region arithmeticOperator
void Vector3::operator=(const Vector3& p_vec3) {

	m_vec3[0] = p_vec3.m_vec3[0];
	m_vec3[1] = p_vec3.m_vec3[1];
	m_vec3[2] = p_vec3.m_vec3[2];
}
Vector3& Vector3::operator-()
{
	m_vec3[0] = -m_vec3[0];
	m_vec3[1] = -m_vec3[1];
	m_vec3[2] = -m_vec3[2];

	return *this;
}
Vector3& Vector3::operator+=(const Vector3& p_vec3) {
	m_vec3[0] = m_vec3[0] + p_vec3.m_vec3[0];
	m_vec3[1] = m_vec3[1] + p_vec3.m_vec3[1];
	m_vec3[2] = m_vec3[2] + p_vec3.m_vec3[2];

	return *this;
}
Vector3& Vector3::operator-=(const Vector3& p_vec3) {
	m_vec3[0] = m_vec3[0] - p_vec3.m_vec3[0];
	m_vec3[1] = m_vec3[1] - p_vec3.m_vec3[1];
	m_vec3[2] = m_vec3[2] - p_vec3.m_vec3[2];

	return *this;
}
Vector3 Vector3::operator+(const Vector3& p_vec3) const {
													
	Vector3 temp(*this);							
	return temp += p_vec3;							 
}													 
Vector3 Vector3::operator-(const Vector3& p_vec3) const {

	Vector3 temp(*this);
	return temp -= p_vec3;
}

Vector3& Vector3::operator*=(const float& p_value) 
{
	m_vec3[0] = m_vec3[0] * p_value;
	m_vec3[1] = m_vec3[1] * p_value;
	m_vec3[2] = m_vec3[2] * p_value;

	return *this;
}
Vector3& Vector3::operator/=(const float& p_value) 
{
	m_vec3[0] = m_vec3[0] / p_value;
	m_vec3[1] = m_vec3[1] / p_value;
	m_vec3[2] = m_vec3[2] / p_value;

	return *this;
}
Vector3 Vector3::operator*(const float& p_value) const  
{
	Vector3 temp(*this);
	return temp *= p_value;
}
Vector3 Vector3::operator/(const float& p_value) const  
{
	Vector3 temp(*this);
	return temp /= p_value;
}

#pragma endregion

#pragma region comparisonOperator
bool Vector3::operator==(const Vector3& p_vec3) const {

	if (m_vec3[0] == p_vec3.m_vec3[0] &&
		m_vec3[1] == p_vec3.m_vec3[1] &&
		m_vec3[2] == p_vec3.m_vec3[2]) {

		return true;
	}
	else {

		return false;
	}

}
bool Vector3::operator!=(const Vector3& p_vec3) const {

	if (m_vec3[0] != p_vec3.m_vec3[0] ||
		m_vec3[1] != p_vec3.m_vec3[1] ||
		m_vec3[2] != p_vec3.m_vec3[2]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

template<typename T, std::size_t M, std::size_t N>
Vector3 operator*(const Matrix<T, M, N>& p_mat, const Vector3& p_vec3) {

	float a1 = p_mat[0][0] * (T)p_vec3.x() + p_mat[0][1] * (T)p_vec3.y() + p_mat[0][2] * (T)p_vec3.z() + p_mat[0][3] * (T)1;
	float a2 = p_mat[1][0] * (T)p_vec3.x() + p_mat[1][1] * (T)p_vec3.y() + p_mat[1][2] * (T)p_vec3.z() + p_mat[1][3] * (T)1;
	float a3 = p_mat[2][0] * (T)p_vec3.x() + p_mat[2][1] * (T)p_vec3.y() + p_mat[2][2] * (T)p_vec3.z() + p_mat[2][3] * (T)1;

	Vector3 a(a1, a2, a3);

	return a;
}

Vector3 operator*(const float& p_f, const Vector3& p_vec3)
{
	return p_vec3 * p_f;
}

std::ostream& operator<<(std::ostream& p_output, const Vector3& p_vec3)
{
	p_output << '(' << Vector3::x(p_vec3) << '/' << Vector3::y(p_vec3) << '/' << Vector3::z(p_vec3) << ')';
	return p_output;
}

std::ostream& operator<<(std::ostream& p_output, const Vector3 p_vec3)
{
	p_output << '(' << Vector3::x(p_vec3) << '/' << Vector3::y(p_vec3) << '/' << Vector3::z(p_vec3) << ')';
	return p_output;
}

