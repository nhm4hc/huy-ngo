#include<reg51.h>
#include"i2c.h"

#define DIG	P0

sbit module3_LSA = P2^2;
sbit module3_LSB = P2^3;
sbit module3_LSC = P2^4;

sbit module3_K1 = P3^1;
sbit module3_K2 = P3^0;
sbit module3_K3 = P3^2;
sbit module3_K4 = P3^3;

const unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char Num;
unsigned char disp[8]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};

void At24c02Write(unsigned char ,unsigned char);
unsigned char At24c02Read(unsigned char );
void Delay1ms(void);
void Timer0Configuration(void);

void At24c02Write(unsigned char addr,unsigned char dat){
	I2cStart();
	I2cSendByte(0xa2);//·// ten eeprom
	I2cSendByte(addr);//·dia chi trong eeprom
	I2cSendByte(dat);	//·data eeprom
	I2cStop();
}

unsigned char At24c02Read(unsigned char addr){
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa2); 
	I2cSendByte(addr); 
	I2cStart();
	I2cSendByte(0xa3); 
	num = I2cReadByte(); 
	I2cStop();
	return num;	
}

void Delay1ms(void)   
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}

void Timer0Configuration(void){
	Num = 0;
	TMOD=0X02;
	TH0=0X9C;	
	TL0=0X9C;	
	ET0=1;
	EA=1;
	TR0=1;	
}

void DigDisplay() interrupt 1{ 
	P1 = disp[7];
	switch(Num)	 
	{
		case(7):
			module3_LSA=0; module3_LSB=0; module3_LSC=0; break;
		case(6):
			module3_LSA=1; module3_LSB=0; module3_LSC=0; break;
		case(5):
			module3_LSA=0; module3_LSB=1; module3_LSC=0; break;
		case(4):
			module3_LSA=1; module3_LSB=1; module3_LSC=0; break;
		case(3):
			module3_LSA=0; module3_LSB=0; module3_LSC=1; break;
		case(2):
			module3_LSA=1; module3_LSB=0; module3_LSC=1; break;
		case(1):
			module3_LSA=0; module3_LSB=1; module3_LSC=1; break;
		case(0):
			module3_LSA=1; module3_LSB=1; module3_LSC=1; break;	
	}
	DIG = disp[Num]; 
	Num++;
	if(Num>7)
		Num=0;
}

void main(void){
	unsigned int num0=0,num1=0,n;
	Timer0Configuration();
	while(1)
	{
		if(module3_K1==0)   // ghi giá tri vào eeprom
		{
			Delay1ms();
			if(module3_K1==0)
				At24c02Write(2,num0);
			while((n<200)&&(module3_K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
			n=0;
		}
		
		if(module3_K2 == 0)		// doc giá tri tu eeprom
		{
			Delay1ms();
			if(module3_K2 == 0)
				num0=At24c02Read(2);
			while((n<200)&&(module3_K3 == 0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
		}			
		if(module3_K3 == 0)
		{
			Delay1ms();
			if(module3_K3 == 0)
				num0++;
			while((n<200)&&(module3_K3 == 0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
			if(num0==256)
				num0=0;
		}
			
		if(module3_K4==0)
		{
			Delay1ms();
			if(module3_K4==0)
				num0=0;
			while((n<200)&&(module3_K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
		}			
		disp[0]=DIG_CODE[num1/1000];//Ç§Î»
		disp[1]=DIG_CODE[num1%1000/100];//°ÙÎ»
		disp[2]=DIG_CODE[num1%1000%100/10];//Ê®Î»
		disp[3]=DIG_CODE[num1%1000%100%10];//¸öÎ»
		disp[4]=DIG_CODE[num0/1000];//Ç§Î»
		disp[5]=DIG_CODE[num0%1000/100];//°ÙÎ»
		disp[6]=DIG_CODE[num0%1000%100/10];//¸öÎ»
		disp[7]=DIG_CODE[num0%1000%100%10];	
	}
}									 

