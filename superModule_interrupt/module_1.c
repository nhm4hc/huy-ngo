#include "module_1.h"
#include "interruptPublish.h"

unsigned int module1_count = 0;
unsigned int module1_value = 0;
unsigned int module1_timer1 = 0;

void Time1Config(void){
	SET_BIT(c_interrupt,MODULE_0);
	TMOD|= 0x10;
	TH1 = 0xFF;
	TL1 = 0xff;
	ET1 = 1;
	EA = 1;
	TR1 = 1;
}

void module_1(void){
	Time1Config();
	if(module1_count > 100)
	{
		module1_count = 0;
		if(DIR == 1)
		{
		  module1_value++;
		}
		if(DIR == 0)
		{
		  module1_value--;
		}
	}

	if(module1_value == 1000)
	{
	  DIR = 0;
	}
	if(module1_value == 0)
	{
	  DIR = 1;
	}
	
	if(module1_timer1 > 1000)
	{
		module1_timer1 = 0;
	}
	if(module1_timer1 < module1_value)
	{
		module1_PWM = 1;
	}
	else
	{
		module1_PWM = 0;
	}
}