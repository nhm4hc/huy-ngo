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
		module1_timer1++;
		module1_count++;
}

void module_1(void){
	Time1Config();
	if(module1_count > 100)
	{
		module1_count = 0;
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
	
	if(module1_timer1 > 1000)
	{
		module1_timer1 = 0;
	}
	if(module1_timer1 < value)
	{
		module1_PWM = 1;
	}
	else
	{
		module1_PWM = 0;
	}
}