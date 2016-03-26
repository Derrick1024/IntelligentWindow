// 
// 
// 
#include "ValueFunDefine.h"
#include "Algorithm.h"
#include "math.h"

double Algorithm::compute_pws(float t, float h)
{
	double T = t + 273.15;
	double pws = exp(C1 / T + C2 + C3*T + C4*pow(T, 2) + C5*pow(T, 3) + C6*pow(T, 4) + C7*log(T));

	return pws;
}
double Algorithm::compute_pw(float t, float h)
{
	h = h / 100;
	double pw=compute_pws(t, h)*h;

	return pw;
}
double Algorithm::compute_d(float t, float h)
{
	double d = 0.621945 * 101325 / (101325 - compute_pw(t, h));

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

String Algorithm::AQI_Evaluate(float PM2_5)
{
	if (SensorData0.PM2_5 <= 50)
	{
		return "A";
	}
	else if (SensorData0.PM2_5 <= 100)
	{
		return "B";
	}
	else if (SensorData0.PM2_5 <= 150)
	{
		return "C";
	}
	else
	{
		return "D";
	}

}

int Algorithm::Window_Evaluate(void)
{
	if (SensorData0.PM2_5 < 150)
	{
		if (compute_pw(SensorData0.TempOut, SensorData0.HumiOut) <= compute_pws(SensorData0.TempIn, SensorData0.HumiIn))
		{
			if (A_A_all_in(SensorData0.TempOut, SensorData0.HumiOut) == 1)
			{
				return 1;
			}
			else if (A_A_all_in(SensorData0.TempIn, SensorData0.HumiIn) == 1)
			{
				return 0;
			}
			else if ((SensorData0.TempIn < SensorData0.TempOut))
			{
				if (SensorData0.TempIn < SetData0.MinTemp)
				{
					return 1;
				}
				return 0;
				
			}
			else if (SensorData0.TempIn > SensorData0.TempOut)
			{
				if (SensorData0.TempIn > SetData0.MaxTemp)
				{
					return 1;
				}
				return 0;
			}
			else
			{
				return 0;
			}
				
		}
		else
		{
			return 0;
		}
	}
	else 
	{
		return 0;
	}
}









