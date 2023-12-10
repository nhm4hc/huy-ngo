#include "module_7.h"

void LCD12864_Delay1ms(uint c){
  uchar a,b;
	for(;c>0; c--)
	{
	  for(b=199; b>0; b--)
		{
	    for(a=1; a>0; a--);
		}
	}
}

uchar LCD12864_Busy(void){
	uchar i = 0;
	LCD12864_RS = 0; //Chon lenh
	LCD12864_RW = 1; //Chon de doc
	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);
	while((LCD12864_DATAPORT & 0x80) == 0x80) //Ph�t hien gi� tri d� doc
	{
		i++;
		if (i > 100)
		{
			LCD12864_EN = 0;
			return 0; //Neu thoi gian cho` vuot qu�, tra ve 0 de b�o loi.
		}
	}
	LCD12864_EN = 0;
	return 1;
}

void LCD12864_WriteCmd(uchar cmd){
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		//LCD12864_Delay1ms(1);
		i++;
		if(i>100)
		{
			return; //tho�t ra sau khi cho` doi
		}
	}
	LCD12864_RS = 0; //Chon lenh
	LCD12864_RW = 0; //Chon ghi
	LCD12864_EN = 0; //Thiet bi dau cuoi cho ph�p khoi tao
	LCD12864_DATAPORT = cmd; //�at du lieu
	LCD12864_EN = 1; // Thoi gian ghi
	//LCD12864_Delay1ms(1);
	LCD12864_EN = 0;
}

void LCD12864_WriteData(uchar dat){
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		//LCD12864_Delay1ms(1);
		i++;
		if(i>100)
		{
			return; //tho�t ra sau khi cho doi
		}
	}
	LCD12864_RS = 1;//Chon du lieu
	LCD12864_RW = 0; //Chon ghi
	LCD12864_EN = 0; //Thiet bi dau cuoi cho ph�p khoi tao
	LCD12864_DATAPORT = dat; //�at du lieu
	LCD12864_EN = 1; // Thoi gian ghi
	//LCD12864_Delay1ms(1);
	LCD12864_EN = 0;
}

void LCD12864_Init(void){
	LCD12864_PSB = 1; //Chon dau v�o song song
	LCD12864_RST = 1;//dat lai
	LCD12864_WriteCmd(0x30); //Chon thao t�c lenh co ban
	LCD12864_WriteCmd(0x0c); //Hien thi bat v� tat con tro
	LCD12864_WriteCmd(0x01); //X�a noi dung hien thi cua LCD12864
}

#ifdef LCD12864_PICTURE

void LCD12864_DrowPic(uchar *a){

	unsigned char i,j;
	LCD12864_WriteCmd(0x01);
	LCD12864_WriteCmd(0x34); //Bat tap lenh mo rong v� tat hien thi ban ve.
	
	for(i=0;i<32;i++) //V� LCD c� 32 toa do doc n�n viet ba muoi hai lan
	{
		LCD12864_WriteCmd(0x80+i); //�au ti�n ghi gi� tri toa do doc Y
		LCD12864_WriteCmd(0x80); //Viet gi� tri cua bieu do X
		for(j=0; j<16; j++) //C� 16 biT trong abscissa v� hai byte du lieu cung duoc ghi trong moi biT
		{ //Chi can viet 32 lan, khi viet 2 byte th� bieu do se tu dong
			LCD12864_WriteData(*a); //th�m 1 n�n kh�ng can ghi lai dia chi.
			a++;
		}
	}
	
	for(i=0;i<32;i++) //V� LCD c� 32 toa do doc n�n viet ba muoi hai lan
	{
		LCD12864_WriteCmd(0x80+i); //�au ti�n ghi gi� tri toa do doc Y
		LCD12864_WriteCmd(0x88); //Viet gi� tri cua bieu do X
		for(j=0; j<16; j++) //C� 16 biT trong abscissa v� hai byte du lieu cung duoc ghi trong moi biT
		{ //Chi can viet 32 lan, nghi rang sau khi viet 2 byte th� bieu do se tu dong
			LCD12864_WriteData(*a); //Tu dong th�m 1 n�n kh�ng can ghi lai dia chi.
			a++;
		}
	}
	
	LCD12864_WriteCmd(0x36); //Mo m�n h�nh
	LCD12864_WriteCmd(0x30); //Quay lai tap lenh co bon
}

#endif
