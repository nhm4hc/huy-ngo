#include<reg51.h>
#include"lcd.h"
#include"temp.h"

uchar CNCHAR[6] = "…„ œ∂»";

// Ham hien thi len LCD
void LcdDisplay(int);

// Cau hinh USART
void UsartConfiguration();

void main()
{
    UsartConfiguration();  // Cau hinh USART
    LcdInit();             // Khoi tao LCD1602
    LcdWriteCom(0x88);     // Viet dia chi, 80 la dia chi khoi tao

    LcdWriteData('C');
    while(1)
    {
        LcdDisplay(Ds18b20ReadTemp()); // Hien thi nhiet do len LCD
        // Delay1ms(1000); // Delay 1s
    }
}

// Ham LcdDisplay() de hien thi nhiet do doc duoc len LCD
void LcdDisplay(int temp)
{
    unsigned char i, datas[] = {0, 0, 0, 0, 0}; // Mang luu tru gia tri nhiet do
    float tp;
    if(temp < 0) // Khi nhiet do la so am
    {
        LcdWriteCom(0x80); // Viet dia chi, 80 la dia chi khoi tao
        SBUF = '-';        // Gui du lieu am den buffer
        while(!TI);        // Doi gui xong du lieu
        TI = 0;            // Xoa co gui xong

        LcdWriteData('-'); // Hien thi dau '-'
        temp = temp - 1;
        temp = ~temp;
        tp = temp;
        temp = tp * 0.0625 * 100 + 0.5;
    }
    else
    {
        LcdWriteCom(0x80); // Viet dia chi, 80 la dia chi khoi tao
        LcdWriteData('+'); // Hien thi dau '+'
        SBUF = '+';        // Gui du lieu duong den buffer
        while(!TI);        // Doi gui xong du lieu
        TI = 0;            // Xoa co gui xong

        tp = temp;
        temp = tp * 0.0625 * 100 + 0.5;
    }

    // Tinh toan va hien thi cac chu so cua nhiet do
    datas[0] = temp / 10000;
    datas[1] = temp % 10000 / 1000;
    datas[2] = temp % 1000 / 100;
    datas[3] = temp % 100 / 10;
    datas[4] = temp % 10;

    // Hien thi nhiet do
    for(i = 0; i < 5; i++)
    {
        LcdWriteCom(0x82 + i);
        LcdWriteData('0' + datas[i]);
        SBUF = '0' + datas[i];
        while(!TI);
        TI = 0;
    }

    for(i = 0; i < 6; i++)
    {
        SBUF = CNCHAR[i];
        while(!TI);
        TI = 0;
    }
}

// Ham cau hinh USART
void UsartConfiguration()
{
    SCON = 0X50; // Che do lam viec 1
    TMOD = 0X20; // Che do timer 2
    PCON = 0X80; // Tang toc do baud
    TH1 = 0XF3;  // Thiet lap gia tri khoi tao timer, baud rate 4800
    TL1 = 0XF3;
    // ES = 1;  // Mo ngat nhan
    // EA = 1;  // Mo ngat tong
    TR1 = 1;    // Khoi dong timer
}
