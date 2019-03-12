//
//  Math.h
//  MathLibery
//
//  Created by William Ratz on 18.09.18.
//  Copyright © 2018 William Ratz. All rights reserved.
//
#ifndef Math_H
#define Math_H

class BWMath {

public:
	
	static double			Sqrt		(const double& value);
	static double			Sin			(const double& angle);
	static double			Cos			(const double& angle);
	static double			Tan			(const double& angle);

	static double			ArcSin		(const double& angle);
	static double			ArcCos		(const double& angle);
	static double			ArcTan		(const double& angle);

	static double			pow			(const double& base, const double& exponent);
	static unsigned int		faculty		(const unsigned int& value);
	static unsigned int		Abs			(const int& value);

	static double			fract		(const double& value);
	static double			round		(const double& value, const int& position);
	static double			floor		(const double& value, const int& position);
	static double			ceil		(const double& value, const int& position);
	static unsigned int		crossSum	(const unsigned int& value);
	static unsigned int		countDigits	(const unsigned int& value);
	
	static int				sign		(const float& value);
	static int				sign		(const int& value);

	static double			PI_Calc		();
	static double			E_Calc		();

	static const double		PI;
	static const double		TAU;
	static const double		EULER;

	static const double		toDeg;
	static const double		toRad;
};



#endif /* Math_hpp */
