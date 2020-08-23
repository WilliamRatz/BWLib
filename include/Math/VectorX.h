#pragma once
#include "Vector.h";
#include "BWMath.h"


template<typename T, std::size_t N>
class  VectorX < T, N, VectorXMacro>
{
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

	unsigned __int64 inline size() { return N; }

	static T& getItem(const unsigned __int64 index) {
		if (index >= N) {
			throw std::out_of_range("Index out of Range");
		}
		return m_elements[index];
	}

	T& operator[](const unsigned __int64 index) {
		if (index >= N) {
			throw std::out_of_range("Index out of Range");
		}
		return m_elements[index];
	}

	const T& operator[](const unsigned __int64 index) const {
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

		for (unsigned __int64 i = 1; i < N - 1; ++i)
		{
			answer ^= static_cast<unsigned __int64>(m_elements[i]) * 397;
		}
		answer ^= static_cast<unsigned __int64>(m_elements[N - 1]);
		return answer;
	}

	static double length(const VectorX& vecX)
	{
		double answer = 0.0;
		for (unsigned __int64 i = 0ull; i < vecX.size(); ++i)
		{
			answer += BWMath::pow(vecX.getItem(i), 2.0);
		}
		return BWMath::sqrt(answer);
	}
	static VectorX normalized(const VectorX& vecX)
	{
		VectorX temp(vecX);
		double length = VectorX::length(*this);
		for (unsigned __int64 i = 0ull; i < N; ++i)
		{
			temp[i] = vecX.getItem(i) / length;
		}
		return temp;
	}
	static double dot(const VectorX& vecX1, const VectorX& vecX2)
	{
		if (*this->size() != vecX1.size()) { throw ("Both Vectors need to have the same dimension"); }

		double answer = 0.0;
		for (unsigned __int64 i = 0ull; i < vecX1.size(); ++i)
		{
			answer += vecX1.getItem(i) * vecX2.getItem(i);
		}
		return answer;
	}
	//has to be specified only for Vectors with 3 items
	static double cross(const VectorX& vecX1, const VectorX& vecX2) { return 3.3; }


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


	VectorX& operator*=(const T& value)
	{
		for (unsigned __int64 i = 0; i < N; ++i)
		{
			m_elements[i] = m_elements[i] * value;
		}
		return *this;
	}
	VectorX& operator/=(const T& value)
	{
		for (unsigned __int64 i = 0; i < N; ++i)
		{
			m_elements[i] = m_elements[i] / value;
		}
		return *this;
	}
	VectorX& operator*(const T& value)
	{
		return *this *= value;
	}
	VectorX& operator/(const T& value)
	{
		return *this /= value;
	}

#pragma endregion

#pragma region comparisonOperator
	bool operator==(VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		for (unsigned long long i = 0; i < N; ++i)
		{
			if (m_elements[i] != vecX.m_elements[i])
				return false;
		}
		return true;
	}
	bool operator!=(VectorX& vecX)
	{
		if (*this->size() != vecX.size()) { throw ("Both Vectors need to have the same dimension"); }

		for (unsigned long long i = 0; i < N; ++i)
		{
			if (m_elements[i] != vecX.m_elements[i])
				return true;
		}
		return false;
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

