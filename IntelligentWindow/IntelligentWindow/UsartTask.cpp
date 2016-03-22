#include "UsartTask.h"
#include "ValueFunDefine.h"
#include "Algorithm.h"

//extern SensorData SensorData0;
//extern CtrlData CtrlData0;


int Usart_Task::Usart0_RevTask(void)
{
	Algorithm0.ASHRAE(SensorData0.TempIn, SensorData0.HumiIn);
	return 1;
}
int Usart_Task::Usart1_TmtTask(void)
{
	const char CmdEnd[3] = { 0xff, 0xff, 0xff };
	/*Serial1.printf("Êý¾Ý¼à¿Ø.t0.txt=%f", SensorData0.PM2_5);*/
	Serial1.print(String("") + "sjjk.t0.txt=\"" + SensorData0.PM2_5 + "\"");
	Serial1.write(CmdEnd, 3);
	Serial1.print(String("") + "sjjk.t1.txt=\"" + int(SensorData0.TempOut) + "\"");
	Serial1.write(CmdEnd, 3);
	Serial1.print(String("") + "sjjk.t2.txt=\"" + int(SensorData0.HumiOut) + "\"");
	Serial1.write(CmdEnd, 3);
	Serial1.print(String("") + "sjjk.t3.txt=\"" + int(SensorData0.TempIn) + "\"");
	Serial1.write(CmdEnd, 3);
	Serial1.print(String("") + "sjjk.t4.txt=\"" + int(SensorData0.HumiIn) + "\"");
	Serial1.write(CmdEnd, 3);
	
	return 1;
}

int Usart_Task::Usart1_RevTask(void)
{
	if (Serial1.available() > 0)
	{
		while (Serial1.peek() != 0xff)
		{
			comdata1 += char(Serial1.read());
			delayMicroseconds(120);
		}
		Serial1.read();
		delayMicroseconds(120);
		Serial1.read();
		delayMicroseconds(120);
		Serial1.read();

		//Serial.print(comdata0);
		comdata1 = "";
	}

	//Serial.write(hexdata, 8);
	return 1;
}

int Usart_Task::Usart2_RevTask(void)
{
	String temp = "";
	int first = 0, second = 0;

	if (Serial2.available() > 0)
	{
		while (Serial2.peek() != 0x0D)
		{
			comdata2 += char(Serial2.read());
			delay(6);
		}
		Serial2.read();
		delay(6);
		Serial2.read();
		delay(6);
		
		for (int i = 0; i < comdata2.length(); i++)
		{
			if (comdata2[i] == ',')
			{
				if (first == 0)
				{
					first = i;
				}
				else
				{
					second = i;
				}
			}
		}
		
		/*Serial.print(comdata2);
		Serial.print(first);
		Serial.print(second);*/
		temp = comdata2.substring(0, first);
		SensorData0.PM2_5 = temp.toFloat();
		temp = comdata2.substring(first + 1, second);
		SensorData0.TempOut = temp.toFloat();
		temp = comdata2.substring(second + 1, comdata2.length());
		SensorData0.HumiOut = temp.toFloat();

		//Serial.print("PM25");
		//Serial.print(SensorData0.PM2_5);
		//Serial.print("HumiOut");
		//Serial.print(SensorData0.HumiOut);
		//Serial.print("TempOut");
		//Serial.print(SensorData0.TempOut);
		comdata2 = "";
	}

	return 1;
}

