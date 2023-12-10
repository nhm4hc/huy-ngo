#include "reg52.h"

#define GPIO_MOTOR P1

sbit module9_K1=P3^0;
sbit module9_K2=P3^1;
sbit module9_K3=P3^2;
sbit module9_K4=P3^3;

unsigned char code FFW[8]={0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9}; //·Xoay cung chieu kim dong ho theo half-step
unsigned char code FFZ[8]={0xf9,0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1}; //Xoay nguoc chieu kim dong ho theo half-step

unsigned char Direction;
unsigned char	Speed;

void Motor(void); 
void module9_Delay(unsigned int t);

void  Motor(){ 
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if(Direction==1) 
			GPIO_MOTOR = FFW[i]&0x1f;  
		if(Direction==2) 
			GPIO_MOTOR = FFZ[i]&0x1f;
		module9_Delay(Speed);		
	}	                  
}

void module9_Delay(unsigned int t){                           
	unsigned int k;
	while(t--)
	{
		for(k=0; k<80; k++){ }
	}
}

void main(void) { 
	unsigned char i;
	Speed=30;
  while(1)
	{
		if(module9_K1==0)		
		{
			module9_Delay(1);	
			if(module9_K1==0)
			{
				Direction=1;
			}
			while((i<200)&&(module9_K1==0))	 
			{
				module9_Delay(1);
				i++;
			}
			i=0;
		}
		if(module9_K2==0)		
		{
			module9_Delay(1);
			if(module9_K2==0)
			{
				Direction=2;
			}
			while((i<200)&&(module9_K2==0))	 
			{
				module9_Delay(1);
				i++;
			}
			i=0;
		}			
		if(module9_K3==0)		
		{
			module9_Delay(1);	
			if(module9_K3==0)
			{
				Speed=13;
			}
			while((i<200)&&(module9_K3==0))	
			{
				module9_Delay(1);
				i++;
			}
			i=0;
		}
		if(module9_K4==0)		
		{
			module9_Delay(1);	
			if(module9_K4==0)
			{
				Speed=40;
			}
			while((i<200)&&(module9_K4==0))	
			{
				module9_Delay(1);
				i++;
			}
			i=0;
		}		
		Motor();
	}
}


