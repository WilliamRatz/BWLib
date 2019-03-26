#include "BWPhysik.h"



BWPhysik::BWPhysik()
{
}


BWPhysik::~BWPhysik()
{
}

double BWPhysik::CalcAccelaration(double v1, double t1, double v2, double t2)
{
	return (v2 - v1) / (t2 - t1);
}
