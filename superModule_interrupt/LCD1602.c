#include "LCD1602.h"

void Lcd1602_Delay1ms(uint c)   //Ham tao delay voi tham so dau vao c
{
    uchar a,b; //Khai bao 2 bien a va b
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}	
}

#ifndef 	LCD1602_4PINS	 //kiem tra LCD1602_4PINS da duoc dinh nghia truoc do trong ma nguon hay chua
void LcdWriteCom(uchar com)	  
{
	LCD1602_E = 0;     //Tat chan Enable (E) trên màn hình LCD, chuan bi cho viec gui lenh
	LCD1602_RS = 0;	   //Dat chan Register Select (RS) ve 0 de chon viec gui lenh, khong phai du lieu
	LCD1602_RW = 0;	   //Dat chan Read/Write (RW) ve 0 de chi dinh la lenh se duoc ghi(khong phai doc)
	
	LCD1602_DATAPINS = com;     //Gan gia tri cua bien 'com' vao LCD1602_DATAPINS
	Lcd1602_Delay1ms(1);		//Goi ham Lcd1602_Delay1ms() voi tham so dau vao la 1

	LCD1602_E = 1;	          //Bat chan E de bat dau gui lenh
	Lcd1602_Delay1ms(5);	  //Goi ham Lcd1602_Delay1ms() voi tham so dau vao la 5
	LCD1602_E = 0;         //tat chan Enable de ket thuc qua trinh gui lenh
}
#else // xac dinh ma nguon nao se duoc bien dich neu dieu kien truoc do la sai
void LcdWriteCom(uchar com)	 
{
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

#ifndef 	LCD1602_4PINS	 //kiem tra LCD1602_4PINS da duoc dinh nghia truoc do trong ma nguon hay chua	   
void LcdWriteData(uchar dat)			
{
	LCD1602_E = 0;	//Tat chan Enable (E) trên màn hình LCD, chuan bi cho viec gui lenh
	LCD1602_RS = 1;	//Dat chan Register Select (RS) ve 0 de chon viec gui lenh, khong phai du lieu
	LCD1602_RW = 0;	//Dat chan Read/Write (RW) ve 0 de chi dinh la lenh se duoc ghi(khong phai doc)

	LCD1602_DATAPINS = dat; 
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   
	Lcd1602_Delay1ms(5);   
	LCD1602_E = 0;
}
#else  //Neu LCD1602_4PINS da duoc dinh nghia truoc do, ma ben trong khoi #else se duoc bien dich
void LcdWriteData(uchar dat)			
{
	LCD1602_E = 0;	 
	LCD1602_RS = 1;	  
	LCD1602_RW = 0;	  

	LCD1602_DATAPINS = dat;	
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;

	LCD1602_DATAPINS = dat << 4; //Dich trai bien dat 4 bitt, sau do gan bien LCD1602_DATAPINS bang dat
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;	 
	Lcd1602_Delay1ms(5);
	LCD1602_E = 0;
}
#endif //Danh dau ket thuc cua khoi ma duoc xac dinh
	   
#ifndef		LCD1602_4PINS
void LcdInit()						  
{
 	LcdWriteCom(0x38);  //thuc hien gui 0x38 toi man hinh LCD
	LcdWriteCom(0x0c);  
	LcdWriteCom(0x06);  
	LcdWriteCom(0x01);  
	LcdWriteCom(0x80);  
}
#else
void LcdInit()						  
{
	LcdWriteCom(0x32);	
	LcdWriteCom(0x28);	 
	LcdWriteCom(0x0c);  
	LcdWriteCom(0x06);  
	LcdWriteCom(0x01);  
	LcdWriteCom(0x80);  
}
#endif
