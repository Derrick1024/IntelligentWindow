// Beep.h

#ifndef _BEEP_h
#define _BEEP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Beep
{
public:
	int BeepSwtich(int state);

	int BeepOn(void);

	int BeepOff(void);

private:

};

extern Beep Beep0;


#endif

