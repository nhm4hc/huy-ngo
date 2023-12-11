#include"temp.h"

// Hàm delay 1ms
void Delay1ms(unsigned int y)
{
    unsigned int x;
    for(y; y > 0; y--)
        for(x = 110; x > 0; x--);
}

// Kh?i t?o DS18B20
unsigned char Ds18b20Init()
{
    unsigned int i;
    EA = 0;  // T?t ng?t toàn c?c
    DSPORT = 0;  // Kéo chân DSPORT xu?ng th?p t? 480us d?n 960us
    i = 70;  
    while(i--);  // Delay 642us
    DSPORT = 1;  // Kéo chân DSPORT lên cao
    i = 0;
    EA = 1;  // B?t ng?t toàn c?c
    while(DSPORT)  // Ð?i DS18B20 kéo chân DSPORT xu?ng th?p
    {
        i++;
        if(i > 5000)  // Ð?i quá 5ms
            return 0;  // Kh?i t?o th?t b?i
    }
    return 1;  // Kh?i t?o thành công
}

// Vi?t 1 byte vào DS18B20
void Ds18b20WriteByte(unsigned char dat)
{
    unsigned int i, j;
    EA = 0;  // T?t ng?t toàn c?c
    for(j = 0; j < 8; j++)
    {
        DSPORT = 0;  // Kéo chân DSPORT xu?ng th?p 1us tru?c khi vi?t
        i++;
        DSPORT = dat & 0x01;  // Vi?t 1 bit d? li?u t? bit th?p nh?t
        i = 6;
        while(i--);  // Delay 68us
        DSPORT = 1;  // Th? chân DSPORT lên cao
        dat >>= 1;   // D?ch ph?i d? li?u d? vi?t bit ti?p theo
    }
    EA = 1;  // B?t ng?t toàn c?c
}

// Ð?c 1 byte t? DS18B20
unsigned char Ds18b20ReadByte()
{
    unsigned char byte, bi;
    unsigned int i, j;
    EA = 0;  // T?t ng?t toàn c?c
    for(j = 8; j > 0; j--)
    {
        DSPORT = 0;  // Kéo chân DSPORT xu?ng th?p 1us
        i++;
        DSPORT = 1;  // Th? chân DSPORT lên cao
        i++; i++;    // Delay 6us d? d?i d? li?u ?n d?nh
        bi = DSPORT;  // Ð?c d? li?u t? bit th?p nh?t
        byte = (byte >> 1) | (bi << 7);  // D?ch ph?i byte và thêm bit v?a d?c vào v? trí cao nh?t
        i = 4;  // Delay 48us tru?c khi d?c byte ti?p theo
        while(i--);
    }
    EA = 1;  // B?t ng?t toàn c?c
    return byte;
}

// B?t d?u quá trình d?i nhi?t d? trên DS18B20
void Ds18b20ChangTemp()
{
    Ds18b20Init();
    Delay1ms(1);
    Ds18b20WriteByte(0xcc);  // G?i l?nh b? qua ROM
    Ds18b20WriteByte(0x44);  // G?i l?nh chuy?n d?i nhi?t d?
    Delay1ms(100);  // Ð?i quá trình chuy?n d?i hoàn t?t, không c?n n?u liên t?c c?p nh?t nhi?t d?
}

// G?i l?nh d?c nhi?t d? t? DS18B20
void Ds18b20ReadTempCom()
{
    Ds18b20Init();
    Delay1ms(1);
    Ds18b20WriteByte(0xcc);  // G?i l?nh b? qua ROM
    Ds18b20WriteByte(0xbe);  // G?i l?nh d?c nhi?t d?
}

// Ð?c giá tr? nhi?t d? t? DS18B20
int Ds18b20ReadTemp()
{
    int temp = 0;
    unsigned char tmh, tml;
    Ds18b20ChangTemp();  // B?t d?u quá trình chuy?n d?i nhi?t d?
    Ds18b20ReadTempCom();  // G?i l?nh d?c nhi?t d?
    tml = Ds18b20ReadByte();  // Ð?c byte th?p c?a nhi?t d?
    tmh = Ds18b20ReadByte();  // Ð?c byte cao c?a nhi?t d?
    temp = tmh;
    temp <<= 8;
    temp |= tml;
    return temp;  // Tr? v? giá tr? nhi?t d?
}
