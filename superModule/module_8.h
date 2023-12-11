#ifndef __MODULE_8_H_
#define __MODULE_8_H_

#include<reg51.h>

#define GPIO_DIG P0

sbit module8_LSA=P2^2;
sbit module8_LSB=P2^3;
sbit module8_LSC=P2^4;

//unsigned char code hello[5]={0x76,0x79,0x3f,0x38,0x00}; //H,E,O,L
static const unsigned char code DIG_CODE_8[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f}; // Mang so tu 0 - 9

void module8_delayMS(unsigned int t);
void chonKey(unsigned int k);
void module_8(void);

#endif
