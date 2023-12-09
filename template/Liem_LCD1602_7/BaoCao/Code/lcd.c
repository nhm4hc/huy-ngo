#include"lcd.h"

/*******************************************************************************
 Chuong trinh tao delay1ms
*******************************************************************************/

void Lcd1602_Delay1ms(uint c){   //Delay1ms
  uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}
    	
}

/*******************************************************************************
* Chuong trinh       : LcdWriteCom
* Chuc nang					 : Gui lenh den lcd
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 
void LcdWriteCom(uchar com)	  //Gui lenh
{
	LCD1602_E = 0; 
	LCD1602_RS = 0;	   //Instruction register
	LCD1602_RW = 0;	   //Mode Write
	
	LCD1602_DATAPINS = com;     //·Gan du lieu vao datapins
	Lcd1602_Delay1ms(1);		

	LCD1602_E = 1;	          
	Lcd1602_Delay1ms(5);	  
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)  //Write command to LCD
{
    LCD1602_E = 0;  //Enable signal low
    LCD1602_RS = 0;  //Select command mode
    LCD1602_RW = 0;  //Select write operation

    LCD1602_DATAPINS = com;  //Send command to 4-bit data bus
    Lcd1602_Delay1ms(1);

    LCD1602_E = 1;  //Enable signal high
    Lcd1602_Delay1ms(5);
    LCD1602_E = 0;

    LCD1602_DATAPINS = com << 4;  //Send command to low nibble
    Lcd1602_Delay1ms(1);

    LCD1602_E = 1;  //Enable signal high
    Lcd1602_Delay1ms(5);
    LCD1602_E = 0;
}

#endif
/*******************************************************************************
* ºChuong trinh         : LcdWriteData
* ºKhi su dung mode 4-bit: chi co 4 chan tu D4 - D7 duoc su dung,
4bit cao se duoc gui truoc, 4 bit thap se duoc gui sau
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//8bit
{
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
void LcdWriteData(uchar dat)			//4 bit
{
	// Gui 4 bit cao
	LCD1602_E = 0;	  
	LCD1602_RS = 1;	  //Data Register
	LCD1602_RW = 0;	  //Mode Write

	LCD1602_DATAPINS = dat;	
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	//Dich trai du lieu 4 bit de gui tiep 4 bit thap
	LCD1602_DATAPINS = dat << 4; 
	Lcd1602_Delay1ms(1);

	// Pin E: H-L ghi du lieu vao LCD
	LCD1602_E = 1;	  
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* ºChuong trinh       : LcdInit()
* º
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //8 bit
{
 	LcdWriteCom(0x38);  //Function set: Hien thi 2 hang, size 5x8 
	LcdWriteCom(0x0c);  // Display on, Cursor off , blink off
	LcdWriteCom(0x06);  //Cursor move direction
	LcdWriteCom(0x01);  //Clear lcd
	LcdWriteCom(0x80);  //Dua con tro ve vi tri dau tien cua hang 1
}
#else
void LcdInit()						  //4 bit
{
	LcdWriteCom(0x32);	 //
	LcdWriteCom(0x28);	 //Function set: Hien thi 2 hang, size 5x8 
	LcdWriteCom(0x0c);  
	LcdWriteCom(0x06);  
	LcdWriteCom(0x01);  
	LcdWriteCom(0x80);  
}
#endif
