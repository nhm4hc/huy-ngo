#include"temp.h"

// Ham delay 1ms
void Delay1ms(unsigned int y)
{
    unsigned int x;
    for(y; y > 0; y--)
        for(x = 110; x > 0; x--);
}

// Ham khoi tao DS18B20
unsigned char Ds18b20Init()
{
    unsigned int i;
    DSPORT = 0;          // Keo chan xuong thap trong 480us~960us
    i = 70;
    while(i--);          // Delay 642us
    DSPORT = 1;          // Keo chan len cao
    i = 0;
    while(DSPORT)        // Doi DS18B20 keo chan xuong thap
    {
        i++;
        if(i > 5000)     // Neu doi qua 5ms
            return 0;    // Khoi tao that bai
    }
    return 1;            // Khoi tao thanh cong
}

// Viet 1 byte vao DS18B20
void Ds18b20WriteByte(unsigned char dat)
{
    unsigned int i, j;
    for(j = 0; j < 8; j++)
    {
        DSPORT = 0;      // Keo chan xuong thap 1us truoc khi viet
        i++;
        DSPORT = dat & 0x01; // Viet 1 bit du lieu
        i = 6;
        while(i--);      // Delay 68us
        DSPORT = 1;      // Tha chan len cao
        dat >>= 1;       // Dich phai de viet bit tiep theo
    }
}

// Doc 1 byte tu DS18B20
unsigned char Ds18b20ReadByte()
{
    unsigned char byte, bi;
    unsigned int i, j;
    for(j = 8; j > 0; j--)
    {
        DSPORT = 0;     // Keo chan xuong thap 1us
        i++;
        DSPORT = 1;     // Tha chan len cao
        i++; i++;       // Delay 6us de doi du lieu on dinh
        bi = DSPORT;    // Doc du lieu
        byte = (byte >> 1) | (bi << 7); // Dich trai byte va them bit vao vi tri cao nhat
        i = 4;          // Delay 48us truoc khi doc byte tiep theo
        while(i--);
    }
    return byte;
}

// Bat dau chuyen doi nhiet do tren DS18B20
void Ds18b20ChangTemp()
{
    Ds18b20Init();
    Delay1ms(1);
    Ds18b20WriteByte(0xcc); // Bo qua ROM
    Ds18b20WriteByte(0x44); // Lenh chuyen doi nhiet do
    // Delay1ms(100); Neu lien tuc lay nhiet do thi khong can delay
}

// Gui lenh doc nhiet do tren DS18B20
void Ds18b20ReadTempCom()
{
    Ds18b20Init();
    Delay1ms(1);
    Ds18b20WriteByte(0xcc); // Bo qua ROM
    Ds18b20WriteByte(0xbe); // Lenh doc nhiet do
}

// Doc gia tri nhiet do tu DS18B20
int Ds18b20ReadTemp()
{
    int temp = 0;
    unsigned char tmh, tml;
    Ds18b20ChangTemp();         // Bat dau chuyen doi nhiet do
    Ds18b20ReadTempCom();       // Gui lenh doc nhiet do
    tml = Ds18b20ReadByte();    // Doc byte thap cua nhiet do
    tmh = Ds18b20ReadByte();    // Doc byte cao cua nhiet do
    temp = tmh;
    temp <<= 8;
    temp |= tml;
    return temp;                // Tra ve gia tri nhiet do
}
