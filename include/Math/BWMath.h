//
//  BWMath.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef Math_H
#define Math_H

#include <cmath>
#include <stdexcept>
#include "Math_Macros.h"

class BWMath
{
private:

	template<typename T> static inline unsigned __int64		template_faculty(const T& value) {
		if (value < (T)0) {
			throw std::out_of_range("no negativ faculty");
		}
		unsigned __int64 result = 1ull;

		for (T i = 2; i <= value; ++i)
		{
			result *= i;
		}

		return result;
	}

	template<typename T> static inline T					template_abs(const T& value)
	{
		if (value >= (T)0)
			return value;

		return -value;
	}
	template<typename T> static inline unsigned int			template_crossSum(const T& value) {
		if (value == NULL)
			return 0u;

		T tempValue = value;
		unsigned int result = 0u;

		while (tempValue > 0) {
			result += (T)(tempValue % 10);
			tempValue /= (T)10;
		}
		return result;
	}
	template<typename T> static inline unsigned int			template_countDigits(const T& value) {
		if (value == NULL)
			return 0;

		T tempValue = value;
		unsigned int result = 0;

		while (tempValue > 9) {
			tempValue /= (T)10;
			++result;
		}
		++result;

		return result;
	}

	template<typename T> static inline int					template_sign(const T& value) {
		//return (value > 0) - (value < 0);
		return (value > (T)0) ? 1 : ((value < (T)0) ? -1 : 0);
	}

public:

	static const double				PI;
	static const double				TAU;
	static const double				EULER;
	static const double				toDeg;
	static const double				toRad;

	
	static inline double			exp(const double& value) 
	{
		double result = 0;
		unsigned int max = static_cast<unsigned int>(BWMath::ceil(value, 0) * 2.0) + 5;
		for (unsigned int i = 0; i <= max; ++i)
		{
			result += BWMath::pow(value, i) / static_cast<double>(BWMath::faculty(i));
		}

		return result;
	}
	static inline double			log(const double& value) 
	{
		if (value < 0)
			throw std::logic_error("log of negative value is undefined");

		double copieValue = value;
		double result = 0;

		double count = 0;
		for (double a = 1.0; a < 1000000.0; a *= 10.0)
		{
			while (copieValue >= BWMath::pow(10, count))
			{
				++count;
			}
			result += ((count == 0) ? count : --count / a);

			copieValue /= BWMath::pow(10, count);
			copieValue = BWMath::pow(copieValue, 10);
			count = 0;
		}

		return result;
	}
	static inline double			ln(const double& value)
	{
		if (value < 0.0)
			throw std::logic_error("ln of negative value is undefined");

		return BWMath::log(value) / BWMath::log(BWMath::EULER);
	}
	

	static inline double			sin(const double& angle)
	{
		double result = std::fmod(angle * toRad, 180);
		result *= toDeg;
		result = result - (BWMath::pow(result, 3.0) / 6.0)
			+ (BWMath::pow(result, 5.0) / 120.0)
			- (BWMath::pow(result, 7.0) / 5040.0)
			+ (BWMath::pow(result, 9.0) / 362880.0)
			- (BWMath::pow(result, 11.0) / 39916800.0);
		/*result^13 / 13!*/


	//works wenn angle was multiplied with toDeg
		if (std::fmod(angle * toRad, 360) > 180) {
			result *= -1;
		}

		return BWMath::floor(result, 7);
	}
	static inline double			cos(const double& angle)
	{
		double result = std::fmod(angle * toRad, 180);
		result *= toDeg;
		result = 1.0 - (BWMath::pow(result, 2.0) / 2.0)
			+ (BWMath::pow(result, 4.0) / 24.0)
			- (BWMath::pow(result, 6.0) / 720.0)
			+ (BWMath::pow(result, 8.0) / 40320.0)
			- (BWMath::pow(result, 10.0) / 3628800.0);
		/*result^12 / 12!*/

		if (std::fmod(angle * toRad, 360) > 90 && std::fmod(angle * toRad, 360) < 270)
		{
			if (BWMath::sign((float)result) != -1)
			{
				result *= -1;
			}
		}

		return BWMath::floor(result, 7);
	}
	static inline double			tan(const double& angle)
	{
		double result = std::fmod(angle * toRad, 180);
		result *= toDeg;
		result = result + (BWMath::pow(result, 3.0) * (1.0 / 3.0))
			+ (BWMath::pow(result, 5.0) * (2.0 / 15.0))
			+ (BWMath::pow(result, 7.0) * (17.0 / 315.0))
			+ (BWMath::pow(result, 9.0) * (62.0 / 2835.0))
			+ (BWMath::pow(result, 11.0) * (1382.0 / 155925.0))
			+ (BWMath::pow(result, 13.0) * (21844.0 / 6081075.0));
		/*taylor series for n = 8 */

		return BWMath::floor(result, 7);
	}
	static inline double			cot(const double& angle)
	{
		double result = std::fmod(angle * toRad, 180);
		result *= toDeg;
		result = (1 / result)
			- (result * (1.0 / 3.0))
			- (BWMath::pow(result, 3.0) * (1.0 / 45.0))
			- (BWMath::pow(result, 5.0) * (2.0 / 945.0))
			- (BWMath::pow(result, 7.0) * (1.0 / 4725.0))
			- (BWMath::pow(result, 9.0) * (2.0 / 93555.0));
		/*taylor series for n = 6 is to inaccurate with double */

		return BWMath::floor(result, 7);
	}

