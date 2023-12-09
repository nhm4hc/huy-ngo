/*******************************************************************************
* ʵ����			  : EEPROMʵ��
* ʹ�õ�IO	    : 
* ʵ��Ч��      : ��K1������ʾ�����ݣ���K2��ȡ�ϴα�������ݣ���K3��ʾ���ݼ�һ��
*��K4��ʾ�������㡣
*	ע��					������P3.2�ڸ������߹��ã�����������ʵ��ʱΪ�˲��ú�����Ӱ��ʵ��Ч������ðѺ�������
*ȡ������
*
*********************************************************************************/
#include<reg51.h>
#include"i2c.h"
//�����IO
#define DIG	P0
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
//����IO
sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;
void At24c02Write(unsigned char ,unsigned char );
unsigned char At24c02Read(unsigned char );
void Delay1ms();
void Timer0Configuration();
unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char Num=0;
unsigned int disp[8]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};
/*******************************************************************************
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{
	unsigned int num0=0,num1=0,n;
	Timer0Configuration();
	while(1)
	{
		if(K1==0)   // ghi gi� tri v�o eeprom
		{
			Delay1ms();
			if(K1==0)
				At24c02Write(2,num0);
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
			n=0;
		}
		
		if(K2==0)		// doc gi� tri tu eeprom
		{
			Delay1ms();
			if(K2==0)
				num0=At24c02Read(2);
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
		}			
		if(K3==0)
		{
			Delay1ms();
			if(K3==0)
				num0++;
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
			if(num0==256)
				num0=0;
		}
			
		if(K4==0)
		{
			Delay1ms();
			if(K4==0)
				num0=0;
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
		}			
		disp[0]=DIG_CODE[num1/1000];//ǧλ
		disp[1]=DIG_CODE[num1%1000/100];//��λ
		disp[2]=DIG_CODE[num1%1000%100/10];//ʮλ
		disp[3]=DIG_CODE[num1%1000%100%10];//��λ
		disp[4]=DIG_CODE[num0/1000];//ǧλ
		disp[5]=DIG_CODE[num0%1000/100];//��λ
		disp[6]=DIG_CODE[num0%1000%100/10];//��λ
		disp[7]=DIG_CODE[num0%1000%100%10];	
	}
}									 
/*******************************************************************************
* ������         : Timer0Configuration()
* ��������		   : ���ü�ʱ��
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void Timer0Configuration()
{
	TMOD=0X02;//ѡ��Ϊ��ʱ��ģʽ��������ʽ2������TRX��������

	TH0=0X9C;	//����ʱ������ֵ����ʱ100us
	TL0=0X9C;	
	ET0=1;//�򿪶�ʱ��0�ж�����
	EA=1;//�����ж�
	TR0=1;//�򿪶�ʱ��		
}
/*******************************************************************************
* ������         : Delay1ms()
* ��������		   : ��ʱ
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void Delay1ms()   //��� 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}
/*******************************************************************************
* ������         : void At24c02Write(unsigned char addr,unsigned char dat)
* ��������		   : ��24c02��һ����ַд��һ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(0xa2);//�// ten eeprom
	I2cSendByte(addr);//�dia chi trong eeprom
	I2cSendByte(dat);	//�data eeprom
	I2cStop();
}
/*******************************************************************************
* ������         : unsigned char At24c02Read(unsigned char addr)
* ��������		   : ��ȡ24c02��һ����ַ��һ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa2); //����д������ַ
	I2cSendByte(addr); //����Ҫ��ȡ�ĵ�ַ
	I2cStart();
	I2cSendByte(0xa3); //���Ͷ�������ַ
	num=I2cReadByte(); //��ȡ����
	I2cStop();
	return num;	
}
/*******************************************************************************
* ������         : DigDisplay() interrupt 1
* ��������		   : �ж��������ʾ
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void DigDisplay() interrupt 1
{
//��ʱ���ڹ�����ʽ�����Զ���װ�������Բ����ڸ�ֵ��
//	TH0=0X9c;//����ʱ������ֵ����ʱ1ms
//	TL0=0X00;		
	// DIG=0; //����
	P1 = disp[7];
	switch(Num)	 //λѡ��ѡ�����������ܣ�
	{
		case(7):
			LSA=0;LSB=0;LSC=0; break;
		case(6):
			LSA=1;LSB=0;LSC=0; break;
		case(5):
			LSA=0;LSB=1;LSC=0; break;
		case(4):
			LSA=1;LSB=1;LSC=0; break;
		case(3):
			LSA=0;LSB=0;LSC=1; break;
		case(2):
			LSA=1;LSB=0;LSC=1; break;
		case(1):
			LSA=0;LSB=1;LSC=1; break;
		case(0):
			LSA=1;LSB=1;LSC=1; break;	
	}
	DIG=disp[Num]; //��ѡ��ѡ����ʾ�����֡�
	Num++;
	if(Num>7)
		Num=0;
}