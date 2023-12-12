#include "module_3.h"
#include "interruptPublish.h"

unsigned char Num = 0;
unsigned int disp[8]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};

void Timer0Configuration(){
	SET_BIT(c_interrupt,MODULE_2);
	TMOD=0X02;
	TH0=0X9C;	
	TL0=0X9C;	
	ET0=1;
	EA=1;
	TR0=1;	
}

void module_3(void){
	Ds1302Init();
  Timer0Configuration();
	Ds1302ReadTime();
	disp[7] = DIG_CODE_13[TIME[0]&0x0f];
	disp[6] = DIG_CODE_13[TIME[0]>>4];
	disp[5] = 0X40;
	disp[4] = DIG_CODE_13[TIME[1]&0x0f];
	disp[3] = DIG_CODE_13[TIME[1]>>4];
	disp[2] = 0X40;
	disp[1] = DIG_CODE_13[TIME[2]&0x0f];
	disp[0] = DIG_CODE_13[TIME[2]>>4];
}