	static inline double			arcSin(const double& angle)
	{
		//if angle is bigger than 0.9 the calculation isn't exact

		double result = std::fmod(angle * toRad, 180);
		result *= toDeg;
		result = result + (0.5 * (BWMath::pow(result, 3.0) / 3.0))
			+ ((3.0 / 8.0) * (BWMath::pow(result, 5.0) / 5.0))
			+ ((5.0 / 16.0) * (BWMath::pow(result, 7.0) / 7.0))
			+ ((35.0 / 128.0) * (BWMath::pow(result, 9.0) / 9.0))
			+ ((63.0 / 256.0) * (BWMath::pow(result, 11.0) / 11.0))
			+ ((231.0 / 1024.0) * (BWMath::pow(result, 13.0) / 13.0))
			+ ((429.0 / 2048.0) * (BWMath::pow(result, 15.0) / 15.0))
			+ ((6435.0 / 32768.0) * (BWMath::pow(result, 17.0) / 17.0));
		/*taylor series for n = 8 = 1*3*5*7*9*11*13*15*17 / 2*4*6*8*10*12*14*16*18 * x^15 / 15 */

		return BWMath::floor(result, 7);
	}
	static inline double			arcCos(const double& angle)
	{
		return BWMath::floor((BWMath::PI / 2) - BWMath::arcSin(angle), 7);
	}
	static inline double			arcTan(const double& angle)
	{
		double result = std::fmod(angle * toRad, 180);
		result *= toDeg;
		result = result - ((1.0 / 3.0) * (BWMath::pow(result, 3.0)))
			+ ((1.0 / 5.0) * (BWMath::pow(result, 5.0)))
			- ((1.0 / 7.0) * (BWMath::pow(result, 7.0)))
			+ ((1.0 / 9.0) * (BWMath::pow(result, 9.0)))
			- ((1.0 / 11.0) * (BWMath::pow(result, 11.0)))
			+ ((1.0 / 13.0) * (BWMath::pow(result, 13.0)));
		/*taylor series for n = 8 = 1*3*5*7*9*11*13 / 2*4*6*8*10*12*14 * x^15 / 15 */

	/*if (std::fmod(angle * toRad, 360) > 90 && std::fmod(angle * toRad, 360) < 270)
	{
		if (BWMath::sign((float)result) != -1)
		{
			result *= -1;
		}
	}*/

		return BWMath::floor(result, 7);
	}
	static inline double			arcCot(const double& angle)
	{
		return BWMath::floor((BWMath::PI / 2) - BWMath::arcTan(angle), 7);
	}


	static inline double			sqrt(const double& value)
	{
		double result;
		result = (value + 1.0) / 2.0;
		for (__int8 i = 0; i < 5; ++i) {
			result = 0.5 * (result + value / result);
		}
		return result;
	}
	static inline double			sqrt(const double& value, const double& n)
	{
		return BWMath::pow(value, 1.0 / n);
	}

