#include "UsartTask.h"
#include "ValueFunDefine.h"

extern SensorData SensorData0;
extern CtrlData CtrlData0;

int Usart_Task::Usart0_RevTask(void)
{

	return 1;
}
int Usart_Task::Usart1_TmtTask(void)
{
	const char CmdEnd[3] = { 0xff, 0xff, 0xff };
	/*Serial1.printf("Êý¾Ý¼à¿Ø.t0.txt=%f", SensorData0.PM2_5);*/
	printf("sjjk.t0.txt=\"%d\"", int(SensorData0.PM2_5));
	Serial1.write(CmdEnd, 3);
	printf("sjjk.t1.txt=\"%d\"",int(SensorData0.TempOut));
	Serial1.write(CmdEnd, 3);
	printf("sjjk.t2.txt=\"%d\"", int(SensorData0.HumiOut));
	Serial1.write(CmdEnd, 3);
	printf("sjjk.t3.txt=\"%d\"", int(SensorData0.TempIn));
	Serial1.write(CmdEnd, 3);
	printf("sjjk.t4.txt=\"%d\"", int(SensorData0.HumiIn));
	Serial1.write(CmdEnd, 3);
	return 1;
}

int Usart_Task::Usart1_RevTask(void)
{
	if (Serial1.available() > 0)
	{
		while (Serial1.peek() != 0xff)
		{
			comdata0 += char(Serial1.read());
			delayMicroseconds(120);
		}
		Serial1.read();
		delayMicroseconds(120);
		Serial1.read();
		delayMicroseconds(120);
		Serial1.read();

		//Serial.print(comdata0);
		comdata0 = "";
	}

	//Serial.write(hexdata, 8);
	return 1;
}

int Usart_Task::Usart2_RevTask(void)
{
	String temp = "";
	if (Serial2.available() > 0)
	{
		//	while (char(Serial.peek()) != '\n')
		//{
		//delayMicroseconds(120);
		//comdata0 += char(Serial.read());
		//delayMicroseconds(120);
		//}
		//Serial.read();
		//delayMicroseconds(120);

		for (int i = 0; i < 16; i++)
		{
			delayMicroseconds(120);
			comdata0 += char(Serial2.read());
		}
		
		/*Serial.print(comdata0);*/
		temp = comdata0.substring(0, 4);
		SensorData0.PM2_5 = temp.toFloat();
		temp = comdata0.substring(5, 9);
		SensorData0.TempOut = temp.toFloat();
		temp = comdata0.substring(10, 14);
		SensorData0.HumiOut = temp.toFloat();

		Serial.print("PM25");
		Serial.print(SensorData0.PM2_5);
		Serial.print("HumiOut");
		Serial.print(SensorData0.HumiOut);
		Serial.print("TempOut");
		Serial.print(SensorData0.TempOut);
		comdata0 = "";
	}
	return 1;
}

