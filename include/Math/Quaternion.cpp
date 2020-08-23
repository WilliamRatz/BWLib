
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Quaternion.h"
#include "Matrix.h"

Quaternion::Quaternion()
{
	m_quad[0] = NULL;
	m_quad[1] = NULL;
	m_quad[2] = NULL;
	m_quad[3] = NULL;
}
Quaternion::Quaternion(const float p_x, const float p_y, const float p_z, const float p_w)
{
	m_quad[0] = p_x;
	m_quad[1] = p_y;
	m_quad[2] = p_z;
	m_quad[3] = p_w;
}
Quaternion::Quaternion(const Quaternion& p_quad)
{
	m_quad = p_quad.m_quad;
}

#pragma region Methods
void Quaternion::conjugate()
{
	m_quad[0] = -m_quad[0];
	m_quad[1] = -m_quad[1];
	m_quad[2] = -m_quad[2];
	m_quad[3] = m_quad[3];
}
void Quaternion::normalize()
{
	float length = Quaternion::length(*this);

	m_quad[0] /= length;
	m_quad[1] /= length;
	m_quad[2] /= length;
	m_quad[3] /= length;
}
void Quaternion::inverse()
{
	this->conjugate();
	this->operator/=(Quaternion::length(*this) * Quaternion::length(*this));
}
unsigned int Quaternion::getHashCode() const
{
	return ((((((static_cast<unsigned int>(m_quad[0])) * 397) ^ static_cast<unsigned int>(m_quad[1])) * 397) ^ static_cast<unsigned int>(m_quad[2])) * 397) ^ static_cast<unsigned int>(m_quad[3]);
}
void Quaternion::rotateVector3(Vector3& v)
{
	Vector3 quadVec = *this;
	float s = this->w();
	v =  quadVec * 2.0f * Vector3::dot(quadVec, v)
			+ v * (s*s - Vector3::dot(quadVec, quadVec))
			+ Vector3::cross(quadVec, v) * 2.0f * s;
}
Quaternion Quaternion::conjugated(const Quaternion& p_quad)
{
	return Quaternion(-Quaternion::x(p_quad),
					  -Quaternion::y(p_quad),
					  -Quaternion::z(p_quad),
					   Quaternion::w(p_quad));
}
Quaternion Quaternion::normalized(const Quaternion& p_quad)
{
	return Quaternion(Quaternion::x(p_quad) / Quaternion::length(p_quad), 
					  Quaternion::y(p_quad) / Quaternion::length(p_quad), 
					  Quaternion::z(p_quad) / Quaternion::length(p_quad), 
					  Quaternion::w(p_quad) / Quaternion::length(p_quad));
}
Quaternion Quaternion::inversed(const Quaternion& p_quad)
{
	Quaternion cQuad = Quaternion::conjugated(p_quad);
	return cQuad/(Quaternion::length(p_quad)* Quaternion::length(p_quad));
}
float Quaternion::length(const Quaternion& p_quad)
{
	return static_cast<float>(BWMath::sqrt(Quaternion::x(p_quad) * Quaternion::x(p_quad)
										 + Quaternion::y(p_quad) * Quaternion::y(p_quad)
										 + Quaternion::z(p_quad) * Quaternion::z(p_quad)
										 + Quaternion::w(p_quad) * Quaternion::w(p_quad)));

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
#pragma endregion

#pragma region arithmeticOperator
void Quaternion::operator=(const Quaternion& p_quad) {

	m_quad[0] = p_quad.m_quad[0];
	m_quad[1] = p_quad.m_quad[1];
	m_quad[2] = p_quad.m_quad[2];
	m_quad[3] = p_quad.m_quad[3];
}
Quaternion Quaternion::operator-()
{
	m_quad[0] = -m_quad[0];
	m_quad[1] = -m_quad[1];
	m_quad[2] = -m_quad[2];
	m_quad[3] = -m_quad[3];

	return *this;
}
Quaternion Quaternion::operator+(const Quaternion& p_quad) const {

	Quaternion temp(*this);
	return temp += p_quad;
}
Quaternion Quaternion::operator-(const Quaternion& p_quad) const {

	Quaternion temp(*this);
	return temp -= p_quad;
}
Quaternion Quaternion::operator*(const Quaternion& p_quad) const {

	Quaternion temp(*this);
	return temp *= p_quad;
}
Quaternion& Quaternion::operator+=(const Quaternion& p_quad) {
	m_quad[0] = m_quad[0] + p_quad.m_quad[0];
	m_quad[1] = m_quad[1] + p_quad.m_quad[1];
	m_quad[2] = m_quad[2] + p_quad.m_quad[2];
	m_quad[3] = m_quad[3] + p_quad.m_quad[3];

	return *this;
}
Quaternion& Quaternion::operator-=(const Quaternion& p_quad) {
	m_quad[0] = m_quad[0] - p_quad.m_quad[0];
	m_quad[1] = m_quad[1] - p_quad.m_quad[1];
	m_quad[2] = m_quad[2] - p_quad.m_quad[2];
	m_quad[3] = m_quad[3] - p_quad.m_quad[3];

	return *this;
}
Quaternion& Quaternion::operator*=(const Quaternion& p_quad) {
	m_quad[0] = (m_quad[0] * p_quad.m_quad[3]) + (m_quad[1] * p_quad.m_quad[2]) - (m_quad[2] * p_quad.m_quad[1]) + (m_quad[3] * p_quad.m_quad[0]);
	m_quad[1] = (-m_quad[0] * p_quad.m_quad[2]) + (m_quad[1] * p_quad.m_quad[3]) + (m_quad[2] * p_quad.m_quad[0]) + (m_quad[3] * p_quad.m_quad[1]);
	m_quad[2] = (m_quad[0] * p_quad.m_quad[1]) - (m_quad[1] * p_quad.m_quad[0]) + (m_quad[2] * p_quad.m_quad[3]) + (m_quad[3] * p_quad.m_quad[2]);
	m_quad[3] = (-m_quad[0] * p_quad.m_quad[0]) - (m_quad[1] * p_quad.m_quad[1]) - (m_quad[2] * p_quad.m_quad[2]) + (m_quad[3] * p_quad.m_quad[3]);

	return *this;
}
Quaternion& Quaternion::operator*=(const float& p_value)
{
	m_quad[0] *= p_value;
	m_quad[1] *= p_value;
	m_quad[2] *= p_value;
	m_quad[3] *= p_value;

	return *this;
}
Quaternion& Quaternion::operator/=(const float& p_value)
{
	m_quad[0] /= p_value;
	m_quad[1] /= p_value;
	m_quad[2] /= p_value;
	m_quad[3] /= p_value;

	return *this;
}
Quaternion Quaternion::operator*(const float& p_value) const
{
	Quaternion temp(*this);
	return temp *= p_value;
}
Quaternion Quaternion::operator/(const float& p_value) const
{
	Quaternion temp(*this);
	return temp /= p_value;
}
#pragma endregion

#pragma region comparisonOperator
bool Quaternion::operator==(Quaternion& p_quad) {

	if (m_quad[0] == p_quad.m_quad[0] &&
		m_quad[1] == p_quad.m_quad[1] &&
		m_quad[2] == p_quad.m_quad[2] &&
		m_quad[3] == p_quad.m_quad[3]) {

		return true;
	}
	else {

		return false;
	}

}
bool Quaternion::operator!=(Quaternion& p_quad) {

	if (m_quad[0] != p_quad.m_quad[0] ||
		m_quad[1] != p_quad.m_quad[1] ||
		m_quad[2] != p_quad.m_quad[2] ||
		m_quad[3] != p_quad.m_quad[3]) {

		return true;
	}
	else {

		return false;
	}
}
#pragma endregion

std::ostream& operator<<(std::ostream& p_output, Quaternion& p_quad)
{
	p_output << '(' << p_quad.x() << '/' << p_quad.y() << '/' << p_quad.z() << '/' << p_quad.w() << ')';
	return p_output;
}

std::ostream & operator<<(std::ostream& p_output, Quaternion p_quad)
{
	p_output << '(' << p_quad.x() << '/' << p_quad.y() << '/' << p_quad.z() << '/' << p_quad.w() << ')';
	return p_output;
}
