#ifndef _VAlUEFUNDEFINE_h
#define _VAlUEFUNDEFINE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/**********************************
器件引脚的定义
***********************************/

//DHT11
#define DHT11Pin 45
#define DHTTYPE DHT11
//moter
#define MotorPin0 32
#define MotorPin1 33
#define MotorPwm 34
//relay
#define RelayPin0 42
#define RelayPin1 43
//LimitSwitch
#define LimitSwitchPin0 25//close
#define LimitSwitchPin1 24//open
#define LimitSwitchPin2 23
//servo
#define ServoPin0 11
#define ServoPin1 12
//Beep
#define BeepPin 44
//rain
#define RainInPin0 A0

// 写库文件时要在.h文件里用extern来声明要用到的类变量
// 这样在其他的地方就不会出现错误了

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
	int WinState=0;
	float SetTemperature=28.0;
	int AutoCtrl=1;

private:

};
class SetData
{
public:
	float PollutantThreshold = 150.0;
	float MinTemp = 24.0;
	float MaxTemp = 28.0;
private:

};
extern SensorData SensorData0;
extern CtrlData CtrlData0;
extern SetData SetData0;
#endif

