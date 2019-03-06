#pragma once

#include "BWDouble.h"
#include <iostream>
#include <string>

class BWFloat
{
private:
	int m_value = 0;

public:
	BWFloat(std::string floatString);
	BWFloat(const BWFloat&);
	~BWFloat();

	operator BWDouble();
	operator float();
	operator double();
	operator int();

	BWDouble& operator+=(const BWDouble&);
	BWDouble& operator-=(const BWDouble&);
	BWDouble& operator*=(const BWDouble&);
	BWDouble& operator/=(const BWDouble&);
	BWDouble operator+(const BWDouble&);
	BWDouble operator-(const BWDouble&);
	BWDouble operator*(const BWDouble&);
	BWDouble operator/(const BWDouble&);

	BWFloat& operator+=(const BWFloat&);
	BWFloat& operator-=(const BWFloat&);
	BWFloat& operator*=(const BWFloat&);
	BWFloat& operator/=(const BWFloat&);
	BWFloat operator+(const BWFloat&);
	BWFloat operator-(const BWFloat&);
	BWFloat operator*(const BWFloat&);
	BWFloat operator/(const BWFloat&);

	BWFloat& operator+=(const int&);
	BWFloat& operator-=(const int&);
	BWFloat& operator*=(const int&);
	BWFloat& operator/=(const int&);
	BWFloat operator+(const int&);
	BWFloat operator-(const int&);
	BWFloat operator*(const int&);
	BWFloat operator/(const int&);

	BWFloat& operator+=(const float&);
	BWFloat& operator-=(const float&);
	BWFloat& operator*=(const float&);
	BWFloat& operator/=(const float&);
	BWFloat operator+(const float&);
	BWFloat operator-(const float&);
	BWFloat operator*(const float&);
	BWFloat operator/(const float&);

	BWFloat& operator+=(const double&);
	BWFloat& operator-=(const double&);
	BWFloat& operator*=(const double&);
	BWFloat& operator/=(const double&);
	BWFloat operator+(const double&);
	BWFloat operator-(const double&);
	BWFloat operator*(const double&);
	BWFloat operator/(const double&);




};

