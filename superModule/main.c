#include "LCD1602.h"
#include "displayLCD.h"
//#include "module_1.h"

void main(void){
	IrInit();
	LcdInit();
	displayLCD();
	//LCD12864_Init();
	
	while(1){
		signalRecieved();
	}
}