#include<reg51.h>
#include"lcd.h"
#include"temp.h"
void LcdDisplay(int);

void main()
{
  LcdInit();           // Khoi tao LCD1602
  LcdWriteCom(0x88);  // Ghi dia chi 80 chi dia chi bat dau
  LcdWriteData('C'); 
  while(1)
  {
    LcdDisplay(Ds18b20ReadTemp());
    // Delay1ms(1000);// Tra 1 giây, cap nhat moi 1 giây
  }
}

void LcdDisplay(int temp)   // lcd hien thi
{
  
    unsigned char datas[] = {0, 0, 0, 0, 0}; // Ðinh nghia mang so
    float tp;  
    if(temp< 0)          // Khi nhiet do là so âm
    {
        LcdWriteCom(0x80);    // Ghi dia chi 80 chi dia chi bat dau
        LcdWriteData('-');    // Hien thi dau tru
        // Vì nhiet do doc duoc là mã bù thuc te, giam 1, sau dó lay mã bù cua giá tri goc
        temp=temp-1;
        temp=~temp;
        tp=temp;
        temp=tp*0.0625*100+0.5;  
        // Ðe lai hai chi so thap phân nhân 100, cong 0.5 de làm tròn
        
    }
    else
    {         
        LcdWriteCom(0x80);    // Ghi dia chi 80 chi dia chi bat dau
        LcdWriteData('+');    // Hien thi dau cong
        tp=temp;
        temp=tp*0.0625*100+0.5;  
        // Tuong tu nhu trên, làm tròn so
    }
    // Chia và lay du du tách tung so và hien thi lên LCD
    datas[0] = temp / 10000;
    datas[1] = temp % 10000 / 1000;
    datas[2] = temp % 1000 / 100;
    datas[3] = temp % 100 / 10;
    datas[4] = temp % 10;

    LcdWriteCom(0x82);      // Ghi dia chi 82
    LcdWriteData('0'+datas[0]); // Hien thi hàng chuc nghìn

    LcdWriteCom(0x83);      // Ghi dia chi 83
    LcdWriteData('0'+datas[1]); // Hien thi hàng nghìn

    LcdWriteCom(0x84);      // Ghi dia chi 84
    LcdWriteData('0'+datas[2]); // Hien thi hàng tram

    LcdWriteCom(0x85);      // Ghi dia chi 85
    LcdWriteData('.');      // HHien thi dau cham

    LcdWriteCom(0x86);      // Ghi dia chi 86
    LcdWriteData('0'+datas[3]); // Hien thi chu so thap phân

    LcdWriteCom(0x87);      // Ghi dia chi 87
    LcdWriteData('0'+datas[4]); // Hien thi chu so thap phân thu hai
}
