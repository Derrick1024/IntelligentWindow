// 
// 
// 

#include "Beep.h"
#include "ValueFunDefine.h"

int Beep::BeepSwtich(int state)
{
	if (state == 1)
	{
		digitalWrite(BeepPin, HIGH);
	}
	if (state == 0)
	{
		digitalWrite(BeepPin, LOW);
	}
	return 1;
}

int Beep::BeepOn(void)
{
	digitalWrite(BeepPin, HIGH);
	return 1;
}

int Beep::BeepOff(void)
{
	digitalWrite(BeepPin, LOW);
	return 1;
}
