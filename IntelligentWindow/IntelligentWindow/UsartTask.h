// UsartTask.h


#ifndef _USARTTASK_h
#define _USARTTASK_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Usart_Task
{
public:
	String comdata0 = "";//串口接收数据
	String comdata1 = "";//串口接收数据
	String comdata2 = "";//串口接收数据
	int numdata[4] = { 0 }; //comdata 拆分后的数据num1,num2,num3,num4
	int states0 = 0; //开始解析的状态标志，取值有（-1）0 1 2 3

	int Usart0_RevTask(void);
	int Usart1_TmtTask(void);
	int Usart1_RevTask(void);
	int Usart2_RevTask(void);

};
#endif

