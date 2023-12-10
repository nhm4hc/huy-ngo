#include <reg51.h>	   

#define LED_DON P2

void module15_Delay10ms(unsigned int c);//tao ham delay 

void module15_Delay10ms(unsigned int c) //ham delay 10ms
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void main()
{ 
	while(1)
	{
		LED_DON  = 0x00;//led tat het 
		module15_Delay10ms(50);//delay 500ms 
		LED_DON  = 0xff;//led sang het
		module15_Delay10ms(50);//delay 500ms
	}

}












