/*******************************************************************************
T�n san pham: Bo dieu khien he thong
Su dung IO: Su dung P1 cho he thong ch�nh, su dung P3.0, P3.1, P3.2, P3.3 cho c�c chuc nang phu.
Ket qua dieu khien: K1 du?i, th?i gian thay d?i, K2 du?i, th?i gian thay d?i, K3 du?i, th?p, K4 du?i, cao.
Ch� �: Do s? d?ng P3.2 d? k?t n?i b�n ngo�i, do d� c�c d�n LED b�n ngo�i s? kh�ng s�ng khi h? th?ng chuy?n sang ch? d? ngo�i vi?c di?u khi?n b?i P3.2.
K?t qu? di?u khi?n t?t nh?t s? du?c hi?n th? du?i d�y sau khi ra kh?i ch? d? b�n ngo�i
*******************************************************************************/ 
#include "reg52.h"

//���IO
#define GPIO_MOTOR P1
//sbit F1 = P1^0;
//sbit F2 = P1^1;
//sbit F3 = P1^2;
//sbit F4 = P1^3;
//����IO
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;

unsigned char code FFW[8]={0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9}; //�Xoay cung chieu kim dong ho theo half-step
unsigned char code FFZ[8]={0xf9,0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1}; //Xoay nguoc chieu kim dong ho theo half-step

unsigned char Direction,Speed;
void Delay(unsigned int t);
void  Motor(); 

/*******************************************************************************
T�n h�m ch�nh: main
Chuc nang cua h�m: H�m ch�nh
Tham so dau v�o: Kh�ng c�
Gi� tri tra ve: Kh�ng c�
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
		if(K2==0)		//��ⰴ��K1�Ƿ���
		{
			Delay(1);	//��������
			if(K2==0)
			{
				Direction=2;
			}
			while((i<200)&&(K2==0))	 //��ⰴ���Ƿ��ɿ�
			{
				Delay(1);
				i++;
			}
			i=0;
		}			
		if(K3==0)		//��ⰴ��K1�Ƿ���
		{
			Delay(1);	//��������
			if(K3==0)
			{
				Speed=13;
			}
			while((i<200)&&(K3==0))	 //��ⰴ���Ƿ��ɿ�
			{
				Delay(1);
				i++;
			}
			i=0;
		}
		if(K4==0)		//��ⰴ��K1�Ƿ���
		{
			Delay(1);	//��������
			if(K4==0)
			{
				Speed=40;
			}
			while((i<200)&&(K4==0))	 //��ⰴ���Ƿ��ɿ�
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
T�n chuc nang: Dong co
Chuc nang ch�nh: Quay dong co
�au v�o: Kh�ng
�au ra: Kh�ng
*******************************************************************************/

void  Motor()
{ 
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(Direction==1) 
			GPIO_MOTOR = FFW[i]&0x1f;  //ȡ����
		if(Direction==2) 
			GPIO_MOTOR = FFZ[i]&0x1f;
		Delay(Speed);	//����ת��	
	}	                  
}
/*******************************************************************************
T�n h�m: Delay
Chuc nang h�m: �oi mot khoang thoi gian
Tham so v�o: t
Tham so ra: Kh�ng

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



