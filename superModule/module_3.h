#ifndef __MODULE_3_H_ 
#define __MODULE_3_H_

#include<reg51.h>
#include"i2c.h"

#define DIG	P0
#define DIG_CODE_length 10
#define disp_length 8

sbit module3_LSA = P2^2;
sbit module3_LSB = P2^3;
sbit module3_LSC = P2^4;

sbit module3_K1 = P3^1;
sbit module3_K2 = P3^0;
sbit module3_K3 = P3^2;
sbit module3_K4 = P3^3;

static const unsigned char code DIG_CODE[DIG_CODE_length]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
static unsigned char Num;
static unsigned char disp[disp_length]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};

void At24c02Write(unsigned char ,unsigned char);
unsigned char At24c02Read(unsigned char );
void module3_Delay1ms(void);
void Timer0Configuration(void);
void module_3(void);

#endif
