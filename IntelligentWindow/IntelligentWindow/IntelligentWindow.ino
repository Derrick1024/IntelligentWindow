/*
 Name:		IntelligentWindow.ino
 Created:	2016/3/14 22:00:22
 Author:	ycg10
*/
#include <DHT.h>
#include <Servo.h>
#include "IntelligentWindow.h"

SensorData SensorData0;
CtrlData CtrlData0;
DHT dht(DHT11Pin, DHTTYPE);
Servo myservo0;
Servo myservo1;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(MotorPin0, OUTPUT);
	pinMode(MotorPin1, OUTPUT);
	pinMode(MotorPwm, OUTPUT);
	pinMode(RelayPin0, OUTPUT);
	pinMode(RelayPin1, OUTPUT);

	pinMode(LimitSwitchPin0, INPUT);
	pinMode(LimitSwitchPin0, INPUT);
	pinMode(LimitSwitchPin0, INPUT);

	Serial.begin(115200);
	Serial1.begin(2400);
	Serial2.begin(115200);
	Serial3.begin(115200);
	dht.begin();
	myservo0.attach(ServoPin0);
	myservo1.attach(ServoPin1);
	
}

// the loop function runs over and over again until power down or reset
void loop() {

	analogWrite(MotorPwm, 128);
	myservo0.write(10);
	int sensorValue = analogRead(RainInPin0);

}
