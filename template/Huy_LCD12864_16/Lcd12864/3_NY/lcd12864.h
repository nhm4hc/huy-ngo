#ifndef __LCD12864_H
#define __LCD12864_H

//---Bao gom c�c tep ti�u d�`---//
#include<reg51.h>

//---X�c dinh lai tu kh�a---//
#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int
#endif

//---Neu ban su dung che do ve de x�c dinh dieu n�y---//

#define LCD12864_PICTURE

//---X�c dinh cong IO duoc su dung---//

#define LCD12864_DATAPORT P0 // Cong IO du lieu

sbit LCD12864_RS = P2^6; //(lenh du lieu) dang k� lua chon dau v�o
sbit LCD12864_RW = P2^5; //�ieu khien doc/ghi LCD
sbit LCD12864_EN = P2^7; //�ieu khien k�ch hoat tinh the long
sbit LCD12864_PSB = P3^2;//�ieu khien che do noi tiep/song song
sbit LCD12864_RST = P3^4; //�at lai thiet bi dau cuii

//---Khai b�o c�c h�m to�n cuc---//
void LCD12864_Delay1ms(uint c);
uchar LCD12864_Busy(void);
void LCD12864_WriteCmd(uchar cmd);
void LCD12864_WriteData(uchar dat);
void LCD12864_Init();
void LCD12864_ClearScreen(void);
void LCD12864_SetWindow(uchar x, uchar y);
void LCD12864_DrowPic(uchar *a);
void LCD12864_DrowPoint(uchar x, uchar y);

#endif