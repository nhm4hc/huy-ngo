#include"lcd.h"

// Ham delay 1ms
void Lcd1602_Delay1ms(uint c)   // Khong co sai so
{
    uchar a,b;
    for (; c>0; c--)
    {
        for (b=199;b>0;b--)
        {
            for(a=1;a>0;a--);
        }      
    }
}

// Viet lenh vao LCD
#ifndef LCD1602_4PINS   // Neu khong dinh nghia LCD1602_4PINS
void LcdWriteCom(uchar com)    // Viet lenh
{
    LCD1602_E = 0;     // Enable low
    LCD1602_RS = 0;    // Chon lenh
    LCD1602_RW = 0;    // Chon ghi du lieu

    LCD1602_DATAPINS = com;     // Dat lenh vao
    Lcd1602_Delay1ms(1);        // Doi du lieu on dinh

    LCD1602_E = 1;              // Bat dau ghi
    Lcd1602_Delay1ms(5);        // Giu thoi gian
    LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)    // Viet lenh
{
    LCD1602_E = 0;    // Enable low
    LCD1602_RS = 0;   // Chon lenh
    LCD1602_RW = 0;   // Chon ghi du lieu

    LCD1602_DATAPINS = com;    // Gui 4 bit cao
    Lcd1602_Delay1ms(1);

    LCD1602_E = 1;    // Bat dau ghi
    Lcd1602_Delay1ms(5);
    LCD1602_E = 0;

    LCD1602_DATAPINS = com << 4; // Gui 4 bit thap
    Lcd1602_Delay1ms(1);

    LCD1602_E = 1;    // Bat dau ghi
    Lcd1602_Delay1ms(5);
    LCD1602_E = 0;
}
#endif

// Viet du lieu vao LCD
#ifndef LCD1602_4PINS          
void LcdWriteData(uchar dat)            // Viet du lieu
{
    LCD1602_E = 0;    // Enable low
    LCD1602_RS = 1;   // Chon du lieu
    LCD1602_RW = 0;   // Chon ghi du lieu

    LCD1602_DATAPINS = dat; // Dat du lieu vao
    Lcd1602_Delay1ms(1);

    LCD1602_E = 1;   // Bat dau ghi
    Lcd1602_Delay1ms(5);   // Giu thoi gian
    LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)            // Viet du lieu
{
    LCD1602_E = 0;    // Enable low
    LCD1602_RS = 1;   // Chon du lieu
    LCD1602_RW = 0;   // Chon ghi du lieu

    LCD1602_DATAPINS = dat;    // Gui 4 bit cao
    Lcd1602_Delay1ms(1);

    LCD1602_E = 1;    // Bat dau ghi
    Lcd1602_Delay1ms(5);
    LCD1602_E = 0;

    LCD1602_DATAPINS = dat << 4; // Gui 4 bit thap
    Lcd1602_Delay1ms(1);

    LCD1602_E = 1;    // Bat dau ghi
    Lcd1602_Delay1ms(5);
    LCD1602_E = 0;
}
#endif

// Khoi tao LCD
#ifndef LCD1602_4PINS
void LcdInit()                          // Khoi tao LCD
{
    LcdWriteCom(0x38);  // Bat hien thi
    LcdWriteCom(0x0c);  // Hien thi khong co con tro
    LcdWriteCom(0x06);  // Ghi mot ky tu, tro tang 1
    LcdWriteCom(0x01);  // Xoa man hinh
    LcdWriteCom(0x80);  // Dat con tro ve dau dong
}
#else
void LcdInit()                          // Khoi tao LCD
{
    LcdWriteCom(0x32);   // Chuyen tu 8 bit sang 4 bit
    LcdWriteCom(0x28);   // Khoi tao o che do 4 bit
    LcdWriteCom(0x0c);  // Hien thi khong co con tro
    LcdWriteCom(0x06);  // Ghi mot ky tu, tro tang 1
    LcdWriteCom(0x01);  // Xoa man hinh
    LcdWriteCom(0x80);  // Dat con tro ve dau dong
}
#endif
