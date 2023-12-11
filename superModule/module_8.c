#include "module_8.h"

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

void module_8(void){
	chonKey(0); GPIO_DIG = DIG_CODE_8[0]; module8_delayMS(3);
	chonKey(1); GPIO_DIG = DIG_CODE_8[2]; module8_delayMS(3);
	chonKey(2); GPIO_DIG = DIG_CODE_8[0]; module8_delayMS(3);
	chonKey(3);	GPIO_DIG = DIG_CODE_8[9]; module8_delayMS(3);
	chonKey(4); GPIO_DIG = DIG_CODE_8[3]; module8_delayMS(3);
	chonKey(5);	GPIO_DIG = DIG_CODE_8[1];	module8_delayMS(3);
	chonKey(6); GPIO_DIG = DIG_CODE_8[1];	module8_delayMS(3);
	chonKey(7);	GPIO_DIG = DIG_CODE_8[2]; module8_delayMS(3);
}