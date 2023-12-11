#include "interruptPublish.h"
#include "module_2.h"

unsigned char c_interrupt = 0;

void timer0(void) interrupt 1{
	
	if(CHECK_BIT(c_interrupt,MODULE_0))
	{
		TH0 = 0xFC;
		TL0 = 0x18;
		module2_count++;
	}
}
