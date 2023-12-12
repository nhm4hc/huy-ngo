#ifndef __MODULE_5_H_ 
#define __MODULE_5_H_

#include<reg51.h>
#include<intrins.h>

#define GPIO_LED_6 P2

extern unsigned char module5_Time;

void TimerConfiguration(void);
void module_5(void);

#endif
