#include "BWMath.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix.h"


const double BWMath::PI = 3.14159265358979323;
const double BWMath::TAU = 6.28318530717958647;
const double BWMath::EULER = 2.71828182845904523;
const double BWMath::toDeg = BWMath::PI / 180;
const double BWMath::toRad = 180 / BWMath::PI;

double BWMath::Sqrt(const double& p_value) {

	double result;
	result = (p_value + 1) / 2;
	for (int i = 0; i < 5; ++i) {
		result = 0.5*(result + p_value / result);
	}
	return result;
}
double BWMath::Sin(const double& p_angle) {

	double angleRad = p_angle * toRad;
	short size = (int)angleRad % 180;
	double result = size + BWMath::fract(angleRad);
	result *= toDeg;
	result = result - BWMath::pow(result, 3) / BWMath::faculty(3) + BWMath::pow(result, 5) / BWMath::faculty(5) - BWMath::pow(result, 7) / BWMath::faculty(7) + BWMath::pow(result, 9) / BWMath::faculty(9);


	//works wenn p_angle was multiplied with toDeg
	if ((int)angleRad % 360 > 180) {
		result *= -1;

	}

	return BWMath::floor(result, 4);
}
double BWMath::Cos(const double& p_angle) {

	double angleRad = p_angle * toRad;
	double result = ((int)angleRad % 180) + BWMath::fract(angleRad);
	result *= toDeg;
	result = (double)1 - (BWMath::pow(result, 2) / BWMath::faculty(2)) + (BWMath::pow(result, 4) / BWMath::faculty(4)) - (BWMath::pow(result, 6) / BWMath::faculty(6)) + (BWMath::pow(result, 8) / BWMath::faculty(8));
	/*if ((int)(p_angle) % 270 > 90) {
		result = ((result*result)/result)* -1;
	}else
	{
		result = ((result*result)/result);
	}*/



	return BWMath::floor(result, 4);
}
double BWMath::Tan(const double& p_angle) {

	return BWMath::floor(BWMath::Sin(p_angle) / BWMath::Cos(p_angle), 4);
}

double BWMath::ArcSin(const double& p_angle) {

	return 3.3;
}
double BWMath::ArcCos(const double& p_angle) {

	return 3.3;
}
double BWMath::ArcTan(const double& p_angle) {
	//TODO

	short size = (int)p_angle % 180;
	double result = size + BWMath::fract(p_angle);
	result *= toDeg;
	result = result - (BWMath::pow(result, 3) * 1 / 3) + (BWMath::pow(result, 5) * 1 / 5) - (BWMath::pow(result, 7) * 1 / 7) + (BWMath::pow(result, 9) * 1 / 9);
	result *= BWMath::sign(size);

	return BWMath::floor(result, 4);
}

double BWMath::pow(const double& p_base, const double& p_exponent)
{
	double result = 1;
	for (int i = 0; i < p_exponent; ++i)
	{
		result *= p_base;
	}

	return result;
}
std::size_t BWMath::faculty(const std::size_t& p_value)
{
	if (p_value < 0) {
		throw std::out_of_range("no negativ faculty");
	}
	std::size_t result = 1;

	for (std::size_t i = 2; i <= p_value; ++i)
	{
		result *= i;
	}

	return result;
}
std::size_t BWMath::Abs(const int & p_value)
{
	if (p_value >= 0)
		return p_value;

	return p_value -2* p_value;
}
double BWMath::fract(const double& p_value)
{
	return p_value - (int)p_value;
}

double BWMath::round(const double& p_value, const int& p_position)
{
	double temp = p_value * BWMath::pow(10, p_position + 1);
	temp = static_cast<int>(temp);
	temp -= static_cast<int>(p_value * BWMath::pow(10, p_position)) * 10;

	if (temp > 4)
	{
		return BWMath::ceil(p_value, p_position);
	}
	else
	{
		return BWMath::floor(p_value, p_position);
	}
}
double BWMath::floor(const double& p_value, const int& p_position)
{
	double temp = p_value * BWMath::pow(10, p_position);
	temp = static_cast<int>(temp);
	temp *= 10;
	temp /= BWMath::pow(10, p_position + 1);

	return temp;
}
double BWMath::ceil(const double& p_value, const int& p_position)
{
	double temp = p_value * BWMath::pow(10, p_position);
	temp = static_cast<int>(temp);
	temp *= 10;
	temp += 10;
	temp /= BWMath::pow(10, p_position + 1);

	return temp;
}

int BWMath::crossSum(const std::size_t& p_value)
{
	if (p_value == NULL)
		return 0;

	std::size_t tempValue = p_value;
	int result = 0;

	while (tempValue > 0) {
		result += tempValue % 10;
		tempValue /= 10;
	}
	return result;
}

int BWMath::countDigits(const std::size_t & p_value)
{
	if (p_value == NULL)
		return 0;

	std::size_t tempValue = p_value;
	int result = 0;

	while (tempValue > 9) {
		tempValue /= 10;
		++result;
	}
	++result;

	return result;
}

int  BWMath::sign(const float& p_value)
{
	//return (p_value > 0) - (p_value < 0);
	return (p_value > 0) ? 1 : ((p_value < 0) ? -1 : 0);
}

int BWMath::sign(const int& p_value)
{
	return (p_value > 0) ? 1 : ((p_value < 0) ? -1 : 0);
}






