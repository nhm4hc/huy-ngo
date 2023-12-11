#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg51.h>

// Ð?nh nghia chân k?t n?i v?i c?m bi?n nhi?t d? DS18B20
sbit DSPORT = P3^7;

// Khai báo các hàm
void Delay1ms(unsigned int);  // Hàm delay 1ms
unsigned char Ds18b20Init();  // Kh?i t?o c?m bi?n DS18B20
void Ds18b20WriteByte(unsigned char com);  // Ghi m?t byte vào DS18B20
unsigned char Ds18b20ReadByte();  // Ð?c m?t byte t? DS18B20
void Ds18b20ChangTemp();  // B?t d?u quá trình chuy?n d?i nhi?t d? trên DS18B20
void Ds18b20ReadTempCom();  // G?i l?nh d?c nhi?t d? trên DS18B20
int Ds18b20ReadTemp();  // Ð?c giá tr? nhi?t d? t? DS18B20

#endif
