#include "module_15.h"

void module15_Delay10ms(unsigned int c) {
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}

void module_15(void){
	LED_DON  = 0x00;//led tat het 
	module15_Delay10ms(50);//delay 500ms 
	LED_DON  = 0xff;//led sang het
	module15_Delay10ms(50);//delay 500ms
}