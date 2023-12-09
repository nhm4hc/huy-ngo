#include"lcd.h"

/*******************************************************************************
* ºChuong trinh       : Lcd1602_Delay1ms
*******************************************************************************/

void Lcd1602_Delay1ms(uint c)   //Delay1ms
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

/*******************************************************************************
* Chuong trình        : LcdWriteCom
* Chuc nang						: Ghi command den LCD
*******************************************************************************/
#ifndef 	LCD1602_4PINS	 //Chan LCD1602_4PINS khong duoc su dung
void LcdWriteCom(uchar com)	  //8 bit
{
	LCD1602_E = 0;     //Bat Dau Doc Du Lieu
	LCD1602_RS = 0;	   //Chon Thanh Ghi Tap Lenh
	LCD1602_RW = 0;	   //Che do ghi du lieu
	
	LCD1602_DATAPINS = com;     //·Gan lenh can gui cho chan I/O
	Lcd1602_Delay1ms(1);

	//Thay doi muc logic tu H->L de ghi lenh vao LCD
	LCD1602_E = 1;	          
	Lcd1602_Delay1ms(5);	  
	LCD1602_E = 0;
}
#else 
void LcdWriteCom(uchar com)	  //4-bit
{
	LCD1602_E = 0;	 
	LCD1602_RS = 0;	
	LCD1602_RW = 0;	

	//Gui truoc 4bit cao cua command
	LCD1602_DATAPINS = com;	
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

//	Dich trai 4 bit de gui 4 bit thap cua command
	LCD1602_DATAPINS = com << 4;
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* Chuong trinh         : LcdWriteData
* Chuc nang   : Gui data den LCD
*******************************************************************************/		   
#ifndef 	LCD1602_4PINS		   
void LcdWriteData(uchar dat)			//8bit
{
	LCD1602_E = 0;
	LCD1602_RS = 1;	
	LCD1602_RW = 0;	

	LCD1602_DATAPINS = dat; //Ghi du lieu can gui vao port noi voi LCD
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#else
void LcdWriteData(uchar dat)			//4bit
{
	
	LCD1602_E = 0;
	LCD1602_RS = 1;	  
	LCD1602_RW = 0;	  
// Gui truoc 4 bit cao cua data
	LCD1602_DATAPINS = dat;
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	  
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

// Dich trai 4 bit de gui tiep 4 bit thap cua data
	LCD1602_DATAPINS = dat << 4; 
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif
/*******************************************************************************
* Chuong trinh     : LcdInit()
* Chuc nang : Khoi tao cac thong so ban dau cua LCD
*******************************************************************************/		   
#ifndef		LCD1602_4PINS
void LcdInit()						  //8 bit data
{
 	lcd1602_write_cmd(0x38);// 8-bit data, 2 lines, 5x7 font size
	lcd1602_write_cmd(0x0c);//Display on, cursor off, blink off
	lcd1602_write_cmd(0x06);//Entry mode set: increment, no shift
	lcd1602_write_cmd(0x01);//Clear LCD
	LcdWriteCom(0x80);  //Dua con tro ve lai o dau cua hang dau
}
#else
void LcdInit()						  //4 bit data
{
	LcdWriteCom(0x32);  // Chuyen che do 8-bit sang 4-bit
	LcdWriteCom(0x28);  // 2 dòng, ma tran 5x7
	LcdWriteCom(0x0c);  
	LcdWriteCom(0x06);  
	LcdWriteCom(0x01);  
	LcdWriteCom(0x80); 

}
#endif
