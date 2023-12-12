#include "interruptPublish.h"
#include "module_1.h"
#include "module_2.h"
//#include "module_3.h"
//#include "module_4.h"
#include "module_5.h"
//#include "module_6.h"

unsigned char c_interrupt = 0;

void interrupt_module1(void){
		TH1 = 0xFF;
		TL1 = 0xFf;
		module1_timer1++;
		module1_count++;
}

void interrupt_module2(void){
		TH0 = 0xFC;
		TL0 = 0x18;
		count++;
}
/*
void interrupt_module3(void){
	DIG=0; 
	switch(Num)	 
	{
		case(7):
			module13_LSA=0; module13_LSB=0; module13_LSC=0; break;
		case(6):
			module13_LSA=1; module13_LSB=0; module13_LSC=0; break;
		case(5):
			module13_LSA=0; module13_LSB=1; module13_LSC=0; break;
		case(4):
			module13_LSA=1; module13_LSB=1; module13_LSC=0; break;
		case(3):
			module13_LSA=0; module13_LSB=0; module13_LSC=1; break;
		case(2):
			module13_LSA=1; module13_LSB=0; module13_LSC=1; break;
		case(1):
			module13_LSA=0; module13_LSB=1; module13_LSC=1; break;
		case(0):
			module13_LSA=1; module13_LSB=1; module13_LSC=1; break;	
	}
	DIG = disp[Num]; 
	Num++;
	if(Num>7)
		Num=0;
}
*/

/*
void interrupt_module4(void){
		TH1 = 0xFE;  
		TL1 = 0x0C;
		module4_timer1++;
}
*/

void interrupt_module5(void){
		TH0 = 0x3C;	 
		TL0 = 0xB0;
		module5_Time++;
}

/*
void interrupt_module6(void){
		TH0 = 0xd8;   
		TL0 = 0xef;   
		module6_n--; 
}
*/

void timer0(void) interrupt 1{
	
	if(CHECK_BIT(c_interrupt,MODULE_1))
	{
		interrupt_module2();
	}
	
	/*
	if(CHECK_BIT(c_interrupt,MODULE_2))
	{
		interrupt_module3();
	}
	*/
	
	if(CHECK_BIT(c_interrupt,MODULE_4))
	{
		interrupt_module5();
	}
	
	/*
	if(CHECK_BIT(c_interrupt,MODULE_5))
	{
		 interrupt_module6();
	}
	*/
}

void Time1(void) interrupt 3{
	
	if(CHECK_BIT(c_interrupt,MODULE_0))
	{
		interrupt_module1();
	}
	/*
	if(CHECK_BIT(c_interrupt,MODULE_3))
	{
		interrupt_module4();
	}
	*/
	
}






