#include <reg52.h>
sbit PWM=P2^0;
unsigned char timer1; 

void Time1Config();

void main(void)
{
        Time1Config();
        while(1)
        { 
                if(timer1>100)  
                {
                        timer1=0;
                }
                if(timer1 < 30) 
                {
                        PWM=1;
                }
                else
                {
                        PWM=0;
                }
        }
        

 }
void Time1Config()
{
        TMOD|= 0x10;   
        TH1 = 0xFE; 
        TL1 = 0x0C;

        
        ET1 = 1;         
        EA = 1;
        TR1 = 1;            
}



void Time1(void) interrupt 3    
{
        TH1 = 0xFE;  
        TL1 = 0x0C;
        timer1++;    
}