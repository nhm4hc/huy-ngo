#include "module_5.h"
#include "interruptPublish.h"

unsigned char module5_Time = 0;

void TimerConfiguration(void){
	SET_BIT(c_interrupt,MODULE_4);
  TMOD = 0x01; 
  TH0 = 0x3C;	 
  TL0 = 0xB0; 
  EA = 1;			 
  ET0 = 1;		 
  TR0 = 1;		 
}

void module_5(void){
	GPIO_LED_6 = 0XFE;
	TimerConfiguration();
	while(1)
	{
		if(module5_Time == 10)
		{
			GPIO_LED_6 =_crol_(GPIO_LED_6, 1);
			module5_Time = 0;
		}
	}
}
	