#include<reg51.h>
#include"lcd12864.h"

void Delay10ms(unsigned int c)
{
  unsigned char a, b;
  for (;c>0;c--)
	{
		for(b=38;b>0;b--)
		{
			for(a=130;a>0;a--);
		}			 
	}    
}

void main()
{
	LCD12864_Init();
	//LCD12864_ClearScreen();
	LCD12864_DrowPoint(0,0);
	LCD12864_DrowPoint(127,63);
	while(1);
}


