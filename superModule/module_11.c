#include "module_11.h"

void module11_delay(unsigned int time){
  unsigned int i,j;
  for(i=0;i<time;i++)
    for(j=0;j<121;j++);
}

void Hc595SendByte(unsigned char dat){
	unsigned char a;
	module11_SRCLK=0;
	module11_RCLK=0;
	for(a=0;a<8;a++)
	{
		module11_SER=dat>>7;
		dat<<=1;
		module11_SRCLK=1;
		_nop_();
		_nop_();
		module11_SRCLK=0;    
	}
	module11_RCLK=1;
	_nop_();
	_nop_();
	module11_RCLK=0;
}

void module_11(void){
	unsigned char tab, j;
  unsigned int  i;
	for(i= 0; i<50; i++)
  {
     for(tab=0;tab<TAB_length;tab++)
     {   
        Hc595SendByte(0x00);                 
        COMMONPORTS = TAB[tab];              
        Hc595SendByte(CHARCODE[j][tab]);    
        module11_delay(2);       
     }
  }
  j++;
  if(j == 18)
  {
     j = 0;
  }
}