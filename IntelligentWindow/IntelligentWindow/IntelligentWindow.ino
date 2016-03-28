/*
 Name:		IntelligentWindow.ino
 Created:	2016/3/14 22:00:22
 Author:	ycg1024
*/

#include "MotorCtrl.h"
#include <EEPROM.h>
#include "Beep.h"
#include "UsartTask.h"
#include "Algorithm.h"
#include <DHT.h>
#include <Servo.h>
#include "ValueFunDefine.h"


SensorData SensorData0;
CtrlData CtrlData0;
SetData SetData0;
DHT dht(DHT11Pin, DHTTYPE);
Servo myservo0;
Servo myservo1;
Usart_Task Usart0_Task;
Usart_Task Usart1_Task;
Usart_Task Usart2_Task;
Usart_Task Usart3_Task;
Algorithm Algorithm0;
Beep Beep0;
MotorCtrl MotorCtrl0;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(MotorPin0, OUTPUT);
	pinMode(MotorPin1, OUTPUT);
	pinMode(MotorPwm, OUTPUT);
	pinMode(RelayPin0, OUTPUT);
	digitalWrite(RelayPin0, HIGH);
	pinMode(RelayPin1, OUTPUT);
	digitalWrite(RelayPin1, HIGH);
	pinMode(BeepPin, OUTPUT);
	
	pinMode(LimitSwitchPin0, INPUT_PULLUP);
	pinMode(LimitSwitchPin1, INPUT_PULLUP);
	pinMode(LimitSwitchPin2, INPUT_PULLUP);

	Serial.begin(115200); // 调试用
	Serial1.begin(115200); // 与屏幕的通信
	Serial2.begin(2400); // 与夏普传感器模块通信
	Serial3.begin(115200);
	dht.begin();
	myservo0.attach(ServoPin0);
	myservo1.attach(ServoPin1);

	Beep0.BeepOn();
	delay(100);
	Beep0.BeepOff();
	delay(100);
	Beep0.BeepOn();
	delay(100);
	Beep0.BeepOff();
	/*Beep0.BeepSwtich(0);*/

}

// the loop function runs over and over again until power down or reset
void loop() {

	//analogWrite(MotorPwm, 128);
	//myservo0.write(10);
	//int sensorValue = analogRead(RainInPin0);

	Usart0_Task.Usart0_RevTask();

	Usart2_Task.Usart2_RevTask();

	DHT_getdata();

	Usart1_Task.Usart1_TmtTask();
	Usart1_Task.Usart1_RevTask();

	Usart3_Task.Usart3_TmtTask();
	Usart3_Task.Usart3_RevTask();
	Serial.print(CtrlData0.AutoCtrl);

	WinLimit();
	
	PollutionAlarm();

	AutoOpenClose();
	//delay(100);
}

void DHT_getdata(void)
{
	SensorData0.TempIn = dht.readTemperature();
	SensorData0.HumiIn = dht.readHumidity();
	//Serial.print("HumiIn");
	//Serial.print(SensorData0.HumiIn, 1);
	//Serial.print("TempIn");
	//Serial.print(SensorData0.TempIn, 1);
}
void WinLimit(void)
{
	if (CtrlData0.WinState == 0)
	{
		if (digitalRead(LimitSwitchPin1) == 0)
		{
			MotorCtrl0.MotorStop();
			CtrlData0.WinState = 1;
		}
	}
	else if (CtrlData0.WinState == 1)
	{
		if (digitalRead(LimitSwitchPin0) == 0)
		{
			MotorCtrl0.MotorStop();
			CtrlData0.WinState = 0;

		}
	}
}

void PollutionAlarm(void)
{
	if (SensorData0.PM2_5 > SetData0.PollutantThreshold)
	{
		if (CtrlData0.PollutionState == 0)
		{
			Beep0.BeepOn();
			delay(200);
			Beep0.BeepOff();
			CtrlData0.PollutionState = 1;
		}

	}
	else
	{
		CtrlData0.PollutionState = 0;
	}
}

void AutoOpenClose(void)
{
	if (CtrlData0.AutoCtrl == 1)
	{
		if (CtrlData0.WinRecommendedState == 1)
		{
			if (CtrlData0.WinState == 0)
			{
				MotorCtrl0.MotorCw();
				CtrlData0.WinState = 0;
			}
		
		}
		if (CtrlData0.WinRecommendedState == 0)
		{
			if (CtrlData0.WinState == 1)
			{
				MotorCtrl0.MotorCcw();
				CtrlData0.WinState = 1;
			}
			
		}
	}
}


