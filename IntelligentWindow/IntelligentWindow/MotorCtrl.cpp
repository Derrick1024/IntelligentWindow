// 
// 
// 

#include "MotorCtrl.h"
#include "ValueFunDefine.h"

int MotorCtrl::MotorCw(void)
{
	MotorStop();
	delay(30);
	digitalWrite(RelayPin0, LOW);
	digitalWrite(RelayPin1, HIGH);

	return 1;
}

int MotorCtrl::MotorCcw(void)
{
	MotorStop();
	delay(30);
	digitalWrite(RelayPin0, HIGH);
	digitalWrite(RelayPin1, LOW);

	return -1;
}

int MotorCtrl::MotorStop(void)
{
	digitalWrite(RelayPin0, HIGH);
	digitalWrite(RelayPin1, HIGH);

	return 0;
}

int MotorCtrl::MotorStateCtrl(int state)
{
	if (state == 0)
	{
		MotorStop();
	}
	if (state == 1)
	{
		MotorCw();
	}
	if (state == -1)
	{
		MotorCcw();
	}

	return state;
}
