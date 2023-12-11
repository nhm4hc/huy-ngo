#include "module_2.h"

unsigned int module2_count = 0;

void module2_delayMS(unsigned int t){
	TMOD = 0x01;
	TH0 = 0xFC;
	TL0 = 0x18;
	ET0 = 1;
	EA = 1;
	module2_count =0;
	TR0 =1;
	while(module2_count < t);
	ET0 = 0;
	TR0 =0;
}

void timer0(void) interrupt 1{
		TH0 = 0xFC;
		TL0 = 0x18;
		module2_count++;
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
		module2_delayMS(1000);
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
		module2_delayMS(1000);
		SMG_A_DP_PORT=0x00;
	}
}

void module_2(void){
	
	if(module2_K1 == 0)
	{
   	smg_display1();
	}
	if(module2_K2 == 0)
	{
		smg_display2();
	}
}