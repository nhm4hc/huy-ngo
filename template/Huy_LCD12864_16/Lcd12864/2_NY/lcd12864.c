#include"lcd12864.h"

void LCD12864_Delay1ms(uint c)
{
  uchar a,b;
	for(;c>0; c--)
	{
	  for(b=199; b>0; b--)
		{
	    for(a=1; a>0; a--);
		}
	}
}

/************************************************************************************
* Tên chuc nang: LCD12864_Busy
* Chuc nang: Kium tra xem LCD có ban không
* Ðau vào: Không có
* Ðau ra: 1 hoac 0 (1 nghia là không ban, 0 nghia là ban)
************************************************************************************/

uchar LCD12864_Busy(void)
{
	uchar i = 0;

	LCD12864_RS = 0; //Chon lenh
	LCD12864_RW = 1; //Chon de doc

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);

	while((LCD12864_DATAPORT & 0x80) == 0x80) //Phát hien giá tri dã doc
	{
		i++;
		if (i > 100)
		{
			LCD12864_EN = 0;
			return 0; //Neu thoi gian cho` vuot quá, tra ve 0 de báo loi.
		}
	}

	LCD12864_EN = 0;

	return 1;
}

/************************************************************************************
* Tên hàm: LCD12864_WriteCmd
* Chuc nang: viet lenh
* Ðau vào: cmd
* Ðau ra: Không có
************************************************************************************/

void LCD12864_WriteCmd(uchar cmd)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		//LCD12864_Delay1ms(1);
		i++;
		if(i>100)
		{
			return; //thoát ra sau khi cho` doi
		}
	}
	
	LCD12864_RS = 0; //Chon lenh
	LCD12864_RW = 0; //Chon ghi
	LCD12864_EN = 0; //Thiet bi dau cuoi cho phép khoi tao

	LCD12864_DATAPORT = cmd; //Ðat du lieu

	LCD12864_EN = 1; // Thoi gian ghi
	//LCD12864_Delay1ms(1);
	LCD12864_EN = 0;
}

/************************************************************************************
* Tên hàm: LCD12864_WriteData
* Chuc nang: ghi du lieu
* Ðau vào: dat
* Ðâu ra: Không có
************************************************************************************/

void LCD12864_WriteData(uchar dat)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		//LCD12864_Delay1ms(1);
		i++;
		if(i>100)
		{
			return; //thoát ra sau khi cho doi
		}
	}

	LCD12864_RS = 1;//Chon du lieu
	LCD12864_RW = 0; //Chon ghi
	LCD12864_EN = 0; //Thiet bi dau cuoi cho phép khoi tao

	LCD12864_DATAPORT = dat; //Ðat du lieu

	LCD12864_EN = 1; // Thoi gian ghi
	//LCD12864_Delay1ms(1);
	LCD12864_EN = 0;
}

/***********************************************************************************
* Tên hàm: LCD12864_ReadData
* Chuc nang: doc du lieu
* Ðau vào: Không có
* Ðau ra: doc du lieu 8 bit
************************************************************************************/
#ifdef LCD12864_PICTURE

uchar LCD12864_ReadData(void)
{
	uchar i, readValue;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
		i++;
		if(i>100)
		{
			return 0; //Thoát sau khi cho hon 10 giây
		}
	}

	LCD12864_RS = 1; //Chon lenh
	LCD12864_RW = 1;
	LCD12864_EN = 0;
	LCD12864_Delay1ms(1); //Cho

	LCD12864_EN = 1;
	LCD12864_Delay1ms(1);
	readValue = LCD12864_DATAPORT;
	LCD12864_EN = 0;

	return readValue;
}

#endif

/************************************************************************************
* Tên hàm: LCD12864_Init
* Chuc nang: Khoi tao LCD12864
* Ðau vào: Không có
* Ðau ra: Không có
************************************************************************************/

void LCD12864_Init()
{
	LCD12864_PSB = 1; //Chon dau vào song song
	LCD12864_RST = 1;//dat lai

	LCD12864_WriteCmd(0x30); //Chon thao tác lenh co ban
	LCD12864_WriteCmd(0x0c); //Hien thi bat và tat con tro
	LCD12864_WriteCmd(0x01); //Xóa noi dung hien thi cua LCD12864
}

