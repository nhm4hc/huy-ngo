/*******************************************************************************
Tên thuc hành: Thuc hành voi dong co buoc
IO su dung: Ðong co su dung cong P1 (P1.0/P1.1/P1.2/P1.3)
Hieu qua thuc hành: 
Luu ý: Do chân P3.2 duoc chia se voi duong dây ngoai vi màu do, de tránh anh huong tu duong dây ngoai 
vi màu do den hieu qua thuc hành khi thuc hien thí nghiem voi nút bam, tot nhat ban nên tháo dây ngoai vi màu do ra truoc.
*******************************************************************************/ 
#include "REG52.H"

//Ðong co IO
#define GPIO_MOTOR P1
//sbit F1 = P1^0;
//sbit F2 = P1^1;
//sbit F3 = P1^2;
//sbit F4 = P1^3;
//Nut bam IO
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;


unsigned char code FFW[8]={0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9}; //Thu tu quay nguoc

void Delay(unsigned int t);
void  Motor(); 

/*******************************************************************************
Tên hàm: main
Chuc nang cua hàm: Hàm chính
Ðau vào: Không
Ðau ra: Không
*******************************************************************************/

void main(void) 
{ 
  while(1)
	{
		Motor();
	}
}
/*******************************************************************************
Tên hàm: Motor
Chac nang cua hàm: Hàm quay d?ng co
Ðau vào: Không
Ðau ra: Không
*******************************************************************************/

void  Motor()
{ 
	unsigned char i;
	for(i=0;i<8;i++)
	{ 
		GPIO_MOTOR = FFW[i]&0x1f;  //Lay du lieu chi lay 4 bit sau
		Delay(30);	//Dieu chinh toc do quay	
	}	                  
}
/*******************************************************************************
Tên hàm: Delay
Chuc nang cua hàm: Hàm trì hoãn (delay)
Ðau vào: t
Ðau ra: Không
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



