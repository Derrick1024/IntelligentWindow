// MotorCtrl.h

#ifndef _MOTORCTRL_h
#define _MOTORCTRL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class MotorCtrl
{
public:
	int MotorCw(void);
	int MotorCcw(void);
	int MotorStop(void);
	int MotorStateCtrl(int state);

private:

};

extern MotorCtrl MotorCtrl0;

#endif

