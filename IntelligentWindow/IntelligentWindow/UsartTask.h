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
	String comdata0 = "";//���ڽ�������
	String comdata1 = "";//���ڽ�������
	String comdata2 = "";//���ڽ�������
	int numdata[4] = { 0 }; //comdata ��ֺ������num1,num2,num3,num4
	int states0 = 0; //��ʼ������״̬��־��ȡֵ�У�-1��0 1 2 3

	int Usart0_RevTask(void);
	int Usart1_TmtTask(void);
	int Usart1_RevTask(void);
	int Usart2_RevTask(void);

};
#endif

