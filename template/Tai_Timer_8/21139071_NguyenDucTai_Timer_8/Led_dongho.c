#include<reg51.h>	
#include"lcd.h"
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;

unsigned char Time;

void Delay1ms(unsigned int c);
void TimerConfiguration();
void Int0Configuration();

unsigned char SetPlace;

void main(void)
{
	unsigned char hour,minit,second;
	unsigned int i;
	TimerConfiguration();
	Int0Configuration();
	LcdInit();
	hour=12;
	LcdWriteData('0'+hour/10);
	LcdWriteData('0'+hour%10);
	LcdWriteData('-');
	LcdWriteData('0'+minit/10);
	LcdWriteData('0'+minit%10);
	LcdWriteData('-');
	LcdWriteData('0'+second/10);
	LcdWriteData('0'+second%10);
	while(1)
	{
		if(TR0==0)
		{
			if(K1==0)
			{
				Delay1ms(10);	
				if(K1==0)
				{
					SetPlace++;
					if(SetPlace>=3)
						SetPlace=0;					
				}

				while((i<50)&&(K1==0))	 
				{
					Delay1ms(1);
					i++;
				}
				i=0;
			}
			if(K2==0)		
			{
				Delay1ms(10);	
				if(K2==0)
				{
					if(SetPlace==0)
					{
						second++;
						if(second>=60)
							second=0;
					}
					else if(SetPlace==1)
					{
						minit++;
						if(minit>=60)
							minit=0;	
					}
					else
					{
						hour++;
						if(hour>=24)
							hour=0;
					}				
				}

				while((i<50)&&(K2==0))	 
				{
					Delay1ms(1);
					i++;
				}
				i=0;
			}
		}	
		if(Time>=20)	 
		{
			Time=0;
			second++;
			if(second==60)
			{
				second=0;
				minit++;
				if(minit==60)
				{
					minit=0;
					hour++;
					if(hour==24)
					{
						hour=0;	
					}
				}				
			}					
		}	
	    
		LcdWriteCom(0x80);
		LcdWriteData('0'+hour/10);
		LcdWriteData('0'+hour%10);
		LcdWriteCom(0x83);
		LcdWriteData('0'+minit/10);
		LcdWriteData('0'+minit%10);
		LcdWriteCom(0x86);
		LcdWriteData('0'+second/10);
		LcdWriteData('0'+second%10);
	
	}				
}
		   
void Delay1ms(unsigned int c)   //Îó²î 0us
{
    unsigned char a,b;
	for (; c>0; c--)
	{
		for(b=199;b>0;b--)
		{
			for(a=1;a>0;a--);
		}
        
	}
    
}
	   
void TimerConfiguration()
{
    TMOD = 0x01; 
    TH0 = 0x3C;	 
    TL0 = 0x0B0; 
    EA = 1;			 
    ET0 = 1;		 
    TR0 = 1;		 
}
	   

void Timer0() interrupt 1
{
	TH0 = 0x3C;	 
    TL0 = 0x0B0;
	Time++;
}
   

void Int0Configuration()
{
	IT0=1;
	EX0=1;
	EA=1;	
}
		   

void Int0() interrupt 0		 
{
	Delay1ms(10);
	if(K3==0)
	{
		TR0=~TR0;
		SetPlace=0;
	}
}