	static inline double			pow(const double& base, const double& exponent) 
	{
		switch (BWMath::sign(exponent)) 
		{
		case 1:
			if (static_cast<double>(static_cast<unsigned __int64>(exponent)) == exponent)
			{
				//exponent has a hole number
				double result = 1.0;
				for (double i = 0; i < exponent; ++i)
				{
					result *= base;
				}
				return result;
			}
			else
			{
				//exponent has a decimal number
				return BWMath::exp(exponent * BWMath::ln(base));
			}
			break;
		case 0:
			return 1.0;
			break;
		case -1:
			if (static_cast<double>(static_cast<unsigned __int64>(BWMath::abs(exponent))) == -exponent)
			{
				//exponent has a hole number
				double result = 1.0;
				for (double i = 0; i < -exponent; ++i)
				{
					result *= base;
				}
				return 1.0/result;
			}
			else
			{
				//exponent has a decimal number
				return 1.0/BWMath::exp(-exponent * BWMath::ln(base));
			}
			break;
		}
		
	}

	static inline unsigned __int64	faculty(const signed   __int8& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty(const signed   __int16& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty(const signed   __int32& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty(const signed   __int64& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty(const unsigned __int8& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty(const unsigned __int16& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty(const unsigned __int32& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty(const unsigned __int64& value) { return template_faculty(value); }

	static inline signed   __int8	abs(const signed   __int8& value) { return template_abs(value); }
	static inline signed   __int16	abs(const signed   __int16& value) { return template_abs(value); }
	static inline signed   __int32	abs(const signed   __int32& value) { return template_abs(value); }
	static inline signed   __int64	abs(const signed   __int64& value) { return template_abs(value); }
	static inline float				abs(const float& value) { return template_abs(value); }
	static inline double			abs(const double& value) { return template_abs(value); }

	static inline double			fract(const double& value)
	{
		return value - BWMath::floor(value, 0);
	}

	/*	
		round(12395.54321,  2) = 124
		round(12395.54321,  0) = 12400
		round(12395.54321, -2) = 12395.54
	*/
	static inline double			round(const double& value, const double& position)
	{
		double result = 0;

		if (position > 0)
		{
			result = (BWMath::fract(value * BWMath::pow(10, -(position))));
		}
		else if (position < 0)
		{
			result = (BWMath::fract(value * BWMath::pow(10, -(position + 1))));
		}
		else
		{
			return BWMath::fract(value);
		}

		if (result >= 0.5)
		{
			return  BWMath::ceil(value, position);
		}
		else
		{
			return BWMath::floor(value, position);
		}
	}
	/*
		floor(12395.54321,  2) = 123
		floor(12395.54321,  0) = 12395
		floor(12395.54321, -2) = 12395.54
	*/
	static inline double			floor(const double& value, const double& position)
	{
		return (value * BWMath::pow(10, -position) - BWMath::fract(value * BWMath::pow(10, -position))) * BWMath::pow(10, position);
	}
	/*
		ceil(12395.54321,  2) = 124
		ceil(12395.54321,  0) = 12400
		ceil(12395.54321, -2) = 12395.55
	*/
	static inline double			ceil(const double& value, const double& position)
	{
		return ((value * BWMath::pow(10, -position) + 1) - BWMath::fract(value * BWMath::pow(10, -position))) * BWMath::pow(10, position);
	}

	static inline unsigned int		crossSum(const signed __int8& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum(const signed __int16& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum(const signed __int32& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum(const signed __int64& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum(const unsigned __int8& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum(const unsigned __int16& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum(const unsigned __int32& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum(const unsigned __int64& value) { return template_crossSum(value); }

	static inline unsigned int		countDigits(const unsigned __int8& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits(const unsigned __int16& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits(const unsigned __int32& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits(const unsigned __int64& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits(const signed __int8& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits(const signed __int16& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits(const signed __int32& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits(const signed __int64& value) { return template_countDigits(value); }

	static inline int				sign(const __int8& value) { return template_sign(value); }
	static inline int				sign(const __int16& value) { return template_sign(value); }
	static inline int				sign(const __int32& value) { return template_sign(value); }
	static inline int				sign(const __int64& value) { return template_sign(value); }
	static inline int				sign(const float& value) { return template_sign(value); }
	static inline int				sign(const double& value) { return template_sign(value); }
};

#endif /* Math_hpp */
