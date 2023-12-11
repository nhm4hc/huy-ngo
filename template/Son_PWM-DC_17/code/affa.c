#include <reg52.h>

sbit module4_PWM = P2^0;

unsigned char module4_timer1; 

void module4_Time1Config(void);
void module4_Time1(void);

void module4_Time1Config(void){
  TMOD |= 0x10;   
  TH1 = 0xFE; 
  TL1 = 0x0C;
  ET1 = 1;         
  EA = 1;
  TR1 = 1;            
}

void module4_Time1(void) interrupt 3{
	TH1 = 0xFE;  
	TL1 = 0x0C;
	module4_timer1++;    
}

void main(void)
{
	module4_Time1Config();
	while(1)
	{ 
		if(module4_timer1>100)  
		{
			module4_timer1=0;
		}
		if(module4_timer1 < 30) 
		{
			module4_PWM=1;
		}
		else
		{
			module4_PWM=0;
		}
	}
}
