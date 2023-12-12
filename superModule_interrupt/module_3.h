#ifndef __MODULE_3_H_ 
#define __MODULE_3_H_

#include<reg51.h>
#include"ds1302.h"

#define DIG	P0

sbit module13_LSA = P2^2;
sbit module13_LSB = P2^3;
sbit module13_LSC = P2^4;

static const unsigned char code DIG_CODE_13[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
extern unsigned char Num;
extern unsigned int disp[8];

void Timer0Configuration(void);
void DigDisplay(void);

#endif
