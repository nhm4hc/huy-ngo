#include "module_3.h"
#include "interruptPublish.h"

void At24c02Write(unsigned char addr,unsigned char dat){
	I2cStart();
	I2cSendByte(0xa2);//·// ten eeprom
	I2cSendByte(addr);//·dia chi trong eeprom
	I2cSendByte(dat);	//·data eeprom
	I2cStop();
}

unsigned char At24c02Read(unsigned char addr){
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa2); 
	I2cSendByte(addr); 
	I2cStart();
	I2cSendByte(0xa3); 
	num = I2cReadByte(); 
	I2cStop();
	return num;	
}

void module3_Delay1ms(void)   
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}

void Timer0Configuration(void){
	SET_BIT(c_interrupt,MODULE_1);
	Num = 0;
	TMOD=0X02;
	TH0=0X9C;	
	TL0=0X9C;	
	ET0=1;
	EA=1;
	TR0=1;	
}

void module_3(void){
	unsigned int num0 = 0, num1 = 0, n = 0;
	Timer0Configuration();
	if(module3_K1==0)   // ghi giá tri vào eeprom
	{
		module3_Delay1ms();
		if(module3_K1==0)
			At24c02Write(2,num0);
		while((n<200)&&(module3_K3==0))
		{
			n++;
			module3_Delay1ms();	
		}			
		n=0;
		n=0;
	}
		
	if(module3_K2 == 0)		// doc giá tri tu eeprom
	{
		module3_Delay1ms();
		if(module3_K2 == 0)
			num0=At24c02Read(2);
		while((n<200)&&(module3_K3 == 0))
		{
			n++;
			module3_Delay1ms();	
		}			
		n=0;
	}			
	if(module3_K3 == 0)
	{
		module3_Delay1ms();
		if(module3_K3 == 0)
			num0++;
		while((n<200)&&(module3_K3 == 0))
		{
			n++;
			module3_Delay1ms();	
		}			
		n=0;
		if(num0==256)
			num0=0;
	}
			
	if(module3_K4==0)
	{
		module3_Delay1ms();
		if(module3_K4==0)
			num0=0;
		while((n<200)&&(module3_K3==0))
		{
			n++;
			module3_Delay1ms();	
		}			
		n=0;
	}			
	disp[0]=DIG_CODE[num1/1000];//Ç§Î»
	disp[1]=DIG_CODE[num1%1000/100];//°ÙÎ»
	disp[2]=DIG_CODE[num1%1000%100/10];//Ê®Î»
	disp[3]=DIG_CODE[num1%1000%100%10];//¸öÎ»
	disp[4]=DIG_CODE[num0/1000];//Ç§Î»
	disp[5]=DIG_CODE[num0%1000/100];//°ÙÎ»
	disp[6]=DIG_CODE[num0%1000%100/10];//¸öÎ»
	disp[7]=DIG_CODE[num0%1000%100%10];
}