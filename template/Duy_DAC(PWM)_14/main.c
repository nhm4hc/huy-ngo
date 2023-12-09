#include <reg52.h>

sbit PWM=P2^1;
bit DIR;
unsigned int count,value,timer1;
unsigned char flag = 0;
void Time1Config()
{
	TMOD|= 0x10;
	TH1 = 0xFF;
	TL1 = 0xff;

	ET1 = 1;
	EA = 1;
	TR1 = 1;
	flag = 1;
}

void Time1(void) interrupt 3
{
	if(flag == 1)
	{
		TH1 = 0xFF;
		TL1 = 0xFf;
		timer1++;
		count++;
	}
	
}

void main(void)
{
	Time1Config();
	while(1)
	{
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
			PWM = 1;
		}
		else
		{
			PWM = 0;
		}
	}
 }


