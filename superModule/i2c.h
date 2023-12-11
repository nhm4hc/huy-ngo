#ifndef __I2C_H_ 
#define __I2C_H_

#include<reg51.h>

sbit i2c_SCL = P2^1;
sbit i2c_SDA = P2^0;

void i2c_Delay10us(void);
void I2cStart(void);
void I2cStop(void);
unsigned char I2cSendByte(unsigned char dat);
unsigned char I2cReadByte(void);
void I2cReadRespon(void);

#endif
