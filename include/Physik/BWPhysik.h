//
//  BWPhysik.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef BWPHYSIK_H
#define BWPHYSIK_H
#include "../Math/Vector3.h"



class BWPhysik
{
public:
	/*
		gravity = the gravity of the envioroment in m/s^2
		time	= time of fall in s
		returns the distance of fall in time
	*/
	static double FreeFall(double gravity, double time);

	/*
		direction = the vector which have to be refected
		normal	= the normal of the reflected surface

		returns the refected vector
	*/
	static Vector3 Reflect(Vector3 direction, Vector3 normal);
};

#endif