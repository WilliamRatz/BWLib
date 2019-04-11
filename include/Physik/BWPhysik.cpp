#include "BWPhysik.h"
#include "../Inc_BWMath.h"



double BWPhysik::FreeFall(double p_gravity, double p_time)
{
	return (p_gravity * BWMath::pow(p_time, 2)) / 2;
}

Vector3 BWPhysik::Reflect(Vector3 p_direction, Vector3 p_normal)
{
	return (p_direction - (p_normal * 2 * (Vector3::dot(p_direction, p_normal))));
}
