#include "UsartTask.h"
#include "ValueFunDefine.h"
#include "Algorithm.h"
#include "MotorCtrl.h"


int Usart_Task::Usart0_RevTask(void)
{
	//Algorithm0.ASHRAE(SensorData0.TempIn, SensorData0.HumiIn);
	//Algorithm0.American(SensorData0.TempIn, SensorData0.HumiIn);

	return 1;
}
int Usart_Task::Usart1_TmtTask(void)
{
	float FloatValue = 0;
	int IntValue = 0;
	const char CmdEnd[3] = { 0xff, 0xff, 0xff };

	//刷新数据监控页
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

	//刷新实时状态页
	Serial1.print(String("") + "sszt.t0.txt=\"" + Algorithm0.compute_d(SensorData0.TempIn, SensorData0.HumiIn) + "/" + Algorithm0.compute_d(SensorData0.TempOut, SensorData0.HumiOut) + "\"");
	Serial1.write(CmdEnd, 3);
	FloatValue = Algorithm0.compute_pws(SensorData0.TempIn, SensorData0.HumiIn);
	Serial1.print(String("") + "sszt.t1.txt=\"" + FloatValue / 1000 + "KPa" + "\"");
	Serial1.write(CmdEnd, 3);
	FloatValue = Algorithm0.compute_pw(SensorData0.TempOut, SensorData0.HumiOut);
	Serial1.print(String("") + "sszt.t2.txt=\"" + FloatValue / 1000 + "KPa" + "\"");
	Serial1.write(CmdEnd, 3);
	Serial1.print(String("") + "sszt.t3.txt=\"" + Algorithm0.AQI_Evaluate(SensorData0.PM2_5) + "\"");
	Serial1.write(CmdEnd, 3);
	Serial1.print(String("") + "sszt.t4.txt=\"" + "N" + "\"");
	Serial1.write(CmdEnd, 3);
	if (Algorithm0.Window_Evaluate() == 0)
	{
		Serial1.print(String("") + "sszt.t5.txt=\"" + "N" + "\"");
		Serial1.write(CmdEnd, 3);
	}
	if (Algorithm0.Window_Evaluate() == 1)
	{
		Serial1.print(String("") + "sszt.t5.txt=\"" + "Y" + "\"");
		Serial1.write(CmdEnd, 3);
	}
	if (CtrlData0.WinState == 0)
	{
		Serial1.print(String("") + "sszt.t6.txt=\"" + "N" + "\"");
		Serial1.write(CmdEnd, 3);
	}
	if (CtrlData0.WinState == 1)
	{
		Serial1.print(String("") + "sszt.t6.txt=\"" + "Y" + "\"");
		Serial1.write(CmdEnd, 3);
	}

	//刷新状态控制页
	//Serial1.print(String("") + "ztkz.bt0.val=\"" + CtrlData0.AutoCtrl + "\"");
	//Serial1.write(CmdEnd, 3);
	//刷新系统设置页
	//Serial1.print(String("") + "xtsz.b8.txt=\"" + CtrlData0.SetTemperature + "\"");
	//Serial1.write(CmdEnd, 3);

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
		//Serial.print(comdata1);
		if (comdata1[0] == 0x03)
		{
			if (comdata1[1] == 0x07)
			{
				if (comdata1[2] == 0x71)
				{
					if (comdata1[3] == 0x00)
					{
						CtrlData0.AutoCtrl = 0;
					}
					if (comdata1[3] == 0x01)
					{
						CtrlData0.AutoCtrl = 1;
					}
				}
			}
		}
		if (CtrlData0.AutoCtrl == 0)
		{
			if (comdata1[0] == 0x65)
			{
				if (comdata1[1] == 0x03)
				{
					if (comdata1[2] == 0x05)
					{
						//open
						MotorCtrl0.MotorCw();
						CtrlData0.WinState = 0;
					}
					if (comdata1[2] == 0x06)
					{
						//close
						MotorCtrl0.MotorCcw();
						CtrlData0.WinState = 1;
					}
					if (comdata1[2] == 0x08)
					{
						//stop
						MotorCtrl0.MotorStop();
					}
				}
			}
		}

		//Serial.print(CtrlData0.AutoCtrl);
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
int Usart_Task::Usart3_TmtTask(void)
{

	return 1;
}

int Usart_Task::Usart3_RevTask(void)
{
	if (Serial3.available() > 0)
	{
		while (Serial3.peek() != 0xff)
		{
			comdata3 += char(Serial3.read());
			delay(6);
		}
		Serial3.read();
		delay(6);
		//Serial.print(comdata3);
		//Serial.print(CtrlData0.AutoCtrl);
		//if (CtrlData0.AutoCtrl == 0)
		//{
			if (comdata3[0] == 0x00)
			{
				//stop
				MotorCtrl0.MotorStop();
			}
			if (comdata3[0] == 0x01)
			{
				//open
				MotorCtrl0.MotorCw();
				CtrlData0.WinState = 0;
			}

			if (comdata3[0] == 0x02)
			{
				//close
				MotorCtrl0.MotorCcw();
				CtrlData0.WinState = 1;
			}

		//}

	}
	comdata3 = "";

	return 1;
}
