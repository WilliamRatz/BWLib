#pragma once
class BWPhysik
{
public:
	BWPhysik();
	~BWPhysik();

	/*
		v1 = start speed in		m/s
		v2 = end speed in		m/s

		t1 = start time in		s
		t2 = end time in		s

		return in m/s^2
	*/
	static double CalcAccelaration(double v1, double t1, double v2, double t2);
};

