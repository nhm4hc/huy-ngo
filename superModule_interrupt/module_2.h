#ifndef __MODULE_2_H_
#define __MODULE_2_H_

#include<reg51.h>

typedef unsigned int u16;	
typedef unsigned char u8;

//PORT 0 = LED 
#define SMG_A_DP_PORT	P0	

sbit module2_LSA = P2^2;
sbit module2_LSB = P2^3;
sbit module2_LSC = P2^4;

sbit module2_K1 = P3^1;
sbit module2_K2 = P3^0;

extern unsigned int count;

static const u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void delayMS(unsigned int t);
void smg_display1(void);
void smg_display2(void);
void module_2(void);

#endif
