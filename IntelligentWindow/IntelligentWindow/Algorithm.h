// Algorithm.h

#ifndef _ALGORITHM_h
#define _ALGORITHM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Algorithm
{
public:
	
	double compute_d(float t, float h);

	bool American(float t, float h);

	bool ASHRAE(float t, float h);

	bool A_A_all_in(float t, float h);

	

private:
	double C1 = -(5.6745359E3);
	double C2 = (6.3925247E0);
	double C3 = -(9.6778430E-3);
	double C4 = (6.2215701E-7);
	double C5 = (2.0747825E-9);
	double C6 = -(9.4840240E-13);
	double C7 = (4.1635019E0);

};

extern Algorithm Algorithm0;

#endif

