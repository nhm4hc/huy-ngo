#ifndef __MODULE_1_H_
#define __MODULE_1_H_

#include<reg51.h>

sbit module1_PWM = P2^1;
static bit DIR;

static unsigned int module1_count, value, module1_timer1;

void Time1Config(void);
void module_1(void);

#endif
