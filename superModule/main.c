#include "LCD1602.h"
#include "displayLCD.h"
//#include ""
void main(void){
	IrInit();
	LcdInit();
	displayLCD();
	while(1){
		signalRecieved();
	}
}