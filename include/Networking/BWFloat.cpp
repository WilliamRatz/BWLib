#include "BWFloat.h"
#include "../Math/BWMath.h"
#include <bitset>

struct SplittetInt
{
	int m_value;
	int m_valueLength;
};


unsigned int BWFloat::getSign(const BWFloat& p_BWFloat)
{
	//false = + = 0
	//true  = - = 1
	return (p_BWFloat.m_value >> 31) << 31;
}
unsigned int BWFloat::getExponent(const BWFloat& p_BWFloat)
{
	return ((static_cast<unsigned int>(p_BWFloat.m_value) << 1) >> 24);
}
unsigned int BWFloat::getMantissa(const BWFloat& p_BWFloat)
{
	return ((static_cast<unsigned int>(p_BWFloat.m_value) << 9) >> 9);
}

BWFloat::BWFloat() {}
BWFloat::BWFloat(const int& p_value) 
{
	m_value = p_value;
}
BWFloat::BWFloat(std::string p_floatString)
{
	int sign = 0;
	int exponent = 127;
	int mantissa = 0;

	//pre prozess
	std::string overNull = "";
	std::string underNull = "";

	for (int i = 0; i < p_floatString.length(); ++i)
	{
		if (p_floatString[i] == '.')
		{
			++i;
			while (i < p_floatString.length())
			{
				underNull += p_floatString[i];
				++i;
			}
			break;
		}
		overNull += p_floatString[i];
	}

	//sign calculation
	if (overNull[0] == '-')
	{
		sign = 1 << 31;
		overNull.erase(0, 1);
	}

	//mantissa calculation pre kommata
	int maxBitsForComata = 0;
	if (overNull != "0") {
		std::bitset<129> mantisseBitSet;
		const int preCommaLength = (overNull.length() % 8 == 0) ? overNull.length() / 8 : overNull.length() / 8 + 1;
		SplittetInt* preCommaArray = new SplittetInt[preCommaLength];

		for (int i = 0; i < preCommaLength; ++i)
		{
			preCommaArray[i].m_value = std::stoi(overNull.substr(i * 8, 8));
			preCommaArray[i].m_valueLength = BWMath::countDigits(preCommaArray[i].m_value);
		}

		while (maxBitsForComata < 129)
		{
			bool oldplus5 = false;
			bool newplus5 = false;

			for (int i = 0; i < preCommaLength; ++i)
			{
				if (i == preCommaLength - 1)
				{
					if (preCommaArray[i].m_value % 2 == 1)
					{
						mantisseBitSet[maxBitsForComata] = 1;
					}
					preCommaArray[i].m_value = (preCommaArray[i].m_value / 2) + ((5 * BWMath::pow(10, preCommaArray[i].m_valueLength - 1) * oldplus5));
					newplus5 = false;
				}
				else
				{
					if (preCommaArray[i].m_value % 2 == 1)
					{
						newplus5 = true;
					}
					preCommaArray[i].m_value = (preCommaArray[i].m_value / 2) + ((5 * BWMath::pow(10, preCommaArray[i].m_valueLength - 1) * oldplus5));
				}
				oldplus5 = newplus5;
				newplus5 = false;
			}

			++maxBitsForComata;
			bool doBreake = true;
			for (int i = 0; i < preCommaLength; ++i)
			{
				if (preCommaArray[i].m_value != 0)
				{
					doBreake = false;
					break;
				}
			}
			if (doBreake)
			{
				break;
			}

			for (int i = 0; i < preCommaLength; ++i)
			{
				std::cout << "i" << i << " " << preCommaArray[i].m_value << std::endl;
			}
		}

		--maxBitsForComata;//because array starting at 0
		std::bitset<24> mantisseBitSetFinal;
		int forLoopLenght = (maxBitsForComata > 23) ? 23 : maxBitsForComata;
		for (int i = 0; i < forLoopLenght + 1; ++i)//to get the leading 24
		{
			mantisseBitSetFinal[23 - i] = mantisseBitSet[maxBitsForComata - i];
		}
		mantisseBitSetFinal[23] = 0;//to reset the leading 1
		mantissa |= (int)(mantisseBitSetFinal.to_ulong());
		exponent += maxBitsForComata;
	}

	//mantissa calculation post kommata
	if (underNull != "") {

		const int postCommaLength = (underNull.length() % 8 == 0) ? underNull.length() / 8 : underNull.length() / 8 + 1;
		int* postCommaArray = new int[postCommaLength];


		for (int i = 0; i < postCommaLength; ++i)
		{
			postCommaArray[i] = std::stoi(underNull.substr(i * 8, 8));
			if (i == postCommaLength - 1)
			{
				postCommaArray[i] *= BWMath::pow(10, 8 - BWMath::countDigits(postCommaArray[i]));
			}
		}

		if (overNull == "0")
		{
			bool oneTime = false;
			while (maxBitsForComata > -129)
			{
				for (int i = postCommaLength - 1; i > -1; --i)
				{
					postCommaArray[i] += postCommaArray[i];
					if (BWMath::countDigits(postCommaArray[i]) == 9)
					{
						postCommaArray[i] -= 100000000;
						if (i == 0)
						{
							if (!oneTime)
							{
								oneTime = true;
								exponent += maxBitsForComata - 1;
								std::cout << maxBitsForComata << std::endl;
								maxBitsForComata = 23;
							}
							else
							{
								int tempint = 1 << maxBitsForComata;
								mantissa |= tempint;
							}
						}
						else
						{
							++postCommaArray[i - 1];
						}
					}
				}
				--maxBitsForComata;

				if (oneTime == true && maxBitsForComata == 0)
				{
					break;
				}
				bool doBreake = true;
				for (int i = 0; i < postCommaLength; ++i)
				{
					if (postCommaArray[i] != 0)
					{
						doBreake = false;
						break;
					}
				}
				if (doBreake)
				{
					break;
				}

			}
		}
		else
		{

			maxBitsForComata = 23 - (exponent - 127);
			std::cout << maxBitsForComata << std::endl;

			while (maxBitsForComata > 0)
			{
				for (int i = postCommaLength - 1; i > -1; --i)
				{
					postCommaArray[i] += postCommaArray[i];
					if (BWMath::countDigits(postCommaArray[i]) == 9)
					{
						postCommaArray[i] -= 100000000;
						if (i == 0)
						{
							int tempint = 1 << maxBitsForComata - 1;
							mantissa |= tempint;
						}
						else
						{
							++postCommaArray[i - 1];
						}
					}
				}
				--maxBitsForComata;
				bool doBreake = true;
				for (int i = 0; i < postCommaLength; ++i)
				{
					if (postCommaArray[i] != 0)
					{
						doBreake = false;
						break;
					}
				}
				if (doBreake)
				{
					break;
				}

			}
		}
	}

	//exponent calculation
	std::cout << exponent << std::endl;
	exponent = exponent << 23;

	m_value |= sign;
	m_value |= exponent;
	m_value |= mantissa;

	std::bitset<32> y((m_value));
	std::cout << y << std::endl;
}
BWFloat::BWFloat(const BWFloat& p_bwFloat)
{
	this->m_value = p_bwFloat.m_value;
}
BWFloat::~BWFloat()
{
}

