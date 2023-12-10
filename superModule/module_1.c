#include "module_1.h"

void Time1Config(void){
	TMOD|= 0x10;
	TH1 = 0xFF;
	TL1 = 0xff;

	ET1 = 1;
	EA = 1;
	TR1 = 1;
}

void Time1(void) interrupt 3{
		TH1 = 0xFF;
		TL1 = 0xFf;
		timer1++;
		count++;
}

void module_1(void){
	Time1Config();
	if(count > 100)
	{
		count = 0;
		if(DIR == 1)
		{
		  value++;
		}
		if(DIR == 0)
		{
		  value--;
		}
	}

	if(value == 1000)
	{
	  DIR = 0;
	}
	if(value == 0)
	{
	  DIR = 1;
	}
	
	if(timer1 > 1000)
	{
		timer1 = 0;
	}
	if(timer1 < value)
	{
		module1_PWM = 1;
	}
	else
	{
		module1_PWM = 0;
	}
}