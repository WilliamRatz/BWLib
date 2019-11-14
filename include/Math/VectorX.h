#pragma once
#include "Vector.h";
#include "BWMath.h"


template<typename T, std::size_t N>
class VectorXMacro {

private:
	T m_elements[N];

public:

	inline VectorX()
	{
		for (std::size_t i = 0; i < N; ++i) {
			m_elements[i] = NULL;
		}
	}
	inline VectorX(T value)
	{
		for (std::size_t i = 0; i < N; ++i) {
			m_elements[i] = value;
		}
	}
	inline VectorX(const VectorX<T, N>& vecX)
	{
		for (std::size_t i = 0; i < N; ++i) {
			m_elements[i] = vecX.m_elements[i];
		}
	}
	inline ~VectorX() {}

	std::size_t inline size() { return N; }

	static T& getItem(const std::size_t index) {
		if (index >= N) {
			throw std::out_of_range("Index out of Range");
		}
		return m_elements[index];
	}

	T& operator[](const std::size_t index) {
		if (index >= N) {
			throw std::out_of_range("Index out of Range");
		}
		return m_elements[index];
	}

	const T& operator[](const std::size_t index) const {
		if (index > N) {
			throw std::out_of_range("Index out of Range");
		}
		return m_elements[index];
	}

#pragma region Methods

	void normalize()
	{
		double length = VectorX::length(*this);
		for (unsigned __int64 i = 0; i < N; ++i)
		{
			m_elements[i] = m_elements[i] / length;
		}
	}
	unsigned __int64 getHashCode()
	{
		unsigned __int64 answer = static_cast<unsigned __int64>(m_elements[0]) * 397;

		for (unsigned __int64 i = 1; i < N-1; ++i)
		{
			answer ^= static_cast<unsigned __int64>(m_elements[i]) * 397;
		}
		answer ^= static_cast<unsigned __int64>(m_elements[N-1]);
		return answer;
	}

	static VectorX normalized(const VectorX& vecX)
	{
		VectorX temp(vecX);
		double length = VectorX::length(*this);
		for (unsigned __int64 i = 0; i < N; ++i)
		{
			temp[i] = vecX[i] / length;
		}
		return temp;
	}
	static double length(const VectorX& vecX)
	{
		double answer = 0;
		for (unsigned __int64 i = 0; i < vecX.size(); ++i) 
		{
			answer + BWMath::pow(vecX[i], 2);
		}
		return BWMath::sqrt(answer);
	}

#pragma endregion

#pragma region castOperations
	/*operator Vector2()
	{
	}
	operator Vector4()
	{
	}
	operator Quaternion()
	{
	}
	operator Matrix<float, 4, 4>()
	{
	}*/
#pragma endregion

#pragma region arithmeticOperator
	void operator=(const VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		for (unsigned __int64 i = 0; i < N; ++i) 
		{
			m_elements[i] = vecX[i];
		}
	}
	VectorX operator-()
	{
		if (*this->size() != m_elements.size()) { throw ("Both Vectors need to have the same dimension"); }

		for (unsigned __int64 i = 0; i < N; ++i)
		{
			m_elements[i] = -m_elements[i];
		}

		return *this;
	}

	VectorX& operator+=(const VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		for (unsigned __int64 i = 0; i < N; ++i)
		{
			m_elements[i] = m_elements[i] + vecX[i];
		}
		return *this;
	}
	VectorX& operator-=(const VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		for (unsigned __int64 i = 0; i < N; ++i)
		{
			m_elements[i] = m_elements[i] - vecX[i];
		}
		return *this;
	}
	VectorX& operator/=(const VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		for (unsigned __int64 i = 0; i < N; ++i)
		{
			m_elements[i] = m_elements[i] - vecX[i];
		}
		return *this;
	}
	VectorX operator+(const VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		VectorX temp(*this);
		return temp += vecX;
	}
	VectorX operator-(const VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		VectorX temp(*this);
		return temp -= vecX;
	}
	VectorX operator/(const VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		VectorX temp(*this);
		return temp /= vecX;
	}

	//VectorX& operator*=(const int&)
	//{
	//	if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

	//	for (unsigned __int64 i = 0; i < N ++i)
	//	{

	//	}
	//}
	//VectorX& operator/=(const int&)
	//{
	//	if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

	//	for (unsigned __int64 i = 0; i < N ++i)
	//	{

	//	}
	//}
	//VectorX operator*(const int&)
	//{
	//	if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

	//	for (unsigned __int64 i = 0; i < N ++i)
	//	{

	//	}
	//}
	//VectorX operator/(const int&)
	//{
	//	if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

	//	for (unsigned __int64 i = 0; i < N ++i)
	//	{

	//	}
	//}

#pragma endregion

#pragma region comparisonOperator
	bool operator==(VectorX& vecX)
	{
	}
	bool operator!=(VectorX& vecX)
	{
	}
#pragma endregion


};
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream&, VectorXMacro&)
{
}
template<typename T, std::size_t N>
std::ostream& operator<<(std::ostream&, VectorXMacro)
{
}

