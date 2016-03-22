#ifndef _VAlUEFUNDEFINE_h
#define _VAlUEFUNDEFINE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/**********************************
�������ŵĶ���
***********************************/

//DHT11
#define DHT11Pin 45
#define DHTTYPE DHT11
//moter
#define MotorPin0 3
#define MotorPin1 4
#define MotorPwm 5
//relay
#define RelayPin0 6
#define RelayPin1 7
//LimitSwitch
#define LimitSwitchPin0 8
#define LimitSwitchPin1 9
#define LimitSwitchPin2 10
//servo
#define ServoPin0 11
#define ServoPin1 12
//rain
#define RainInPin0 A0

// д���ļ�ʱҪ��.h�ļ�����extern������Ҫ�õ��������
// �����������ĵط��Ͳ�����ִ�����

class SensorData
{
public:
	float PM2_5;
	float TempOut;
	float TempIn;
	float HumiOut;
	float HumiIn;
	int RainOut;

private:

};

class CtrlData
{
public:
	int WinState;

private:

};

extern SensorData SensorData0;
extern CtrlData CtrlData0;

#endif

