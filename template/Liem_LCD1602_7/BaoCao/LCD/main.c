#include<reg51.h>	
#include"lcd.h"

unsigned char PuZh[]=" Liem__21139076 ";
unsigned char Test[] = "  Xin chao VN  ";

/*******************************************************************************
* 	Chuong trinh         : main
*******************************************************************************/
void main(void)
{
	unsigned char i;
	LcdInit();//Goi ham khoi tao cho LCD
	//Ghi ra man hinh LCD lan luot cac ky tu cua chuoi
	for(i=0;i<16;i++)
	{
		LcdWriteData(PuZh[i]);	
	}
	LcdWriteCom(0x80 + 0x40);
	for (i=0;i < 16;i++){
		 LcdWriteData(Test[i]);
	}
	while(1)
	{
	}				
}