#include<reg51.h>

sbit LED1=P2^0;//noi led vao chan P2.0
void Delay(unsigned int a);//ham delay
void main()
{
	while(1)
	{
		LED1=0;//tat led
		Delay(5000);//khoan 1.2s
		LED1=1;//bat led
		Delay(5000);
	}
}

void Delay(unsigned int a)//0~65535
{
	unsigned char b;
	for(;a>0;a--)
	{
		for(b=110;b>0;b--);
	}
}