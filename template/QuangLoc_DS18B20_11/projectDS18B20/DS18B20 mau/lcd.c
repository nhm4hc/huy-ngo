#include "lcd.h"  // Bao gom file header cho LCD

// Ham delay, chi tre khoang 1ms moi lan goi
void Lcd1602_Delay1ms(uint c)   // Sai so 0us
{
    uchar a,b;
    for (; c>0; c--)
    {
         for (b=199;b>0;b--)
         {
              for(a=1;a>0;a--);
         }      
    } 
}

// Ham viet lenh cho LCD
#ifndef LCD1602_4PINS   // Neu khong dinh nghia che do 4 chan
void LcdWriteCom(uchar com)    // Viet lenh
{
    LCD1602_E = 0;     // Kich hoat tin hieu Enable
    LCD1602_RS = 0;    // Chon che do viet lenh
    LCD1602_RW = 0;    // Chon che do viet
    
    LCD1602_DATAPINS = com;     // Dat lenh vao cong du lieu
    Lcd1602_Delay1ms(1);        // Doi du lieu on dinh

    LCD1602_E = 1;              // Bat dau truyen du lieu
    Lcd1602_Delay1ms(5);        // Giu tin hieu trong mot khoang thoi gian
    LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)    // Viet lenh cho che do 4 chan
{
    // Tuong tu nhu tren nhung thuc hien voi 4 chan
	LCD1602_E = 0;	 
	LCD1602_RS = 0;	 
	LCD1602_RW = 0;	 

	LCD1602_DATAPINS = com;	
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

//	Lcd1602_Delay1ms(1);
	LCD1602_DATAPINS = com << 4; 
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif

// Ham viet du lieu len LCD
#ifndef LCD1602_4PINS
void LcdWriteData(uchar dat)   // Viet du lieu
{
    // Tuong tu ham LcdWriteCom nhung danh cho viec viet du lieu
		LCD1602_E = 0;	
	LCD1602_RS = 1;	
	LCD1602_RW = 0;	

	LCD1602_DATAPINS = dat; 
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   
	Lcd1602_Delay1ms(5);  
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)   // Viet du lieu cho che do 4 chan
{
    // Tuong tu nhu tren nhung thuc hien voi 4 chan
	LCD1602_E = 0;	  
	LCD1602_RS = 1;	  
	LCD1602_RW = 0;	 

	LCD1602_DATAPINS = dat;	
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; 
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif

// Ham khoi tao LCD
#ifndef LCD1602_4PINS
void LcdInit()  // Khoi tao LCD cho che do 8 chan
{
    // Gui lenh khoi tao LCD voi cac thiet lap cu the
	LcdWriteCom(0x38); 
	LcdWriteCom(0x0c); 
	LcdWriteCom(0x06); 
	LcdWriteCom(0x01); 
	LcdWriteCom(0x80); 
}
#else
void LcdInit()  // Khoi tao LCD cho che do 4 chan
{
    // Gui lenh khoi tao LCD voi cac thiet lap cu the cho che do 4 chan
		LcdWriteCom(0x32);	
	LcdWriteCom(0x28);	 
	LcdWriteCom(0x0c); 
	LcdWriteCom(0x06);  
	LcdWriteCom(0x01);  
	LcdWriteCom(0x80);  
}
#endif
