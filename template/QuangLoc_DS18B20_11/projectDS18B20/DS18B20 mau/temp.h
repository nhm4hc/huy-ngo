#ifndef __TEMP_H_  // Kiem tra xem __TEMP_H_ da duoc dinh nghia chua, ngan chan dinh nghia trung lap
#define __TEMP_H_  // Dinh nghia __TEMP_H_ neu chua duoc dinh nghia

#include<reg51.h>  // Bao gom thu vien cho vi dieu khien 8051

sbit DSPORT=P3^7;  // Dinh nghia chan giao tiep voi DS18B20, noi voi bit 7 cua cong P3

// Khai bao cac ham su dung trong viec tuong tac voi cam bien DS18B20
void Delay1ms(unsigned int );  // Ham delay khoang 1ms
unsigned char Ds18b20Init();  // Ham khoi tao cam bien DS18B20
void Ds18b20WriteByte(unsigned char com);  // Ham gui mot byte du lieu toi DS18B20
unsigned char Ds18b20ReadByte();  // Ham doc mot byte du lieu tu DS18B20
void Ds18b20ChangTemp();  // Ham bat dau qua trinh do nhiet do
void Ds18b20ReadTempCom();  // Ham gui lenh doc nhiet do tu DS18B20
int Ds18b20ReadTemp();  // Ham doc gia tri nhiet do tu DS18B20

#endif  // Ket thuc cua dieu kien ifndef
