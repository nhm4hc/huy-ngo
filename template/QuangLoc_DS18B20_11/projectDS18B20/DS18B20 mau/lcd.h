#ifndef __LCD_H_  // Kiem tra xem da dinh nghia __LCD_H_ chua, ngan chan dinh nghia trung lap
#define __LCD_H_  // Dinh nghia __LCD_H_ neu chua duoc dinh nghia

// Dinh nghia cho viec su dung LCD 1602 voi 4 chan ket noi
#define LCD1602_4PINS

#include<reg51.h>  // Bao gom thu vien cho vi dieu khien 8051

// Dinh nghia kieu du lieu uchar neu chua duoc dinh nghia
#ifndef uchar
#define uchar unsigned char
#endif

// Dinh nghia kieu du lieu uint neu chua duoc dinh nghia
#ifndef uint 
#define uint unsigned int
#endif

// Dinh nghia cac chan ket noi va cong cho LCD
#define LCD1602_DATAPINS P0  // Cac chan du lieu cua LCD ket noi den cong P0
sbit LCD1602_E=P2^7;  // Chan Enable ket noi toi bit thu 7 cua cong P2
sbit LCD1602_RW=P2^5;  // Chan Read/Write ket noi toi bit thu 5 cua cong P2
sbit LCD1602_RS=P2^6;  // Chan Register Select ket noi toi bit thu 6 cua cong P2

// Khai bao cac ham su dung trong viec dieu khien LCD
void Lcd1602_Delay1ms(uint c);   // Ham delay
void LcdWriteCom(uchar com);     // Ham gui lenh cho LCD
void LcdWriteData(uchar dat);    // Ham gui du lieu cho LCD
void LcdInit();                  // Ham khoi tao LCD

#endif  // Ket thuc cua dieu kien ifndef
