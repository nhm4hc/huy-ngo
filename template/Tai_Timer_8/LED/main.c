#include<reg51.h>	
#include<intrins.h>

#define GPIO_LED P2

unsigned char Time;

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
	Time++;
}

void main(void){
	Time=0;
	GPIO_LED=0XFE;
	TimerConfiguration();
	while(1)
	{
		if(Time==10)
		{
			GPIO_LED=_crol_(GPIO_LED,1);
			Time=0;
		}
	}				
}  

