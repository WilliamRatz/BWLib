#include "BWPhysik3D.h"


Vector3 BWPhysik3D::Reflect(Vector3& p_direction, Vector3& p_normal)
{
	return (p_direction - (p_normal * 2 * (Vector3::dot(p_direction, p_normal))));
}

Vector3 BWPhysik3D::PosToVelo(Vector3& p_position, double& p_time)
{
	return Vector3(p_position / p_time);
}
Vector3 BWPhysik3D::PosToAccel(Vector3& p_position, double& p_time)
{
	return Vector3((p_position / p_time) / p_time);
}
Vector3 BWPhysik3D::PosToMomentum(Vector3& p_position, double& p_time, double& p_mass)
{
	Vector3 tempVec(BWPhysik3D::PosToVelo(p_position, p_time));
	return Vector3(BWPhysik3D::VeloToMomentum(tempVec, p_mass));
}
Vector3 BWPhysik3D::PosToForce(Vector3& p_position, double& p_time, double& p_mass)
{
	Vector3 tempVec(BWPhysik3D::PosToAccel(p_position, p_time));
	return Vector3(BWPhysik3D::AccelForce(tempVec, p_mass));
}

Vector3 BWPhysik3D::VeloToPos(Vector3& p_velocity, Vector3& p_startPosition, double& p_time)
{
	return Vector3((p_velocity * p_time) + p_startPosition);
}
Vector3 BWPhysik3D::VeloToAccel(Vector3& p_velocity, double& p_time)
{
	return Vector3(p_velocity / p_time);
}
Vector3 BWPhysik3D::VeloToMomentum(Vector3& p_velocity, double& p_mass)
{
	return Vector3(p_velocity * p_mass);
}
Vector3 BWPhysik3D::VeloToForce(Vector3& p_velocity, double& p_mass, double& p_time)
{
	Vector3 tempVec(BWPhysik3D::VeloToMomentum(p_velocity, p_mass));
	return Vector3(BWPhysik3D::MomentumToForce(tempVec, p_time));
}

Vector3 BWPhysik3D::AccelToPos(Vector3& p_acceleration, Vector3& p_startVelocity, Vector3& p_startPosition, double& p_time)
{
	return Vector2((p_acceleration / 2) * (p_time *p_time) + p_startVelocity * p_time + p_startPosition);
}
Vector3 BWPhysik3D::AccelToVelo(Vector3& p_acceleration, Vector3& p_startVelocity, double& p_time)
{
	return Vector2(p_acceleration * p_time + p_startVelocity);
}
Vector3 BWPhysik3D::AccelMomentum(Vector3& p_acceleration, Vector3& p_startVelocity, double& p_time, double& p_mass)
{
	Vector3 tempVec(BWPhysik3D::AccelToVelo(p_acceleration, p_startVelocity, p_time));
	return Vector3(BWPhysik3D::VeloToMomentum(tempVec, p_mass));
}
Vector3 BWPhysik3D::AccelForce(Vector3& p_acceleration, double& p_mass)
{
	return Vector3(p_acceleration * p_mass);
}

Vector3 BWPhysik3D::MomentumToPos(Vector3& p_momentum, double& p_mass, Vector3& p_startPosition, double& p_time)
{
	Vector3 tempVec(BWPhysik3D::MomentumToVelo(p_momentum, p_mass));
	return Vector3(BWPhysik3D::VeloToPos(tempVec, p_startPosition, p_time));
}
Vector3 BWPhysik3D::MomentumToVelo(Vector3& p_momentum, double& p_mass)
{
	return Vector3(p_momentum / p_mass);
}
Vector3 BWPhysik3D::MomentumToAccel(Vector3& p_momentum, double& p_mass, double& p_time)
{
	Vector3 tempVec(BWPhysik3D::MomentumToVelo(p_momentum, p_mass));
	return Vector3(BWPhysik3D::VeloToAccel(tempVec, p_time));
}
Vector3 BWPhysik3D::MomentumToForce(Vector3& p_momentum, double& p_time)
{
	return Vector3(p_momentum / p_time);
}
Vector3 BWPhysik3D::MomentumToMass(Vector3& p_momentum, Vector3& p_acceleration, double& p_time)
{
	Vector3 tempVec(BWPhysik3D::MomentumToForce(p_momentum, p_time));
	return Vector3(BWPhysik3D::ForceToMass(tempVec, p_acceleration));
}

Vector3 BWPhysik3D::ForceToPos(Vector3& p_force, Vector3& p_startVelocity, Vector3& p_startPosition, double& p_mass, double& p_time)
{
	Vector3 tempVec(BWPhysik3D::ForceToAccel(p_force, p_mass));
	return Vector3(BWPhysik3D::AccelToPos(tempVec, p_startVelocity, p_startPosition, p_time));
}
Vector3 BWPhysik3D::ForceToVelo(Vector3& p_force, Vector3& p_startVelocity, double& p_mass, double& p_time)
{
	Vector3 tempVec(BWPhysik3D::ForceToAccel(p_force, p_mass));
	return Vector3(BWPhysik3D::AccelToVelo(tempVec, p_startVelocity, p_time));
}
Vector3 BWPhysik3D::ForceToAccel(Vector3& p_force, double& p_mass)
{
	return Vector3(p_force / p_mass);
}
Vector3 BWPhysik3D::ForceToMomentum(Vector3& p_force, double& p_time)
{
	return Vector3(p_force * p_time);
}
Vector3 BWPhysik3D::ForceToMass(Vector3& p_force, Vector3& p_acceleration)
{
	return Vector3(p_force / p_acceleration);
}
