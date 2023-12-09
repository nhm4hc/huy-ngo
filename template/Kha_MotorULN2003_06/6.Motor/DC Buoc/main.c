/*******************************************************************************
Tên san pham: Bo dieu khien he thong
Su dung IO: Su dung P1 cho he thong chính, su dung P3.0, P3.1, P3.2, P3.3 cho các chuc nang phu.
Ket qua dieu khien: K1 du?i, th?i gian thay d?i, K2 du?i, th?i gian thay d?i, K3 du?i, th?p, K4 du?i, cao.
Chú ý: Do s? d?ng P3.2 d? k?t n?i bên ngoài, do dó các dèn LED bên ngoài s? không sáng khi h? th?ng chuy?n sang ch? d? ngoài vi?c di?u khi?n b?i P3.2.
K?t qu? di?u khi?n t?t nh?t s? du?c hi?n th? du?i dây sau khi ra kh?i ch? d? bên ngoài
*******************************************************************************/ 
#include "reg52.h"

//µç»úIO
#define GPIO_MOTOR P1
//sbit F1 = P1^0;
//sbit F2 = P1^1;
//sbit F3 = P1^2;
//sbit F4 = P1^3;
//°´¼üIO
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;

unsigned char code FFW[8]={0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9}; //·Xoay cung chieu kim dong ho theo half-step
unsigned char code FFZ[8]={0xf9,0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1}; //Xoay nguoc chieu kim dong ho theo half-step

unsigned char Direction,Speed;
void Delay(unsigned int t);
void  Motor(); 

/*******************************************************************************
Tên hàm chính: main
Chuc nang cua hàm: Hàm chính
Tham so dau vào: Không có
Giá tri tra ve: Không có
*******************************************************************************/

void main(void) 
{ 
	unsigned char i;
	Speed=30;
  while(1)
	{
		if(K1==0)		//Kiem tra nut K1 co nhan hay khong
		{
			Delay(1);	//Ham delay don nut
			if(K1==0)
			{
				Direction=1;
			}
			while((i<200)&&(K1==0))	 //Kiem tra nut co duoc nha hay khong (trong 200ms)
			{
				Delay(1);
				i++;
			}
			i=0;
		}
		if(K2==0)		//¼ì²â°´¼üK1ÊÇ·ñ°´ÏÂ
		{
			Delay(1);	//Ïû³ý¶¶¶¯
			if(K2==0)
			{
				Direction=2;
			}
			while((i<200)&&(K2==0))	 //¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay(1);
				i++;
			}
			i=0;
		}			
		if(K3==0)		//¼ì²â°´¼üK1ÊÇ·ñ°´ÏÂ
		{
			Delay(1);	//Ïû³ý¶¶¶¯
			if(K3==0)
			{
				Speed=13;
			}
			while((i<200)&&(K3==0))	 //¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay(1);
				i++;
			}
			i=0;
		}
		if(K4==0)		//¼ì²â°´¼üK1ÊÇ·ñ°´ÏÂ
		{
			Delay(1);	//Ïû³ý¶¶¶¯
			if(K4==0)
			{
				Speed=40;
			}
			while((i<200)&&(K4==0))	 //¼ì²â°´¼üÊÇ·ñËÉ¿ª
			{
				Delay(1);
				i++;
			}
			i=0;
		}		
		Motor();
	}
}
/*******************************************************************************
Tên chuc nang: Dong co
Chuc nang chính: Quay dong co
Ðau vào: Không
Ðau ra: Không
*******************************************************************************/

void  Motor()
{ 
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(Direction==1) 
			GPIO_MOTOR = FFW[i]&0x1f;  //È¡Êý¾Ý
		if(Direction==2) 
			GPIO_MOTOR = FFZ[i]&0x1f;
		Delay(Speed);	//µ÷½Ú×ªËÙ	
	}	                  
}
/*******************************************************************************
Tên hàm: Delay
Chuc nang hàm: Ðoi mot khoang thoi gian
Tham so vào: t
Tham so ra: Không

*******************************************************************************/
void Delay(unsigned int t)
{                           
	unsigned int k;
	while(t--)
	{
		for(k=0; k<80; k++)
		{ }
	}
}



