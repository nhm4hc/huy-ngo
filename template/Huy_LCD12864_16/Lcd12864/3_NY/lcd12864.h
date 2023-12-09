#ifndef __LCD12864_H
#define __LCD12864_H

//---Bao gom các tep tiêu dê`---//
#include<reg51.h>

//---Xác dinh lai tu khóa---//
#ifndef uchar
#define uchar unsigned char 
#endif

#ifndef uint
#define uint unsigned int
#endif

//---Neu ban su dung che do ve de xác dinh dieu này---//

#define LCD12864_PICTURE

//---Xác dinh cong IO duoc su dung---//

#define LCD12864_DATAPORT P0 // Cong IO du lieu

sbit LCD12864_RS = P2^6; //(lenh du lieu) dang ký lua chon dau vào
sbit LCD12864_RW = P2^5; //Ðieu khien doc/ghi LCD
sbit LCD12864_EN = P2^7; //Ðieu khien kích hoat tinh the long
sbit LCD12864_PSB = P3^2;//Ðieu khien che do noi tiep/song song
sbit LCD12864_RST = P3^4; //Ðat lai thiet bi dau cuii

//---Khai báo các hàm toàn cuc---//
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