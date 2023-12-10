#ifndef __LCD_H_
#define __LCD_H_

// Neu su dung truyen du lieu 4 bit thi dinh nghia, bo qua neu su dung 8 bit
#define LCD1602_4PINS

// Goi thu vien
#include<reg51.h>

// Dinh nghia kieu du lieu
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

// Dinh nghia cac chan giao tiep voi LCD
#define LCD1602_DATAPINS P0
sbit LCD1602_E = P2^7;   // Chan Enable
sbit LCD1602_RW = P2^5;  // Chan Read/Write
sbit LCD1602_RS = P2^6;  // Chan Register Select

// Khai bao cac ham
/* Ham delay trong 51 single-chip microcomputer voi toc do 12MHZ */
void Lcd1602_Delay1ms(uint c);   // Delay 1ms, sai so 0us

/* Ham ghi lenh 8 bit vao LCD1602 */
void LcdWriteCom(uchar com);

/* Ham ghi du lieu 8 bit vao LCD1602 */
void LcdWriteData(uchar dat);

/* Ham khoi tao LCD1602 */
void LcdInit();

#endif
