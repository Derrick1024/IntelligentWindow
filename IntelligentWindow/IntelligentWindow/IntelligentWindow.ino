/*
 Name:		IntelligentWindow.ino
 Created:	2016/3/14 22:00:22
 Author:	ycg10
*/

#include "UsartTask.h"
#include <DHT.h>
#include <Servo.h>
#include "ValueFunDefine.h"

SensorData SensorData0;
CtrlData CtrlData0;
DHT dht(DHT11Pin, DHTTYPE);
Servo myservo0;
Servo myservo1;
Usart_Task Usart0_Task;
Usart_Task Usart1_Task;
Usart_Task Usart2_Task;



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

	Serial.begin(115200); // 调试用
	Serial1.begin(115200); // 与屏幕的通信
	Serial2.begin(2400); // 与夏普传感器模块通信
	Serial3.begin(115200);
	printf_begin();
	dht.begin();
	myservo0.attach(ServoPin0);
	myservo1.attach(ServoPin1);

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

	delay(100);
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
int serial_putc(char c, struct __file *)
{
	Serial1.write(c);
	return c;
}
void printf_begin(void)
{
	fdevopen(&serial_putc, 0);
}