/************************************************************************************
* Tên chuc nang: LCD12864_ClearScreen
* Chuc nang: o che do ve, lenh 01H cua LCD12864 không xóa duoc màn hình nên ban phai tu viet hàm rõ ràng hon.
* Chuc nang màn hình
* Ðau vào: Không có
* Ðau ra: Không có
************************************************************************************/
#ifdef LCD12864_PICTURE

void LCD12864_ClearScreen(void)
{
	uchar i,j;

	LCD12864_WriteCmd(0x34); //Bat tap lenh mo rong

	for(i=0;i<32;i++) //Vì LCD có 32 toa do doc nên viet ba muoi hai lan
	{	
		LCD12864_WriteCmd(0x80+i); //Ðau tiên ghi giá tri toa do doc Y
		LCD12864_WriteCmd(0x80); //Viet giá tri cua bieu do X
		for(j=0;j<32;j++) // có 16 biT và moi biT cung ghi hai byte du lieu
		{ //Chi can viet 32 lan, khi viet 2 byte thì bieu do
			//se tu dong thêm 1 nên không can ghi lai dia chi.
			LCD12864_WriteData(0xFF); 
		}
	}

	LCD12864_WriteCmd(0x36); //Mo màn hình ve theo lenh mo rong 0x36
	LCD12864_WriteCmd(0x30); //Khôi phuc tap lenh co ban
}

#endif
/************************************************************************************
* Tên hàm: LCD12864_SetWindow
* Chuc nang: Thiet lap toa do hien thi o che do lenh co bon. Luu ý: x là hàng cài dat, y là cot cài dat
* Ðau vào: x, y
* Ðau ra: Không có
************************************************************************************/

void LCD12864_SetWindow(uchar x, uchar y)
{
	uchar pos;

	if(x == 0) //Ðia chi cua dòng dau tiên là 80H
	{
		x = 0x80;
	}
		
	else if(x == 1) //Ðia chi cua dòng thu hai là 90H
	{
		x = 0x90;
	}
	
	else if(x == 2) //Ðia chi cua dòng thu ba là 88H
	{
	x = 0x88;
	}
	
	else if(x==3)
	{
		x = 0x98;
	}
	
	pos = x + y;
	LCD12864_WriteCmd(pos);
}

/*************************************************** ***** ****************************
* Tên chuc nang: LCD12864_ClearScreen
* Chuc nang: o che do ve, lenh 01H cua LCD12864 không xóa duoc màn hình nên ban phai tu viet hàm rõ ràng hon.
* Chuc nang màn hình
* Ðau vào: Không có
* Ðau ra: Không có
**************************************************** * *******************************/
#ifdef LCD12864_PICTURE

void LCD12864_DrowPic(uchar *a)
{

	unsigned char i,j;
	//LCD12864_ClearScreen();
	LCD12864_WriteCmd(0x34); //Bat tap lenh mo rong và tat hien thi ban ve.
	
	for(i=0;i<32;i++) //Vì LCD có 32 toa do doc nên viet ba muoi hai lan
	{
		LCD12864_WriteCmd(0x80+i); //Ðau tiên ghi giá tri toa do doc Y
		LCD12864_WriteCmd(0x80); //Viet giá tri cua bieu do X
		for(j=0; j<16; j++) //Có 16 biT trong abscissa và hai byte du lieu cung duoc ghi trong moi biT
		{ //Chi can viet 32 lan, khi viet 2 byte thì bieu do se tu dong
			LCD12864_WriteData(*a); //thêm 1 nên không can ghi lai dia chi.
			a++;
		}
	}
	
	for(i=0;i<32;i++) //Vì LCD có 32 toa do doc nên viet ba muoi hai lan
	{
		LCD12864_WriteCmd(0x80+i); //Ðau tiên ghi giá tri toa do doc Y
		LCD12864_WriteCmd(0x88); //Viet giá tri cua bieu do X
		for(j=0; j<16; j++) //Có 16 biT trong abscissa và hai byte du lieu cung duoc ghi trong moi biT
		{ //Chi can viet 32 lan, nghi rang sau khi viet 2 byte thì bieu do se tu dong
			LCD12864_WriteData(*a); //Tu dong thêm 1 nên không can ghi lai dia chi.
			a++;
		}
	}
	
	LCD12864_WriteCmd(0x36); //Mo màn hình
	LCD12864_WriteCmd(0x30); //Quay lai tap lenh co bon
}

#endif
