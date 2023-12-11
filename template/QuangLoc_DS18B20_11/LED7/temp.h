#ifndef __TEMP_H_
#define __TEMP_H_

#include<reg51.h>

// �?nh nghia ch�n k?t n?i v?i c?m bi?n nhi?t d? DS18B20
sbit DSPORT = P3^7;

// Khai b�o c�c h�m
void Delay1ms(unsigned int);  // H�m delay 1ms
unsigned char Ds18b20Init();  // Kh?i t?o c?m bi?n DS18B20
void Ds18b20WriteByte(unsigned char com);  // Ghi m?t byte v�o DS18B20
unsigned char Ds18b20ReadByte();  // �?c m?t byte t? DS18B20
void Ds18b20ChangTemp();  // B?t d?u qu� tr�nh chuy?n d?i nhi?t d? tr�n DS18B20
void Ds18b20ReadTempCom();  // G?i l?nh d?c nhi?t d? tr�n DS18B20
int Ds18b20ReadTemp();  // �?c gi� tr? nhi?t d? t? DS18B20

#endif
