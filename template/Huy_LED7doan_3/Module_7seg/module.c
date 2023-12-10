#include<regx52.h>

#define GPIO_DIG P0

sbit module8_LSA=P2^2;
sbit module8_LSB=P2^3;
sbit module8_LSC=P2^4;

//unsigned char code hello[5]={0x76,0x79,0x3f,0x38,0x00}; //H,E,O,L
unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; // Mang so tu 0 - 9

void module8_delayMS(unsigned int t);
void chonKey(unsigned int k);

void module8_delayMS(unsigned int t){
	int i,j;
	for (i=0; i<t; i++)
		for (j=0; j<123; j++) {} 
}

void chonKey(unsigned int k){
	switch (k)
  {
    case (0):
        module8_LSC = 0; module8_LSB = 0; module8_LSA = 0; break;
    case (1):
        module8_LSC = 0; module8_LSB = 0; module8_LSA = 1; break;
    case (2):
        module8_LSC = 0; module8_LSB = 1; module8_LSA = 0; break;
    case (3):
        module8_LSC = 0; module8_LSB = 1; module8_LSA = 1; break;        
    case (4):
        module8_LSC = 1; module8_LSB = 0; module8_LSA = 0; break;        
    case (5):
        module8_LSC = 1; module8_LSB = 0; module8_LSA = 1; break;       
    case (6):
        module8_LSC = 1; module8_LSB = 1; module8_LSA = 0; break;       
    case (7):
        module8_LSC = 1; module8_LSB = 1; module8_LSA = 1; break;        
  }
}
main(void)
{
	while(1)
	{		
		chonKey(0); GPIO_DIG=DIG_CODE[0]; module8_delayMS(3);
		chonKey(1); GPIO_DIG=DIG_CODE[2]; module8_delayMS(3);
		chonKey(2); GPIO_DIG=DIG_CODE[0]; module8_delayMS(3);
		chonKey(3);	GPIO_DIG=DIG_CODE[9]; module8_delayMS(3);
		chonKey(4); GPIO_DIG=DIG_CODE[3]; module8_delayMS(3);
		chonKey(5);	GPIO_DIG=DIG_CODE[1];	module8_delayMS(3);
		chonKey(6); GPIO_DIG=DIG_CODE[1];	module8_delayMS(3);
		chonKey(7);	GPIO_DIG=DIG_CODE[2]; module8_delayMS(3);
	}				
}