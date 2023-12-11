#ifndef __MODULE_4_H_
#define __MODULE_4_H_

#include<reg51.h>

sbit module4_PWM = P2^0;

static unsigned char module4_timer1; 

void module4_Time1Config(void);
void module4_Time1(void);
void module_4(void);

#endif
