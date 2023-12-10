#include "temp.h"  // Bao gom file header cho DS18B20

// Ham tre khoang 1ms
void Delay1ms(unsigned int y)
{
    unsigned int x;
    for(y; y>0; y--)
        for(x=110; x>0; x--);
}

// Ham khoi tao DS18B20
unsigned char Ds18b20Init()
{
    unsigned int i;
    DSPORT=0;  // Dat DS18B20 vao trang thai tre
    i=70;
    while(i--);  // Tre 642us
    DSPORT=1;  // Dat DS18B20 vao trang thai hoat dong
    i=0;
    while(DSPORT)  // Doi DS18B20 tro ve trang thai ban dau
    {
        i++;
        if(i>5000)  // Neu tre qua 5ms
            return 0;  // Khoi tao that bai
    }
    return 1;  // Khoi tao thanh cong
}

// Ham viet mot byte vao DS18B20
void Ds18b20WriteByte(unsigned char dat)
{
    unsigned int i, j;
    for(j=0; j<8; j++)
    {
        DSPORT=0;  // Tre 1us truoc khi viet
        i++;
        DSPORT=dat & 0x01;  // Viet du lieu
        i=6;
        while(i--);  // Tre 68us
        DSPORT=1;  // Tha DSPORT
        dat >>= 1;  // Dich bit de ghi tiep
    }
}

// Ham doc mot byte tu DS18B20
unsigned char Ds18b20ReadByte()
{
    unsigned char byte, bi;
    unsigned int i, j;
    for(j=8; j>0; j--)
    {
        DSPORT=0;  // Tre 1us
        i++;
        DSPORT=1;  // Tha DSPORT
        i++;
        i++;  // Tre 6us de du lieu on dinh
        bi=DSPORT;  // Doc du lieu
        byte = (byte >> 1) | (bi << 7);  // Luu du lieu doc duoc
        i=4;  // Tre 48us
        while(i--);
    }
    return byte;
}

// Ham bat dau qua trinh chuyen doi nhiet do DS18B20
void Ds18b20ChangTemp()
{
    Ds18b20Init();  // Khoi tao DS18B20
    Delay1ms(1);
    Ds18b20WriteByte(0xcc);  // Bo qua lenh ROM
    Ds18b20WriteByte(0x44);  // Lenh chuyen doi nhiet do
}

// Ham bat dau qua trinh doc nhiet do tu DS18B20
void Ds18b20ReadTempCom()
{
    Ds18b20Init();  // Khoi tao DS18B20
    Delay1ms(1);
    Ds18b20WriteByte(0xcc);  // Bo qua lenh ROM
    Ds18b20WriteByte(0xbe);  // Lenh doc nhiet do
}

// Ham doc nhiet do tu DS18B20
int Ds18b20ReadTemp()
{
    int temp=0;
    unsigned char tmh, tml;
    Ds18b20ChangTemp();  // Chuyen doi nhiet do
    Ds18b20ReadTempCom();  // Doc nhiet do
    tml = Ds18b20ReadByte();  // Doc byte thap
    tmh = Ds18b20ReadByte();  // Doc byte cao
    temp = tmh;
    temp <<= 8;
    temp |= tml;
    return temp;  // Tra ve gia tri nhiet do
}
