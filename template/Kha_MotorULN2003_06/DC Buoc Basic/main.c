/*******************************************************************************
T�n thuc h�nh: Thuc h�nh voi dong co buoc
IO su dung: �ong co su dung cong P1 (P1.0/P1.1/P1.2/P1.3)
Hieu qua thuc h�nh: 
Luu �: Do ch�n P3.2 duoc chia se voi duong d�y ngoai vi m�u do, de tr�nh anh huong tu duong d�y ngoai 
vi m�u do den hieu qua thuc h�nh khi thuc hien th� nghiem voi n�t bam, tot nhat ban n�n th�o d�y ngoai vi m�u do ra truoc.
*******************************************************************************/ 
#include "REG52.H"

//�ong co IO
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
T�n h�m: main
Chuc nang cua h�m: H�m ch�nh
�au v�o: Kh�ng
�au ra: Kh�ng
*******************************************************************************/

void main(void) 
{ 
  while(1)
	{
		Motor();
	}
}
/*******************************************************************************
T�n h�m: Motor
Chac nang cua h�m: H�m quay d?ng co
�au v�o: Kh�ng
�au ra: Kh�ng
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
T�n h�m: Delay
Chuc nang cua h�m: H�m tr� ho�n (delay)
�au v�o: t
�au ra: Kh�ng
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



