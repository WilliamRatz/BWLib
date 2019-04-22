//
//  BWPhysik.h
//  BWLib
//
//  Created by William Ratz on 11.04.19
//  Copyright © 2019 William Ratz. All rights reserved.
//

#ifndef BWPHYSIK3D_H
#define BWPHYSIK3D_H
#include "BWPhysik.h"


class BWPhysik3D : public BWPhysik
{
public:

	static Vector3 PosToVelo(Vector3& position, double& time);
	static Vector3 PosToAccel(Vector3& position, double& time);
	static Vector3 PosToMomentum(Vector3& position, double& time, double& mass);
	static Vector3 PosToForce(Vector3& position, double& time, double& mass);

	static Vector3 VeloToPos(Vector3& velocity, Vector3& startPosition, double& time);
	static Vector3 VeloToAccel(Vector3& velocity, double& time);
	static Vector3 VeloToMomentum(Vector3& velocity, double& mass);
	static Vector3 VeloToForce(Vector3& velocity, double& mass, double& time);

	static Vector3 AccelToPos(Vector3& acceleration, Vector3& startVelocity, Vector3& startPosition, double& time);
	static Vector3 AccelToVelo(Vector3& acceleration, Vector3& startVelocity, double& time);
	static Vector3 AccelMomentum(Vector3& acceleration, Vector3& startVelocity, double& time, double& mass);
	static Vector3 AccelForce(Vector3& acceleration, double& mass);

	static Vector3 MomentumToPos(Vector3& momentum, double& mass, Vector3& startPosition, double& time); //maybe startVelocity 
	static Vector3 MomentumToVelo(Vector3& momentum, double& mass);
	static Vector3 MomentumToAccel(Vector3& momentum, double& mass, double& time); //maybe startVelocity , startAcceleration
	static Vector3 MomentumToForce(Vector3& momentum, double& time);
	static Vector3 MomentumToMass(Vector3& p_momentum, Vector3& p_acceleration, double& p_time);

	static Vector3 ForceToPos(Vector3& force, Vector3& startVelocity, Vector3& startPosition, double& mass, double& time);//maybe startAcceleration
	static Vector3 ForceToVelo(Vector3& force, Vector3& startVelocity, double& mass, double& time); //maybe startAcceleration
	static Vector3 ForceToAccel(Vector3& force, double& mass);
	static Vector3 ForceToMomentum(Vector3& force, double& time);
	static Vector3 ForceToMass(Vector3& force, Vector3& acceleration);

	/*
		direction = the vector which have to be refected
		normal = the normal of the reflected surface

		returns the refected vector
	*/
	static Vector3 Reflect(Vector3& direction, Vector3& normal);
};

#endif