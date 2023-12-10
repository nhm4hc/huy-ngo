#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg51.h>

// Dinh nghia chan giao tiep voi DS18B20
sbit DSPORT = P3^7;

// Khai bao cac ham
void Delay1ms(unsigned int);  // Ham delay 1ms
unsigned char Ds18b20Init();  // Khoi tao DS18B20
void Ds18b20WriteByte(unsigned char com);  // Viet 1 byte vao DS18B20
unsigned char Ds18b20ReadByte();  // Doc 1 byte tu DS18B20
void Ds18b20ChangTemp();  // Bat dau chuyen doi nhiet do tren DS18B20
void Ds18b20ReadTempCom();  // Gui lenh doc nhiet do tren DS18B20
int Ds18b20ReadTemp();  // Doc gia tri nhiet do tu DS18B20

#endif
