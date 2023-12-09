#ifndef __LCD_H_
#define __LCD_H_

#define LCD1602_4PINS

/**********************************
Dinh nghia cac bien
**********************************/
#include<reg51.h>

#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

/**********************************
Dinh nghia cac chan IO
**********************************/
#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/**********************************
Dinh nghia cac chuong trinh chinh
**********************************/
void Lcd1602_Delay1ms(uint c);
void LcdWriteCom(uchar com);	
void LcdWriteData(uchar dat)	;
void LcdInit();						  

#endif