BWFloat BWFloat::operator+(const BWFloat& p_BWFloat)
{
	bool endSign = 0;
	if (this->getSign(p_BWFloat) != 0)
	{
		if (this->getSign(*this) != 0)
		{
			endSign = 1;
		}
		else
		{
			return this->operator-(p_BWFloat);
		}
	}
	else if (this->getSign(*this) != 0)
	{
		return BWFloat(p_BWFloat).operator-(*this);
	}


	std::bitset<32> a;
	if (this->getExponent(*this) > this->getExponent(p_BWFloat))
	{
		a = (this->getMantissa(*this) | 1 << 23) + ((this->getMantissa(p_BWFloat) | 1 << 23) >> BWMath::Abs(static_cast<int>(this->getExponent(*this)) - static_cast<int>(this->getExponent(p_BWFloat))));
	}
	else
	{
		a = ((this->getMantissa(*this) | 1 << 23) >> BWMath::Abs(static_cast<int>(this->getExponent(*this)) - static_cast<int>(this->getExponent(p_BWFloat)))) + (this->getMantissa(p_BWFloat) | 1 << 23);
	}

	std::cout << "bevor Exponent " << a << std::endl;

	if (a[24] == 1) {
		a = a >> 1;
		a[23] = 0;
		a |= (this->getExponent(*this) > this->getExponent(p_BWFloat)) ? (this->getExponent(*this) + 1) << 23 : (this->getExponent(p_BWFloat) + 1) << 23;
	}
	else {
		a[23] = 0;
		a |= (this->getExponent(*this) > this->getExponent(p_BWFloat)) ? this->getExponent(*this) << 23 : this->getExponent(p_BWFloat) << 23;
	}
	a |= endSign << 31;

	std::bitset<32> b(BWMath::Abs(static_cast<int>(this->getExponent(*this)) - static_cast<int>(this->getExponent(p_BWFloat))) << 23);
	std::cout << "after Exponent " << a << std::endl;

	return BWFloat(m_value = static_cast<int>(a.to_ulong()));
}
BWFloat BWFloat::operator-(const BWFloat& p_BWFloat)
{


	return BWFloat();
}
/*
BWDouble& BWFloat::operator+=(const BWDouble& p_BWDouble)
{
	// TODO: insert return statement here
}
BWDouble& BWFloat::operator-=(const BWDouble& p_BWDouble)
{
	// TODO: insert return statement here
}
BWDouble& BWFloat::operator*=(const BWDouble& p_BWDouble)
{
	// TODO: insert return statement here
}
BWDouble& BWFloat::operator/=(const BWDouble& p_BWDouble)
{
	// TODO: insert return statement here
}
BWDouble BWFloat::operator+(const BWDouble& p_BWDouble)
{
	return BWDouble();
}
BWDouble BWFloat::operator-(const BWDouble& p_BWDouble)
{
	return BWDouble();
}
BWDouble BWFloat::operator*(const BWDouble& p_BWDouble)
{
	return BWDouble();
}
BWDouble BWFloat::operator/(const BWDouble& p_BWDouble)
{
	return BWDouble();
}

BWFloat& BWFloat::operator+=(const BWFloat& p_BWFloat)
{
	// TODO: insert return statement here
}
BWFloat& BWFloat::operator-=(const BWFloat& p_BWFloat)
{
	// TODO: insert return statement here
}
BWFloat& BWFloat::operator*=(const BWFloat& p_BWFloat)
{
	// TODO: insert return statement here
}
BWFloat& BWFloat::operator/=(const BWFloat& p_BWFloat)
{
	// TODO: insert return statement here
}
BWFloat BWFloat::operator*(const BWFloat& p_BWFloat)
{
	return BWFloat();
}
BWFloat BWFloat::operator/(const BWFloat& p_BWFloat)
{
	return BWFloat();
}
*/