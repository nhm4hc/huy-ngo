#include<reg51.h>
#include"lcd12864.h"

unsigned char code Ten[]="NGO QUOC HUY!";
void main()
{
	unsigned char i=0;
	LCD12864_Init();
	while(1)
	{
		LCD12864_SetWindow(0,0);
		while(Ten[i]!='\0')
		{
			LCD12864_WriteData(Ten[i]);
			i++;
			//sau khi viet 16 ki tu thi xuong dong
			if(i==16)  
				LCD12864_SetWindow(1,0);
			if(i==32)  
				LCD12864_SetWindow(2,0);
			if(i==48)
				LCD12864_SetWindow(3,0);
		}
		LCD12864_WriteCmd(0x01);
	}	
}
