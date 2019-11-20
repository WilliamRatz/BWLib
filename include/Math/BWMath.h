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
	template<typename T> static inline double				template_exp(const T& value) {
		double result = 0;
		unsigned int max = static_cast<unsigned int>(BWMath::ceil(value, 0) * 2.0) + 5;
		for (unsigned int i = 0; i <= max; ++i)
		{
			result += BWMath::pow(value, i) / static_cast<double>(BWMath::faculty(i));
		}

		return result;
	}
	template<typename T> static inline double				template_log(const T& value)
	{
		if (value < 0)
			throw std::logic_error("log of negative value is undefined");

		T copieValue = value;
		double result = 0;

		for (double a = 1; a < 1000000.0; a *= 10)
		{
			double count = 0;
			while (copieValue >= (T)BWMath::pow(10, count))
			{
				++count;
			}
			result += ((count == 0) ? count : --count / a);

			copieValue /= (T)BWMath::pow(10, count);
			copieValue = (T)BWMath::pow(copieValue, 10);
		}

		return result;
	}
	template<typename T> static inline double				template_ln(const T& value)
	{
		if (value < 0)
			throw std::logic_error("ln of negative value is undefined");

		return BWMath::log(value) / BWMath::log(BWMath::EULER);
	}
									   
	template<typename T> static inline double				template_sin(const T& angle)
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
	template<typename T> static inline double				template_cos(const T& angle)
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
	template<typename T> static inline double				template_tan(const T& angle)
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
	template<typename T> static inline double				template_cot(const T& angle)
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
									   
	template<typename T> static inline double				template_arcSin(const T& angle)
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
	template<typename T> static inline double				template_arcCos(const T& angle)
	{
		return BWMath::floor((BWMath::PI / 2) - BWMath::arcSin(angle), 7);
	}
	template<typename T> static inline double				template_arcTan(const T& angle)
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
	template<typename T> static inline double				template_arcCot(const T& angle)
	{
		return BWMath::floor((BWMath::PI / 2) - BWMath::arcTan(angle), 7);
	}

	template<typename T> static inline double				template_sqrt(const T& value)
	{
		double result;
		result = (value + 1.0) / 2.0;
		for (__int8 i = 0; i < 5; ++i) {
			result = 0.5 * (result + value / result);
		}
		return result;
	}
	template<typename T, typename Z> static inline T		template_sqrt(const T& value, const Z& n)
	{
		return (T)BWMath::pow(value, 1 / n);
	}

	template<typename R,typename T, typename Z> static inline R	template_pow(const T& base, const Z& exponent)
	{

		if (BWMath::ceil(exponent, 0) == BWMath::floor(exponent, 0))
		{
			//exponent has a hole number
			double result = 1.0;
			for (Z i = 0; i < exponent; ++i)
			{
				result *= base;
			}
			return (R)result;
		}
		else
		{
			//exponent has a decimal number
			return (R)BWMath::exp(exponent * BWMath::ln(base));
		}
	}
	template<typename T> static inline unsigned __int64		template_faculty(const T& value) {
		if (value < 0) {
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
		if (value >= 0)
			return value;

		return value - (2 * value);
	}

	template<typename T> static inline T					template_fract(const T& value)
	{
		return value - BWMath::floor(value, 0);
	}
	template<typename T, typename Z> static inline T		template_round(const T& value, const Z& position)
	{
		T temp = value * (T)BWMath::pow(10.0, position + 1.0);
		temp = temp;
		temp -= (value * (T)BWMath::pow(10, position)) * (T)10.0;

		if (temp > 4.0)
		{
			return BWMath::ceil(value, position);
		}
		else
		{
			return BWMath::floor(value, position);
		}
	}
	template<typename T, typename Z> static inline T		template_floor(const T& value, const Z& position)
	{
		T temp = value * (T)BWMath::pow(10.0, position);
		temp = (T)static_cast<int>(temp);
		temp *= (T)10.0;
		temp /= (T)BWMath::pow(10.0, (position) + 1.0);

		return temp;
	}
	template<typename T, typename Z> static inline T		template_ceil(const T& value, const Z& position)
	{
		T temp = value * (T)BWMath::pow(10.0, position);
		temp = (T)static_cast<int>(temp);
		temp *= (T)10.0;
		temp += (T)10.0;
		temp /= (T)BWMath::pow(10.0, position + 1.0);

		return temp;
	}
	template<typename T> static inline unsigned int			template_crossSum(const T& value) {
		if (value == NULL)
			return 0;

		T tempValue = value;
		unsigned int result = 0;

		while (tempValue > 0) {
			result += tempValue % 10;
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
		return (value > 0) ? 1 : ((value < 0) ? -1 : 0);
	}

public: 

	static const double		PI;
	static const double		TAU;
	static const double		EULER;
	static const double		toDeg;
	static const double		toRad;
	
	static inline double			exp			(const signed __int8& value)	{ return template_exp(value); }
	static inline double			exp			(const signed __int16& value)	{ return template_exp(value); }
	static inline double			exp			(const signed __int32& value)	{ return template_exp(value); }
	static inline double			exp			(const signed __int64& value)	{ return template_exp(value); }
	static inline double			exp			(const unsigned __int8& value)	{ return template_exp(value); }
	static inline double			exp			(const unsigned __int16& value) { return template_exp(value); }
	static inline double			exp			(const unsigned __int32& value) { return template_exp(value); }
	static inline double			exp			(const unsigned __int64& value) { return template_exp(value); }
	static inline double			exp			(const float& value)			{ return template_exp(value); }
	static inline double			exp			(const double& value)			{ return template_exp(value); }

	static inline double			log			(const signed __int8& value)	{ return template_log(value); }
	static inline double			log			(const signed __int16& value)	{ return template_log(value); }
	static inline double			log			(const signed __int32& value)	{ return template_log(value); }
	static inline double			log			(const signed __int64& value)	{ return template_log(value); }
	static inline double			log			(const unsigned __int8& value)	{ return template_log(value); }
	static inline double			log			(const unsigned __int16& value) { return template_log(value); }
	static inline double			log			(const unsigned __int32& value) { return template_log(value); }
	static inline double			log			(const unsigned __int64& value) { return template_log(value); }
	static inline double			log			(const float& value)			{ return template_log(value); }
	static inline double			log			(const double& value)			{ return template_log(value); }

	static inline double			ln			(const signed __int8& value)	{ return template_ln(value); }
	static inline double			ln			(const signed __int16& value)	{ return template_ln(value); }
	static inline double			ln			(const signed __int32& value)	{ return template_ln(value); }
	static inline double			ln			(const signed __int64& value)	{ return template_ln(value); }
	static inline double			ln			(const unsigned __int8& value)	{ return template_ln(value); }
	static inline double			ln			(const unsigned __int16& value) { return template_ln(value); }
	static inline double			ln			(const unsigned __int32& value) { return template_ln(value); }
	static inline double			ln			(const unsigned __int64& value) { return template_ln(value); }
	static inline double			ln			(const float& value)			{ return template_ln(value); }
	static inline double			ln			(const double& value)			{ return template_ln(value); }

	static inline double			sin			(const signed __int8& angle)	{ return template_sin(angle); };
	static inline double			sin			(const signed __int16& angle)	{ return template_sin(angle); };
	static inline double			sin			(const signed __int32& angle)	{ return template_sin(angle); };
	static inline double			sin			(const signed __int64& angle)	{ return template_sin(angle); };
	static inline double			sin			(const unsigned __int8& angle)	{ return template_sin(angle); };
	static inline double			sin			(const unsigned __int16& angle) { return template_sin(angle); };
	static inline double			sin			(const unsigned __int32& angle) { return template_sin(angle); };
	static inline double			sin			(const unsigned __int64& angle) { return template_sin(angle); };
	static inline double			sin			(const float& angle)			{ return template_sin(angle); };
	static inline double			sin			(const double& angle)			{ return template_sin(angle); };

	static inline double			cos			(const signed __int8& angle)	{ return template_cos(angle); };
	static inline double			cos			(const signed __int16& angle)	{ return template_cos(angle); };
	static inline double			cos			(const signed __int32& angle)	{ return template_cos(angle); };
	static inline double			cos			(const signed __int64& angle)	{ return template_cos(angle); };
	static inline double			cos			(const unsigned __int8& angle)	{ return template_cos(angle); };
	static inline double			cos			(const unsigned __int16& angle) { return template_cos(angle); };
	static inline double			cos			(const unsigned __int32& angle) { return template_cos(angle); };
	static inline double			cos			(const unsigned __int64& angle) { return template_cos(angle); };
	static inline double			cos			(const float& angle)			{ return template_cos(angle); };
	static inline double			cos			(const double& angle)			{ return template_cos(angle); };

	static inline double			tan			(const signed __int8& angle)	{ return template_tan(angle); };
	static inline double			tan			(const signed __int16& angle)	{ return template_tan(angle); };
	static inline double			tan			(const signed __int32& angle)	{ return template_tan(angle); };
	static inline double			tan			(const signed __int64& angle)	{ return template_tan(angle); };
	static inline double			tan			(const unsigned __int8& angle)	{ return template_tan(angle); };
	static inline double			tan			(const unsigned __int16& angle) { return template_tan(angle); };
	static inline double			tan			(const unsigned __int32& angle) { return template_tan(angle); };
	static inline double			tan			(const unsigned __int64& angle) { return template_tan(angle); };
	static inline double			tan			(const float& angle)			{ return template_tan(angle); };
	static inline double			tan			(const double& angle)			{ return template_tan(angle); };

	static inline double			cot			(const signed __int8& angle)	{ return template_cot(angle); };
	static inline double			cot			(const signed __int16& angle)	{ return template_cot(angle); };
	static inline double			cot			(const signed __int32& angle)	{ return template_cot(angle); };
	static inline double			cot			(const signed __int64& angle)	{ return template_cot(angle); };
	static inline double			cot			(const unsigned __int8& angle)	{ return template_cot(angle); };
	static inline double			cot			(const unsigned __int16& angle) { return template_cot(angle); };
	static inline double			cot			(const unsigned __int32& angle) { return template_cot(angle); };
	static inline double			cot			(const unsigned __int64& angle) { return template_cot(angle); };
	static inline double			cot			(const float& angle)			{ return template_cot(angle); };
	static inline double			cot			(const double& angle)			{ return template_cot(angle); };

	static inline double			arcSin		(const signed __int8& angle)	{ return template_arcSin(angle); };
	static inline double			arcSin		(const signed __int16& angle)	{ return template_arcSin(angle); };
	static inline double			arcSin		(const signed __int32& angle)	{ return template_arcSin(angle); };
	static inline double			arcSin		(const signed __int64& angle)	{ return template_arcSin(angle); };
	static inline double			arcSin		(const unsigned __int8& angle)	{ return template_arcSin(angle); };
	static inline double			arcSin		(const unsigned __int16& angle) { return template_arcSin(angle); };
	static inline double			arcSin		(const unsigned __int32& angle) { return template_arcSin(angle); };
	static inline double			arcSin		(const unsigned __int64& angle) { return template_arcSin(angle); };
	static inline double			arcSin		(const float& angle)			{ return template_arcSin(angle); };
	static inline double			arcSin		(const double& angle)			{ return template_arcSin(angle); };

	static inline double			arcCos		(const signed __int8& angle)	{ return template_arcCos(angle); };
	static inline double			arcCos		(const signed __int16& angle)	{ return template_arcCos(angle); };
	static inline double			arcCos		(const signed __int32& angle)	{ return template_arcCos(angle); };
	static inline double			arcCos		(const signed __int64& angle)	{ return template_arcCos(angle); };
	static inline double			arcCos		(const unsigned __int8& angle)	{ return template_arcCos(angle); };
	static inline double			arcCos		(const unsigned __int16& angle) { return template_arcCos(angle); };
	static inline double			arcCos		(const unsigned __int32& angle) { return template_arcCos(angle); };
	static inline double			arcCos		(const unsigned __int64& angle) { return template_arcCos(angle); };
	static inline double			arcCos		(const float& angle)			{ return template_arcCos(angle); };
	static inline double			arcCos		(const double& angle)			{ return template_arcCos(angle); };

	static inline double			arcTan		(const signed __int8& angle)	{ return template_arcTan(angle); };
	static inline double			arcTan		(const signed __int16& angle)	{ return template_arcTan(angle); };
	static inline double			arcTan		(const signed __int32& angle)	{ return template_arcTan(angle); };
	static inline double			arcTan		(const signed __int64& angle)	{ return template_arcTan(angle); };
	static inline double			arcTan		(const unsigned __int8& angle)	{ return template_arcTan(angle); };
	static inline double			arcTan		(const unsigned __int16& angle) { return template_arcTan(angle); };
	static inline double			arcTan		(const unsigned __int32& angle) { return template_arcTan(angle); };
	static inline double			arcTan		(const unsigned __int64& angle) { return template_arcTan(angle); };
	static inline double			arcTan		(const float& angle)			{ return template_arcTan(angle); };
	static inline double			arcTan		(const double& angle)			{ return template_arcTan(angle); };

	static inline double			arcCot		(const signed __int8& angle)	{ return template_arcCot(angle); };
	static inline double			arcCot		(const signed __int16& angle)	{ return template_arcCot(angle); };
	static inline double			arcCot		(const signed __int32& angle)	{ return template_arcCot(angle); };
	static inline double			arcCot		(const signed __int64& angle)	{ return template_arcCot(angle); };
	static inline double			arcCot		(const unsigned __int8& angle)	{ return template_arcCot(angle); };
	static inline double			arcCot		(const unsigned __int16& angle) { return template_arcCot(angle); };
	static inline double			arcCot		(const unsigned __int32& angle) { return template_arcCot(angle); };
	static inline double			arcCot		(const unsigned __int64& angle) { return template_arcCot(angle); };
	static inline double			arcCot		(const float& angle)			{ return template_arcCot(angle); };
	static inline double			arcCot		(const double& angle)			{ return template_arcCot(angle); };

	
	static inline double			sqrt		(const double& value)			{ return template_sqrt(value); }
	static inline float				sqrt		(const float& value, const signed __int8& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const signed __int16& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const signed __int32& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const signed __int64& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const unsigned __int8& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const unsigned __int16& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const unsigned __int32& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const unsigned __int64& n)		{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const float& n)				{ return template_sqrt(value, n); }
	static inline float				sqrt		(const float& value, const double& n)				{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const signed __int8& n)		{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const signed __int16& n)		{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const signed __int32& n)		{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const signed __int64& n)		{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const unsigned __int8& n)		{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const unsigned __int16& n)	{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const unsigned __int32& n)	{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const unsigned __int64& n)	{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const float& n)				{ return template_sqrt(value, n); }
	static inline double			sqrt		(const double& value, const double& n)				{ return template_sqrt(value, n); }

	static inline signed __int64			pow			(const signed __int8& base, const signed __int8&		exponent) { return template_pow<__int64, signed __int8, signed __int8>		(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const signed __int16&		exponent) { return template_pow<__int64, signed __int8, signed __int16>		(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const signed __int32&		exponent) { return template_pow<__int64, signed __int8, signed __int32>		(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const signed __int64&		exponent) { return template_pow<__int64, signed __int8, signed __int64>		(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const unsigned __int8&		exponent) { return template_pow<__int64, signed __int8, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const unsigned __int16&		exponent) { return template_pow<__int64, signed __int8, unsigned __int16>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const unsigned __int32&		exponent) { return template_pow<__int64, signed __int8, unsigned __int32>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const unsigned __int64&		exponent) { return template_pow<__int64, signed __int8, unsigned __int64>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const float&				exponent) { return template_pow<__int64, signed __int8, float>				(base, exponent); }
	static inline signed __int64			pow			(const signed __int8& base, const double&				exponent) { return template_pow<__int64, signed __int8, double>				(base, exponent); }

	static inline signed __int64			pow			(const unsigned __int8& base, const signed __int8&		exponent) { return template_pow<__int64, unsigned __int8, signed __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const signed __int16&		exponent) { return template_pow<__int64, unsigned __int8, signed __int16>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const signed __int32&		exponent) { return template_pow<__int64, unsigned __int8, signed __int32>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const signed __int64&		exponent) { return template_pow<__int64, unsigned __int8, signed __int64>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const unsigned __int8&	exponent) { return template_pow<__int64, unsigned __int8, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const unsigned __int16&	exponent) { return template_pow<__int64, unsigned __int8, unsigned __int16>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const unsigned __int32&	exponent) { return template_pow<__int64, unsigned __int8, unsigned __int32>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const unsigned __int64&	exponent) { return template_pow<__int64, unsigned __int8, unsigned __int64>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const float&				exponent) { return template_pow<__int64, unsigned __int8, float>			(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int8& base, const double&				exponent) { return template_pow<__int64, unsigned __int8, double>			(base, exponent); }

	static inline signed __int64			pow			(const signed __int16& base, const signed __int8&		exponent) { return template_pow<__int64, signed __int16, signed __int8>		(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const signed __int16&		exponent) { return template_pow<__int64, signed __int16, signed __int16>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const signed __int32&		exponent) { return template_pow<__int64, signed __int16, signed __int32>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const signed __int64&		exponent) { return template_pow<__int64, signed __int16, signed __int64>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const unsigned __int8&		exponent) { return template_pow<__int64, signed __int16, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const unsigned __int16&	exponent) { return template_pow<__int64, signed __int16, unsigned __int16>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const unsigned __int32&	exponent) { return template_pow<__int64, signed __int16, unsigned __int32>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const unsigned __int64&	exponent) { return template_pow<__int64, signed __int16, unsigned __int64>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const float&				exponent) { return template_pow<__int64, signed __int16, float>				(base, exponent); }
	static inline signed __int64			pow			(const signed __int16& base, const double&				exponent) { return template_pow<__int64, signed __int16, double>			(base, exponent); }
				  
	static inline signed __int64			pow			(const unsigned __int16& base, const signed __int8&		exponent) { return template_pow<__int64, unsigned __int16, signed __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const signed __int16&	exponent) { return template_pow<__int64, unsigned __int16, signed __int16>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const signed __int32&	exponent) { return template_pow<__int64, unsigned __int16, signed __int32>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const signed __int64&	exponent) { return template_pow<__int64, unsigned __int16, signed __int64>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const unsigned __int8&	exponent) { return template_pow<__int64, unsigned __int16, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const unsigned __int16&	exponent) { return template_pow<__int64, unsigned __int16, unsigned __int16>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const unsigned __int32&	exponent) { return template_pow<__int64, unsigned __int16, unsigned __int32>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const unsigned __int64&	exponent) { return template_pow<__int64, unsigned __int16, unsigned __int64>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const float&				exponent) { return template_pow<__int64, unsigned __int16, float>			(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int16& base, const double&			exponent) { return template_pow<__int64, unsigned __int16, double>			(base, exponent); }
				  
	static inline signed __int64			pow			(const signed __int32& base, const signed __int8&		exponent) { return template_pow<__int64, signed __int32, signed __int8>		(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const signed __int16&		exponent) { return template_pow<__int64, signed __int32, signed __int16>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const signed __int32&		exponent) { return template_pow<__int64, signed __int32, signed __int32>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const signed __int64&		exponent) { return template_pow<__int64, signed __int32, signed __int64>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const unsigned __int8&		exponent) { return template_pow<__int64, signed __int32, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const unsigned __int16&	exponent) { return template_pow<__int64, signed __int32, unsigned __int16>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const unsigned __int32&	exponent) { return template_pow<__int64, signed __int32, unsigned __int32>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const unsigned __int64&	exponent) { return template_pow<__int64, signed __int32, unsigned __int64>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const float&				exponent) { return template_pow<__int64, signed __int32, float>				(base, exponent); }
	static inline signed __int64			pow			(const signed __int32& base, const double&				exponent) { return template_pow<__int64, signed __int32, double>			(base, exponent); }
				  
	static inline signed __int64			pow			(const unsigned __int32& base, const signed __int8&		exponent) { return template_pow<__int64, unsigned __int32, signed __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const signed __int16&	exponent) { return template_pow<__int64, unsigned __int32, signed __int16>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const signed __int32&	exponent) { return template_pow<__int64, unsigned __int32, signed __int32>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const signed __int64&	exponent) { return template_pow<__int64, unsigned __int32, signed __int64>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const unsigned __int8&	exponent) { return template_pow<__int64, unsigned __int32, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const unsigned __int16&	exponent) { return template_pow<__int64, unsigned __int32, unsigned __int16>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const unsigned __int32&	exponent) { return template_pow<__int64, unsigned __int32, unsigned __int32>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const unsigned __int64&	exponent) { return template_pow<__int64, unsigned __int32, unsigned __int64>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const float&				exponent) { return template_pow<__int64, unsigned __int32, float>			(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int32& base, const double&			exponent) { return template_pow<__int64, unsigned __int32, double>			(base, exponent); }
				  
	static inline signed __int64			pow			(const signed __int64& base, const signed __int8&		exponent) { return template_pow<__int64, signed __int64, signed __int8>		(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const signed __int16&		exponent) { return template_pow<__int64, signed __int64, signed __int16>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const signed __int32&		exponent) { return template_pow<__int64, signed __int64, signed __int32>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const signed __int64&		exponent) { return template_pow<__int64, signed __int64, signed __int64>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const unsigned __int8&		exponent) { return template_pow<__int64, signed __int64, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const unsigned __int16&	exponent) { return template_pow<__int64, signed __int64, unsigned __int16>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const unsigned __int32&	exponent) { return template_pow<__int64, signed __int64, unsigned __int32>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const unsigned __int64&	exponent) { return template_pow<__int64, signed __int64, unsigned __int64>	(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const float&				exponent) { return template_pow<__int64, signed __int64, float>				(base, exponent); }
	static inline signed __int64			pow			(const signed __int64& base, const double&				exponent) { return template_pow<__int64, signed __int64, double>			(base, exponent); }
				  
	static inline signed __int64			pow			(const unsigned __int64& base, const signed __int8&		exponent) { return template_pow<__int64, unsigned __int64, signed __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const signed __int16&	exponent) { return template_pow<__int64, unsigned __int64, signed __int16>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const signed __int32&	exponent) { return template_pow<__int64, unsigned __int64, signed __int32>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const signed __int64&	exponent) { return template_pow<__int64, unsigned __int64, signed __int64>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const unsigned __int8&	exponent) { return template_pow<__int64, unsigned __int64, unsigned __int8>	(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const unsigned __int16&	exponent) { return template_pow<__int64, unsigned __int64, unsigned __int16>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const unsigned __int32&	exponent) { return template_pow<__int64, unsigned __int64, unsigned __int32>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const unsigned __int64&	exponent) { return template_pow<__int64, unsigned __int64, unsigned __int64>(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const float&				exponent) { return template_pow<__int64, unsigned __int64, float>			(base, exponent); }
	static inline signed __int64			pow			(const unsigned __int64& base, const double&			exponent) { return template_pow<__int64, unsigned __int64, double>			(base, exponent); }

	static inline double			pow			(const double& base, const signed __int8&		exponent)	{ return template_pow<double, double, signed __int8>	(base, exponent); }
	static inline double			pow			(const double& base, const signed __int16&		exponent)	{ return template_pow<double, double, signed __int16>	(base, exponent); }
	static inline double			pow			(const double& base, const signed __int32&		exponent)	{ return template_pow<double, double, signed __int32>	(base, exponent); }
	static inline double			pow			(const double& base, const signed __int64&		exponent)	{ return template_pow<double, double, signed __int64>	(base, exponent); }
	static inline double			pow			(const double& base, const unsigned __int8&		exponent)	{ return template_pow<double, double, unsigned __int8>	(base, exponent); }
	static inline double			pow			(const double& base, const unsigned __int16&	exponent)	{ return template_pow<double, double, unsigned __int16>	(base, exponent); }
	static inline double			pow			(const double& base, const unsigned __int32&	exponent)	{ return template_pow<double, double, unsigned __int32>	(base, exponent); }
	static inline double			pow			(const double& base, const unsigned __int64&	exponent)	{ return template_pow<double, double, unsigned __int64>	(base, exponent); }
	static inline double			pow			(const double& base, const float&				exponent)	{ return template_pow<double, double, float>			(base, exponent); }
	static inline double			pow			(const double& base, const double&				exponent)	{ return template_pow<double, double, double>			(base, exponent); }

	static inline double			pow			(const float& base, const signed __int8&		exponent)	{ return template_pow<double, float, signed __int8>		(base, exponent); }
	static inline double			pow			(const float& base, const signed __int16&		exponent)	{ return template_pow<double, float, signed __int16>	(base, exponent); }
	static inline double			pow			(const float& base, const signed __int32&		exponent)	{ return template_pow<double, float, signed __int32>	(base, exponent); }
	static inline double			pow			(const float& base, const signed __int64&		exponent)	{ return template_pow<double, float, signed __int64>	(base, exponent); }
	static inline double			pow			(const float& base, const unsigned __int8&		exponent)	{ return template_pow<double, float, unsigned __int8>	(base, exponent); }
	static inline double			pow			(const float& base, const unsigned __int16&		exponent)	{ return template_pow<double, float, unsigned __int16>	(base, exponent); }
	static inline double			pow			(const float& base, const unsigned __int32&		exponent)	{ return template_pow<double, float, unsigned __int32>	(base, exponent); }
	static inline double			pow			(const float& base, const unsigned __int64&		exponent)	{ return template_pow<double, float, unsigned __int64>	(base, exponent); }
	static inline double			pow			(const float& base, const float&				exponent)	{ return template_pow<double, float, float>				(base, exponent); }
	static inline double			pow			(const float& base, const double&				exponent)	{ return template_pow<double, float, double>			(base, exponent); }
	
	static inline unsigned __int64	faculty		(const signed   __int8& value)  { return template_faculty(value); }
	static inline unsigned __int64	faculty		(const signed   __int16& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty		(const signed   __int32& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty		(const signed   __int64& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty		(const unsigned __int8& value)  { return template_faculty(value); }
	static inline unsigned __int64	faculty		(const unsigned __int16& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty		(const unsigned __int32& value) { return template_faculty(value); }
	static inline unsigned __int64	faculty		(const unsigned __int64& value) { return template_faculty(value); }

	static inline signed __int8		abs			(const signed __int8& value) { return template_abs(value); }
	static inline signed __int16	abs			(const signed __int16& value) { return template_abs(value); }
	static inline signed __int32	abs			(const signed __int32& value) { return template_abs(value); }
	static inline signed __int64	abs			(const signed __int64& value)	{ return template_abs(value); }
	static inline float				abs			(const float& value)  { return template_abs(value); }
	static inline double			abs			(const double& value) { return template_abs(value); }
	
	static inline float				fract		(const float& value)  { return template_fract(value); }
	static inline double			fract		(const double& value) { return template_fract(value); }
	
	static inline float				round		(const float& value, const signed __int8& position)     { return template_round(value, position); }
	static inline float				round		(const float& value, const signed __int16& position)    { return template_round(value, position); }
	static inline float				round		(const float& value, const signed __int32& position)    { return template_round(value, position); }
	static inline float				round		(const float& value, const signed __int64& position)    { return template_round(value, position); }
	static inline float				round		(const float& value, const unsigned __int8& position)   { return template_round(value, position); }
	static inline float				round		(const float& value, const unsigned __int16& position)  { return template_round(value, position); }
	static inline float				round		(const float& value, const unsigned __int32& position)  { return template_round(value, position); }
	static inline float				round		(const float& value, const unsigned __int64& position)  { return template_round(value, position); }
	static inline double			round		(const double& value, const signed __int8& position)    { return template_round(value, position); }
	static inline double			round		(const double& value, const signed __int16& position)   { return template_round(value, position); }
	static inline double			round		(const double& value, const signed __int32& position)   { return template_round(value, position); }
	static inline double			round		(const double& value, const signed __int64& position)   { return template_round(value, position); }
	static inline double			round		(const double& value, const unsigned __int8& position)  { return template_round(value, position); }
	static inline double			round		(const double& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline double			round		(const double& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline double			round		(const double& value, const unsigned __int64& position) { return template_round(value, position); }

	static inline signed __int8			round(const signed __int8& value, const signed __int8& position) { return template_round(value, position); }
	static inline signed __int8			round(const signed __int8& value, const signed __int16& position) { return template_round(value, position); }
	static inline signed __int8			round(const signed __int8& value, const signed __int32& position) { return template_round(value, position); }
	static inline signed __int8			round(const signed __int8& value, const signed __int64& position) { return template_round(value, position); }
	static inline signed __int8			round(const signed __int8& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline signed __int8			round(const signed __int8& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline signed __int8			round(const signed __int8& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline signed __int8			round(const signed __int8& value, const unsigned __int64& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const signed __int8& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const signed __int16& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const signed __int32& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const signed __int64& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline signed __int16			round(const signed __int16& value, const unsigned __int64& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const signed __int8& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const signed __int16& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const signed __int32& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const signed __int64& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline signed __int32			round(const signed __int32& value, const unsigned __int64& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const signed __int8& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const signed __int16& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const signed __int32& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const signed __int64& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline signed __int64			round(const signed __int64& value, const unsigned __int64& position) { return template_round(value, position); }

	static inline unsigned __int8			round(const unsigned __int8& value, const signed __int8& position) { return template_round(value, position); }
	static inline unsigned __int8			round(const unsigned __int8& value, const signed __int16& position) { return template_round(value, position); }
	static inline unsigned __int8			round(const unsigned __int8& value, const signed __int32& position) { return template_round(value, position); }
	static inline unsigned __int8			round(const unsigned __int8& value, const signed __int64& position) { return template_round(value, position); }
	static inline unsigned __int8			round(const unsigned __int8& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline unsigned __int8			round(const unsigned __int8& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline unsigned __int8			round(const unsigned __int8& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline unsigned __int8			round(const unsigned __int8& value, const unsigned __int64& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const signed __int8& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const signed __int16& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const signed __int32& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const signed __int64& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline unsigned __int16			round(const unsigned __int16& value, const unsigned __int64& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const signed __int8& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const signed __int16& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const signed __int32& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const signed __int64& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline unsigned __int32			round(const unsigned __int32& value, const unsigned __int64& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const signed __int8& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const signed __int16& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const signed __int32& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const signed __int64& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const unsigned __int8& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const unsigned __int16& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const unsigned __int32& position) { return template_round(value, position); }
	static inline unsigned __int64			round(const unsigned __int64& value, const unsigned __int64& position) { return template_round(value, position); }


	static inline float				floor		(const float& value, const signed __int8& position)     { return template_floor(value, position); }
	static inline float				floor		(const float& value, const signed __int16& position)    { return template_floor(value, position); }
	static inline float				floor		(const float& value, const signed __int32& position)    { return template_floor(value, position); }
	static inline float				floor		(const float& value, const signed __int64& position)    { return template_floor(value, position); }
	static inline float				floor		(const float& value, const unsigned __int8& position)   { return template_floor(value, position); }
	static inline float				floor		(const float& value, const unsigned __int16& position)  { return template_floor(value, position); }
	static inline float				floor		(const float& value, const unsigned __int32& position)  { return template_floor(value, position); }
	static inline float				floor		(const float& value, const unsigned __int64& position)  { return template_floor(value, position); }
	static inline double			floor		(const double& value, const signed __int8& position)    { return template_floor(value, position); }
	static inline double			floor		(const double& value, const signed __int16& position)   { return template_floor(value, position); }
	static inline double			floor		(const double& value, const signed __int32& position)   { return template_floor(value, position); }
	static inline double			floor		(const double& value, const signed __int64& position)   { return template_floor(value, position); }
	static inline double			floor		(const double& value, const unsigned __int8& position)  { return template_floor(value, position); }
	static inline double			floor		(const double& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline double			floor		(const double& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline double			floor		(const double& value, const unsigned __int64& position) { return template_floor(value, position); }

	static inline signed __int8				floor(const signed __int8& value, const signed __int8& position) { return template_floor(value, position); }
	static inline signed __int8				floor(const signed __int8& value, const signed __int16& position) { return template_floor(value, position); }
	static inline signed __int8				floor(const signed __int8& value, const signed __int32& position) { return template_floor(value, position); }
	static inline signed __int8				floor(const signed __int8& value, const signed __int64& position) { return template_floor(value, position); }
	static inline signed __int8				floor(const signed __int8& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline signed __int8				floor(const signed __int8& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline signed __int8				floor(const signed __int8& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline signed __int8				floor(const signed __int8& value, const unsigned __int64& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const signed __int8& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const signed __int16& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const signed __int32& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const signed __int64& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline signed __int16			floor(const signed __int16& value, const unsigned __int64& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const signed __int8& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const signed __int16& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const signed __int32& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const signed __int64& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline signed __int32			floor(const signed __int32& value, const unsigned __int64& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const signed __int8& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const signed __int16& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const signed __int32& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const signed __int64& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline signed __int64			floor(const signed __int64& value, const unsigned __int64& position) { return template_floor(value, position); }

	static inline unsigned __int8				floor(const unsigned __int8& value, const signed __int8& position) { return template_floor(value, position); }
	static inline unsigned __int8				floor(const unsigned __int8& value, const signed __int16& position) { return template_floor(value, position); }
	static inline unsigned __int8				floor(const unsigned __int8& value, const signed __int32& position) { return template_floor(value, position); }
	static inline unsigned __int8				floor(const unsigned __int8& value, const signed __int64& position) { return template_floor(value, position); }
	static inline unsigned __int8				floor(const unsigned __int8& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline unsigned __int8				floor(const unsigned __int8& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline unsigned __int8				floor(const unsigned __int8& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline unsigned __int8				floor(const unsigned __int8& value, const unsigned __int64& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const signed __int8& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const signed __int16& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const signed __int32& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const signed __int64& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline unsigned __int16			floor(const unsigned __int16& value, const unsigned __int64& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const signed __int8& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const signed __int16& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const signed __int32& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const signed __int64& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline unsigned __int32			floor(const unsigned __int32& value, const unsigned __int64& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const signed __int8& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const signed __int16& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const signed __int32& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const signed __int64& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const unsigned __int8& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const unsigned __int16& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const unsigned __int32& position) { return template_floor(value, position); }
	static inline unsigned __int64			floor(const unsigned __int64& value, const unsigned __int64& position) { return template_floor(value, position); }


	//ceil shut also work above the komma floor and round also
	static inline float				ceil		(const float& value, const signed __int8& position)		{ return template_ceil(value, position); }
	static inline float				ceil		(const float& value, const signed __int16& position)	{ return template_ceil(value, position); }
	static inline float				ceil		(const float& value, const signed __int32& position)	{ return template_ceil(value, position); }
	static inline float				ceil		(const float& value, const signed __int64& position)	{ return template_ceil(value, position); }
	static inline float				ceil		(const float& value, const unsigned __int8& position)   { return template_ceil(value, position); }
	static inline float				ceil		(const float& value, const unsigned __int16& position)  { return template_ceil(value, position); }
	static inline float				ceil		(const float& value, const unsigned __int32& position)  { return template_ceil(value, position); }
	static inline float				ceil		(const float& value, const unsigned __int64& position)  { return template_ceil(value, position); }
	
	static inline double			ceil		(const double& value, const signed __int8& position)    { return template_ceil(value, position); }
	static inline double			ceil		(const double& value, const signed __int16& position)   { return template_ceil(value, position); }
	static inline double			ceil		(const double& value, const signed __int32& position)   { return template_ceil(value, position); }
	static inline double			ceil		(const double& value, const signed __int64& position)   { return template_ceil(value, position); }
	static inline double			ceil		(const double& value, const unsigned __int8& position)  { return template_ceil(value, position); }
	static inline double			ceil		(const double& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline double			ceil		(const double& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline double			ceil		(const double& value, const unsigned __int64& position) { return template_ceil(value, position); }
	
	static inline signed __int8			ceil		(const signed __int8& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline signed __int8			ceil		(const signed __int8& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline signed __int8			ceil		(const signed __int8& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline signed __int8			ceil		(const signed __int8& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline signed __int8			ceil		(const signed __int8& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline signed __int8			ceil		(const signed __int8& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline signed __int8			ceil		(const signed __int8& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline signed __int8			ceil		(const signed __int8& value, const unsigned __int64& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline signed __int16			ceil		(const signed __int16& value, const unsigned __int64& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline signed __int32			ceil		(const signed __int32& value, const unsigned __int64& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline signed __int64			ceil		(const signed __int64& value, const unsigned __int64& position) { return template_ceil(value, position); }

	static inline unsigned __int8				ceil(const unsigned __int8& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int8				ceil(const unsigned __int8& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int8				ceil(const unsigned __int8& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int8				ceil(const unsigned __int8& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline unsigned __int8				ceil(const unsigned __int8& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int8				ceil(const unsigned __int8& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int8				ceil(const unsigned __int8& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int8				ceil(const unsigned __int8& value, const unsigned __int64& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int16			ceil(const unsigned __int16& value, const unsigned __int64& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int32			ceil(const unsigned __int32& value, const unsigned __int64& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const signed __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const signed __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const signed __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const signed __int64& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const unsigned __int8& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const unsigned __int16& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const unsigned __int32& position) { return template_ceil(value, position); }
	static inline unsigned __int64			ceil(const unsigned __int64& value, const unsigned __int64& position) { return template_ceil(value, position); }


	static inline unsigned int		crossSum	(const signed __int8& value)	{ return template_crossSum(value); }
	static inline unsigned int		crossSum	(const signed __int16& value)	{ return template_crossSum(value); }
	static inline unsigned int		crossSum	(const signed __int32& value)	{ return template_crossSum(value); }
	static inline unsigned int		crossSum	(const signed __int64& value)	{ return template_crossSum(value); }
	static inline unsigned int		crossSum	(const unsigned __int8& value)	{ return template_crossSum(value); }
	static inline unsigned int		crossSum	(const unsigned __int16& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum	(const unsigned __int32& value) { return template_crossSum(value); }
	static inline unsigned int		crossSum	(const unsigned __int64& value) { return template_crossSum(value); }

	static inline unsigned int		countDigits (const unsigned __int8& value)	{ return template_countDigits(value); }
	static inline unsigned int		countDigits (const unsigned __int16& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits (const unsigned __int32& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits (const unsigned __int64& value) { return template_countDigits(value); }
	static inline unsigned int		countDigits	(const signed __int8& value)	{ return template_countDigits(value); }
	static inline unsigned int		countDigits	(const signed __int16& value)	{ return template_countDigits(value); }
	static inline unsigned int		countDigits	(const signed __int32& value)	{ return template_countDigits(value); }
	static inline unsigned int		countDigits	(const signed __int64& value)	{ return template_countDigits(value); }

	static inline int				sign		(const __int8& value)	{ return template_sign(value); }
	static inline int				sign		(const __int16& value)	{ return template_sign(value); }
	static inline int				sign		(const __int32& value)	{ return template_sign(value); }
	static inline int				sign		(const __int64& value)	{ return template_sign(value); }
	static inline int				sign		(const float& value)	{ return template_sign(value); }
	static inline int				sign		(const double& value)	{ return template_sign(value); }
};

#endif /* Math_hpp */
