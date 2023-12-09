#include<reg51.h>	
#include<intrins.h>
#define GPIO_LED P2

void TimerConfiguration();
unsigned char Time;

void main(void)
{
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

		   

void TimerConfiguration()
{
    TMOD = 0x01; 
    TH0 = 0x3C;	 
    TL0 = 0xB0; 
    EA = 1;			 
    ET0 = 1;		 
    TR0 = 1;		 
	   

void Timer0() interrupt 1
{
	TH0 = 0x3C;	 
    TL0 = 0xB0;
	Time++;
}