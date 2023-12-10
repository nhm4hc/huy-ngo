#ifndef __MODULE_9_H_
#define __MODULE_9_H_

#include<reg51.h>

#define GPIO_MOTOR P1
#define FF_length 8 

sbit module9_K1=P3^0;
sbit module9_K2=P3^1;
sbit module9_K3=P3^2;
sbit module9_K4=P3^3;

static const unsigned char code FFW[FF_length]={0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9}; //·Xoay cung chieu kim dong ho theo half-step
static const unsigned char code FFZ[FF_length]={0xf9,0xf8,0xfc,0xf4,0xf6,0xf2,0xf3,0xf1}; //Xoay nguoc chieu kim dong ho theo half-step

static unsigned char Direction;
static unsigned char	Speed;

void Motor(void); 
void module9_Delay(unsigned int t);
void module_9(void);

#endif
