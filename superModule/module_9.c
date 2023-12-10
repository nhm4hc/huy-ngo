#include "module_9.h"

void  Motor(){ 
	unsigned char i;
	for(i=0;i<FF_length;i++)
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
		for(k=0; k<80; k++)
		{ }
	}
}

void module_9(void){
	unsigned char i;
	Speed = 30;
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