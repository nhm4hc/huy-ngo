#ifndef __LCD12864_H
#define __LCD12864_H

#include<reg51.h>

#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int
#endif

#define LCD12864_PICTURE

#define LCD12864_DATAPORT P0 

sbit LCD12864_RS = P2^6; 
sbit LCD12864_RW = P2^5; 
sbit LCD12864_EN = P2^7; 
sbit LCD12864_PSB = P3^2;
sbit LCD12864_RST = P3^4; 

void LCD12864_Delay1ms(uint c);
uchar LCD12864_Busy(void);
void LCD12864_WriteCmd(uchar cmd);
void LCD12864_WriteData(uchar dat);
void LCD12864_Init(void);
void LCD12864_DrowPic(uchar *a);

#endif