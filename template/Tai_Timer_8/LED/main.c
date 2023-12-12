#include<reg51.h>	
#include<intrins.h>

#define GPIO_LED_6 P2

extern unsigned char module5_Time;

unsigned char module5_Time = 0;

void TimerConfiguration(void);
void Timer0(void);

void TimerConfiguration(void){
  TMOD = 0x01; 
  TH0 = 0x3C;	 
  TL0 = 0xB0; 
  EA = 1;			 
  ET0 = 1;		 
  TR0 = 1;		 
}

void Timer0(void) interrupt 1{
	TH0 = 0x3C;	 
  TL0 = 0xB0;
	module5_Time++;
}

void main(void){
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

