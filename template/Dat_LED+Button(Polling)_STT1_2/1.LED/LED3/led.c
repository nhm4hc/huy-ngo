#include <reg51.h>	   

void Delay10ms(unsigned int);//tao ham delay 

void main()
{ 
	while(1)
	{
		P2  = 0x00;//led tat het 
		Delay10ms(50);//delay 500ms 
		P2  = 0xff;//led sang het
		Delay10ms(50);//delay 500ms
	}

}

void Delay10ms(unsigned int c) //ham delay 10ms
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}










