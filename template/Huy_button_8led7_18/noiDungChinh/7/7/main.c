
#include<REGX52.H>

typedef unsigned int u16;	
typedef unsigned char u8;

//PORT 0 = LED 
#define SMG_A_DP_PORT	P0	

sbit module2_LSA = P2^2;
sbit module2_LSB = P2^3;
sbit module2_LSC = P2^4;

sbit module2_K1 = P3^1;
sbit module2_K2 = P3^0;

unsigned int count;

u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delayMS(unsigned int t);
void ISR_timer0(void);
void smg_display1(void);
void smg_display2(void);

void delayMS(unsigned int t){
		TMOD = 0x01;
		TH0 = 0xFC;
		TL0 = 0x18;
		IE = 0x82;
		count =0;
		TR0 =1;
		while(count < t);
		IE =0;
		TR0 =0;
}

void ISR_timer0(void) interrupt 1{
	TH0 = 0xFC;
	TL0 = 0x18;
	count++;
}

void smg_display1(void){
	u8 i;
	for(i=0;i<8;i++)
	{
	  switch(i)
		{
			case 0: module2_LSC=1; module2_LSB=1; module2_LSA=1; break;
			case 1: module2_LSC=1; module2_LSB=1; module2_LSA=0; break;
			case 2: module2_LSC=1; module2_LSB=0; module2_LSA=1; break;
			case 3: module2_LSC=1; module2_LSB=0; module2_LSA=0; break;
			case 4: module2_LSC=0; module2_LSB=1; module2_LSA=1; break;
			case 5: module2_LSC=0; module2_LSB=1; module2_LSA=0; break;
			case 6: module2_LSC=0; module2_LSB=0; module2_LSA=1; break;
			case 7: module2_LSC=0; module2_LSB=0; module2_LSA=0; break;
		}
		SMG_A_DP_PORT = gsmg_code[i];
		delayMS(1000);
		SMG_A_DP_PORT=0x00;
	}
}

void smg_display2(void){
	u8 i;
	for(i=8;i<18;i++)
	{
	  switch(i)
		{
			case 8: module2_LSC=1; module2_LSB=1; module2_LSA=1; break;
			case 9: module2_LSC=1; module2_LSB=1; module2_LSA=0; break;
			case 10: module2_LSC=1; module2_LSB=0; module2_LSA=1; break;
			case 11: module2_LSC=1; module2_LSB=0; module2_LSA=0; break;
			case 12: module2_LSC=0; module2_LSB=1; module2_LSA=1; break;
			case 13: module2_LSC=0; module2_LSB=1; module2_LSA=0; break;
			case 14: module2_LSC=0; module2_LSB=0; module2_LSA=1; break;
			case 15: module2_LSC=0; module2_LSB=0; module2_LSA=0; break;;
		}
		SMG_A_DP_PORT = gsmg_code[i];
		delayMS(1000);
		SMG_A_DP_PORT=0x00;
	}
}

void main(void)
{	
	while(1)
	{
		if(module2_K1 == 0)
		{
	   	smg_display1();
		}
		if(module2_K2 == 0)
		{
			smg_display2();
		}
	}		
}