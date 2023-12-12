#ifndef __DISPLAY_LCD_H_
#define __DISPLAY_LCD_H_

#include<reg51.h>

sbit IRIN = P3^2; //Gan chan P3.2 co ten la IRIN

#define CDIS_length 9
#define IrValue_length 6

static const unsigned char code CDIS1[CDIS_length]={"Module: "};
static const unsigned char code CDIS2[CDIS_length]={"Nhap mode"};
static const unsigned char code CDIS3[CDIS_length]={"Dang chay"};
static const unsigned char code CDIS4[CDIS_length]={"Out range"};
static unsigned char IrValue[IrValue_length];
static unsigned char Time;
static unsigned int checkRun;
static unsigned int module;
static unsigned int nutBam;

void IrInit(void);
void DelayMs(unsigned int x);
void ReadIr(void);
void hienThiChuc(int x);
void hienThiDonVi(int x);
void reset(void);
void xuLi(int x);
void runModule(int x);
void disableInterrupt(void);
void displayLCD(void);
void signalRecieved(void);

#endif
