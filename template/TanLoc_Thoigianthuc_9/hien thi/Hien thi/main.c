#include<reg51.h>
#include"ds1302.h"

#define DIG	P0
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char Num=0;
unsigned int disp[8]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};

void Timer0Configuration(void);
void DigDisplay(void);

void Timer0Configuration(){
	TMOD=0X02;
	TH0=0X9C;	
	TL0=0X9C;	
	ET0=1;
	EA=1;
	TR0=1;	
}

void DigDisplay() interrupt 1{
//	TH0=0X9c;
//	TL0=0X00;		
	DIG=0; 
	switch(Num)	 
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
	DIG=disp[Num]; 
	Num++;
	if(Num>7)
		Num=0;
}

void main()
{
	Ds1302Init();
  Timer0Configuration();
	while(1)
	{	
		Ds1302ReadTime();
		disp[7] = DIG_CODE[TIME[0]&0x0f];
		disp[6] = DIG_CODE[TIME[0]>>4];
		disp[5] = 0X40;
		disp[4] = DIG_CODE[TIME[1]&0x0f];
		disp[3] = DIG_CODE[TIME[1]>>4];
		disp[2] = 0X40;
		disp[1] = DIG_CODE[TIME[2]&0x0f];
		disp[0] = DIG_CODE[TIME[2]>>4];	
	}
}


