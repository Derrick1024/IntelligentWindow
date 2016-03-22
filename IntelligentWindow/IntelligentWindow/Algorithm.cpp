// 
// 
// 

#include "Algorithm.h"
#include "math.h"

double Algorithm::compute_d(float t, float h)
{
	double T = t + 273.15;
	double pws = exp(C1 / T + C2 + C3*T + C4*pow(T, 2) + C5*pow(T, 3) + C6*pow(T, 4) + C7*log(T));
	double pw = pws*h;
	double d = 0.621945 * 101325 / (101325 - pw);

	return d;
}

bool Algorithm::American(float t, float h)
{
	double d = compute_d(t, h);

	if ((t >= 24) && (t <= 26.8) && (d >= (-0.002*t + 0.0568)) && (d <= (-0.024286*t + 0.0751)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool Algorithm::ASHRAE(float t, float h)
{
	double d = compute_d(t, h);

	if ((d >= 0.0044) && (d <= 0.012) && (t >= (d - 0.2172) / (-(9.5e-3))) && (t <= (d - 0.1176) / (-(4.2e-3))))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
bool Algorithm::A_A_all_in(float t, float h)
{
	if (Algorithm::ASHRAE(t, h) && Algorithm::ASHRAE(t, h))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}









