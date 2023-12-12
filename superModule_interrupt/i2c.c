#include"i2c.h"

void i2c_Delay10us(void){
	// deplay 10us
	unsigned char a,b;
	for(b=1;b>0;b--)
		for(a=2;a>0;a--);
}

void I2cStart(void){
	// Hàm I2c Start 
	i2c_SDA=1;
	i2c_Delay10us();
	i2c_SCL=1;
	i2c_Delay10us();
	i2c_SDA=0;
	i2c_Delay10us();
	i2c_SCL=0;			
	i2c_Delay10us();		
}

void I2cStop(void){
	i2c_SDA=0;
	i2c_Delay10us();
	i2c_SCL=1;
	i2c_Delay10us();
	i2c_SDA=1;
	i2c_Delay10us();		
}

unsigned char I2cSendByte(unsigned char dat){
	unsigned char a=0,b=0;	
	for(a=0;a<8;a++)
	{
		i2c_SDA = dat>>7;	 
		dat = dat<<1;
		i2c_Delay10us();
		i2c_SCL = 1;
		i2c_Delay10us();
		i2c_SCL = 0;
		i2c_Delay10us();
	}
	i2c_SDA = 1;
	i2c_Delay10us();
	i2c_SCL=1;
	while(i2c_SDA)
	{
		b++;
		if(b>200)	 
		{
			i2c_SCL=0;
			i2c_Delay10us();
			return 0;
		}
	}
	i2c_SCL=0;
	i2c_Delay10us();
 	return 1;		
}

unsigned char I2cReadByte(void)
{
	unsigned char a=0,dat=0;
	i2c_SDA=1;			
	i2c_Delay10us();
	for(a=0;a<8;a++)
	{
		i2c_SCL=1;
		i2c_Delay10us();
		dat<<=1;
		dat|=i2c_SDA;
		i2c_Delay10us();
		i2c_SCL=0;
		i2c_Delay10us();
	}
	return dat;		
}
