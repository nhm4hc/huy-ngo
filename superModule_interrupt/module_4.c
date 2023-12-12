#include "module_4.h"
#include "interruptPublish.h"

unsigned char module4_timer1 = 0;

void module4_Time1Config(void){
	SET_BIT(c_interrupt,MODULE_3);
  TMOD|= 0x10;   
  TH1 = 0xFE; 
  TL1 = 0x0C;
  ET1 = 1;         
  EA = 1;
  TR1 = 1;            
}

void module_4(void){
	module4_Time1Config();
	if(module4_timer1>100)  
	{
		module4_timer1=0;
	}
	if(module4_timer1 < 30) 
	{
		module4_PWM = 1;
	}
	else
	{
		module4_PWM = 0;
	}
}