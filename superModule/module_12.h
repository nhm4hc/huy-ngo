#ifndef __MODULE_12_H_
#define __MODULE_12_H_

#include<reg51.h>
#include<intrins.h>	//dung de dich trai phai

#define GPIO_LED P2

sbit module12_K1 = P3^1;

static unsigned int i;
static unsigned char j;

void module12_Delay10ms(void);  
void module_12(void);
#endif
