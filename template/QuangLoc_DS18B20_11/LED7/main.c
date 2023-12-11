#include<reg51.h>
#include"temp.h"

// Cac chan giao tiep voi man hinh LED 7 doan
#define DIG P0

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;

// Ma LED 7 doan tuong ung voi cac chu so tu 0 den 9
unsigned char code DIG_CODE[10] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
unsigned char Num = 0;
unsigned int disp[8] = {0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f};

// Khai bao cac ham
void LcdDisplay(int temp);
void Timer0Configuration(void);
void DigDisplay(void);

// Ham hien thi nhiet do len LCD
void LcdDisplay(int temp){
    unsigned char datas[] = {0, 0, 0, 0, 0}; // Mang luu tru gia tri nhiet do
    float tp;
    if(temp < 0) // Neu nhiet do la so am
    {
        disp[2] = 0x40; // Hien thi dau '-'
        temp = temp - 1;
        temp = ~temp;
        tp = temp;
        temp = tp * 0.0625 * 100 + 0.5;
    }
    else
    {
        disp[2] = 0; // Khong hien thi dau
        tp = temp; 
        temp = tp * 0.0625 * 100 + 0.5;
    }

    // Chuyen doi gia tri nhiet do thanh ma hien thi tren LED 7 doan
    disp[0] = 0;
    disp[1] = 0;
    disp[3] = DIG_CODE[temp / 10000];
    disp[4] = DIG_CODE[temp % 10000 / 1000];
    disp[5] = DIG_CODE[temp % 1000 / 100] | 0x80; // Them dau '.' vao gia tri
    disp[6] = DIG_CODE[temp % 100 / 10];
    disp[7] = DIG_CODE[temp % 10];
}

// Cau hinh Timer 0
void Timer0Configuration(void){
    TMOD = 0X02; // Chon che do Timer, che do 2

    TH0 = 0X9C;  // Gia tri khoi tao cho Timer, 100us
    TL0 = 0X9C;  
    ET0 = 1;     // Bat ngat Timer 0
    EA = 1;      // Bat ngat toan cuc
    TR0 = 1;     // Khoi dong Timer 0
}

// Ham ngat Timer 0 de hien thi tren man hinh LED 7 doan
void DigDisplay(void) interrupt 1{
    DIG = 0; // Tat hien thi
    switch(Num)  
    {
        case(7):
            LSA = 0; LSB = 0; LSC = 0; break;
        case(6):
            LSA = 1; LSB = 0; LSC = 0; break;
        case(5):
            LSA = 0; LSB = 1; LSC = 0; break;
        case(4):
            LSA = 1; LSB = 1; LSC = 0; break;
        case(3):
            LSA = 0; LSB = 0; LSC = 1; break;
        case(2):
            LSA = 1; LSB = 0; LSC = 1; break;
        case(1):
            LSA = 0; LSB = 1; LSC = 1; break;
        case(0):
            LSA = 1; LSB = 1; LSC = 1; break; 
    }
    DIG = disp[Num]; 
    Num++;
    if(Num > 7)
        Num = 0;
}

void main()
{
    Timer0Configuration();
    while(1)
    {
        LcdDisplay(Ds18b20ReadTemp());
    }
}
