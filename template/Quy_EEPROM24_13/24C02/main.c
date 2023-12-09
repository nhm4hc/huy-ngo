/*******************************************************************************
* ÊµÑéÃû			  : EEPROMÊµÑé
* Ê¹ÓÃµÄIO	    : 
* ÊµÑéĞ§¹û      : °´K1±£´æÏÔÊ¾µÄÊı¾İ£¬°´K2¶ÁÈ¡ÉÏ´Î±£´æµÄÊı¾İ£¬°´K3ÏÔÊ¾Êı¾İ¼ÓÒ»£¬
*°´K4ÏÔÊ¾Êı¾İÇåÁã¡£
*	×¢Òâ					£ºÓÉÓÚP3.2¿Ú¸úºìÍâÏß¹²ÓÃ£¬ËùÒÔ×ö°´¼üÊµÑéÊ±ÎªÁË²»ÈÃºìÍâÏßÓ°ÏìÊµÑéĞ§¹û£¬×îºÃ°ÑºìÍâÏßÏÈ
*È¡ÏÂÀ´¡£
*
*********************************************************************************/
#include<reg51.h>
#include"i2c.h"
//ÊıÂë¹ÜIO
#define DIG	P0
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
//°´¼üIO
sbit K1=P3^1;
sbit K2=P3^0;
sbit K3=P3^2;
sbit K4=P3^3;
void At24c02Write(unsigned char ,unsigned char );
unsigned char At24c02Read(unsigned char );
void Delay1ms();
void Timer0Configuration();
unsigned char code DIG_CODE[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char Num=0;
unsigned int disp[8]={0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};
/*******************************************************************************
* º¯ÊıÃû         : main
* º¯Êı¹¦ÄÜ		   : Ö÷º¯Êı
* ÊäÈë           : ÎŞ
* Êä³ö         	 : ÎŞ
*******************************************************************************/

void main()
{
	unsigned int num0=0,num1=0,n;
	Timer0Configuration();
	while(1)
	{
		if(K1==0)   // ghi giá tri vào eeprom
		{
			Delay1ms();
			if(K1==0)
				At24c02Write(2,num0);
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
			n=0;
		}
		
		if(K2==0)		// doc giá tri tu eeprom
		{
			Delay1ms();
			if(K2==0)
				num0=At24c02Read(2);
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
		}			
		if(K3==0)
		{
			Delay1ms();
			if(K3==0)
				num0++;
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
			}			
			n=0;
			if(num0==256)
				num0=0;
		}
			
		if(K4==0)
		{
			Delay1ms();
			if(K4==0)
				num0=0;
			while((n<200)&&(K3==0))
			{
				n++;
				Delay1ms();	
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
}									 
/*******************************************************************************
* º¯ÊıÃû         : Timer0Configuration()
* º¯Êı¹¦ÄÜ		   : ÉèÖÃ¼ÆÊ±Æ÷
* ÊäÈë           : ÎŞ
* Êä³ö         	 : ÎŞ
*******************************************************************************/

void Timer0Configuration()
{
	TMOD=0X02;//Ñ¡ÔñÎª¶¨Ê±Æ÷Ä£Ê½£¬¹¤×÷·½Ê½2£¬½öÓÃTRX´ò¿ªÆô¶¯¡£

	TH0=0X9C;	//¸ø¶¨Ê±Æ÷¸³³õÖµ£¬¶¨Ê±100us
	TL0=0X9C;	
	ET0=1;//´ò¿ª¶¨Ê±Æ÷0ÖĞ¶ÏÔÊĞí
	EA=1;//´ò¿ª×ÜÖĞ¶Ï
	TR0=1;//´ò¿ª¶¨Ê±Æ÷		
}
/*******************************************************************************
* º¯ÊıÃû         : Delay1ms()
* º¯Êı¹¦ÄÜ		   : ÑÓÊ±
* ÊäÈë           : ÎŞ
* Êä³ö         	 : ÎŞ
*******************************************************************************/

void Delay1ms()   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}
/*******************************************************************************
* º¯ÊıÃû         : void At24c02Write(unsigned char addr,unsigned char dat)
* º¯Êı¹¦ÄÜ		   : Íù24c02µÄÒ»¸öµØÖ·Ğ´ÈëÒ»¸öÊı¾İ
* ÊäÈë           : ÎŞ
* Êä³ö         	 : ÎŞ
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2cStart();
	I2cSendByte(0xa2);//·// ten eeprom
	I2cSendByte(addr);//·dia chi trong eeprom
	I2cSendByte(dat);	//·data eeprom
	I2cStop();
}
/*******************************************************************************
* º¯ÊıÃû         : unsigned char At24c02Read(unsigned char addr)
* º¯Êı¹¦ÄÜ		   : ¶ÁÈ¡24c02µÄÒ»¸öµØÖ·µÄÒ»¸öÊı¾İ
* ÊäÈë           : ÎŞ
* Êä³ö         	 : ÎŞ
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2cStart();
	I2cSendByte(0xa2); //·¢ËÍĞ´Æ÷¼şµØÖ·
	I2cSendByte(addr); //·¢ËÍÒª¶ÁÈ¡µÄµØÖ·
	I2cStart();
	I2cSendByte(0xa3); //·¢ËÍ¶ÁÆ÷¼şµØÖ·
	num=I2cReadByte(); //¶ÁÈ¡Êı¾İ
	I2cStop();
	return num;	
}
/*******************************************************************************
* º¯ÊıÃû         : DigDisplay() interrupt 1
* º¯Êı¹¦ÄÜ		   : ÖĞ¶ÏÊıÂë¹ÜÏÔÊ¾
* ÊäÈë           : ÎŞ
* Êä³ö         	 : ÎŞ
*******************************************************************************/

void DigDisplay() interrupt 1
{
//¶¨Ê±Æ÷ÔÚ¹¤×÷·½Ê½¶ş»á×Ô¶¯ÖØ×°³õ£¬ËùÒÔ²»ÓÃÔÚ¸³Öµ¡£
//	TH0=0X9c;//¸ø¶¨Ê±Æ÷¸³³õÖµ£¬¶¨Ê±1ms
//	TL0=0X00;		
	// DIG=0; //ÏûÒş
	P1 = disp[7];
	switch(Num)	 //Î»Ñ¡£¬Ñ¡ÔñµãÁÁµÄÊıÂë¹Ü£¬
	{
		case(7):
			LSA=0;LSB=0;LSC=0; break;
		case(6):
			LSA=1;LSB=0;LSC=0; break;
		case(5):
			LSA=0;LSB=1;LSC=0; break;
		case(4):
			LSA=1;LSB=1;LSC=0; break;
		case(3):
			LSA=0;LSB=0;LSC=1; break;
		case(2):
			LSA=1;LSB=0;LSC=1; break;
		case(1):
			LSA=0;LSB=1;LSC=1; break;
		case(0):
			LSA=1;LSB=1;LSC=1; break;	
	}
	DIG=disp[Num]; //¶ÎÑ¡£¬Ñ¡ÔñÏÔÊ¾µÄÊı×Ö¡£
	Num++;
	if(Num>7)
		Num=0;
}