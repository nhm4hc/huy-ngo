#include"lcd12864.h"

/************************************************************************************
* T�n chuc nang: LCD12864_Delay1ms
* Chuc nang: Tr� ho�n 1MS
* �au v�o: c
* �au ra: Kh�ng c�
************************************************************************************/

void LCD12864_Delay1ms(uint c)
{
  uchar a,b;
	for(; c>0; c--)
	{
	  for(b=199; b>0; b--)
		{
	    for(a=1; a>0; a--);
		}
	}
}

/************************************************************************************
* T�n chuc nang: LCD12864_Busy
* Chuc nang: Kium tra xem LCD c� ban kh�ng
* �au v�o: Kh�ng c�
* �au ra: 1 hoac 0 (1 nghia l� kh�ng ban, 0 nghia l� ban)
************************************************************************************/

uchar LCD12864_Busy(void)
{
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

/************************************************************************************
* T�n h�m: LCD12864_WriteCmd
* Chuc nang: viet lenh
* �au v�o: cmd
* �au ra: Kh�ng c�
************************************************************************************/

void LCD12864_WriteCmd(uchar cmd)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
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
	LCD12864_Delay1ms(1);
	LCD12864_EN = 0;
}

/************************************************************************************
* T�n h�m: LCD12864_WriteData
* Chuc nang: ghi du lieu
* �au v�o: dat
* ��u ra: Kh�ng c�
************************************************************************************/

void LCD12864_WriteData(uchar dat)
{
	uchar i;
	i = 0;
	while( LCD12864_Busy() == 0)
	{
		LCD12864_Delay1ms(1);
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
	LCD12864_Delay1ms(1);
	LCD12864_EN = 0;
}

/***********************************************************************************
* T�n h�m: LCD12864_ReadData
* Chuc nang: doc du lieu
* �au v�o: Kh�ng c�
* �au ra: doc du lieu 8 bit
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
			return 0; //Tho�t sau khi cho hon 10 gi�y
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
* T�n h�m: LCD12864_Init
* Chuc nang: Khoi tao LCD12864
* �au v�o: Kh�ng c�
* �au ra: Kh�ng c�
************************************************************************************/

void LCD12864_Init()
{
	LCD12864_PSB = 1; //Chon dau v�o song song
	LCD12864_RST = 1;//dat lai

	LCD12864_WriteCmd(0x30); //Chon thao t�c lenh co ban
	LCD12864_WriteCmd(0x0c); //Hien thi bat v� tat con tro
	LCD12864_WriteCmd(0x01); //X�a noi dung hien thi cua LCD12864
}

/************************************************************************************
* T�n chuc nang: LCD12864_ClearScreen
* Chuc nang: o che do ve, lenh 01H cua LCD12864 kh�ng x�a duoc m�n h�nh n�n ban phai tu viet h�m r� r�ng hon.
* Chuc nang m�n h�nh
* �au v�o: Kh�ng c�
* �au ra: Kh�ng c�
************************************************************************************/
#ifdef LCD12864_PICTURE

void LCD12864_ClearScreen(void)
{
	uchar i,j;

	LCD12864_WriteCmd(0x34); //Bat tap lenh mo rong

	for(i=0;i<32;i++) //V� LCD c� 32 toa do doc n�n viet ba muoi hai lan
	{	
		LCD12864_WriteCmd(0x80+i); //�au ti�n ghi gi� tri toa do doc Y
		LCD12864_WriteCmd(0x80); //Viet gi� tri cua bieu do X
		for(j=0;j<32;j++) // abscissa c� 16 bit v� moi bit cung ghi hai byte du lieu
		{ //Chi can viet 32 lan, nghi rang sau khi viet 2 byte th� bieu do se tu dong
			LCD12864_WriteData(0xFF); //Tu dong th�m 1 n�n kh�ng can ghi lai dia chi.
		}
	}

	LCD12864_WriteCmd(0x36); //Mo m�n h�nh ve theo lenh mo rong 0x36
	LCD12864_WriteCmd(0x30); //Kh�i phuc tap lenh co ban
}

#endif
/************************************************************************************
* T�n h�m: LCD12864_SetWindow
* Chuc nang: Thiet lap toa do hien thi o che do lenh co bon. Luu �: x l� h�ng c�i dat, y l� cot c�i dat
* �au v�o: x, y
* �au ra: Kh�ng c�
************************************************************************************/

void LCD12864_SetWindow(uchar x, uchar y)
{
	uchar pos;

	if(x == 0) //�ia chi cua d�ng dau ti�n l� 80H
		x = 0x80;
	else if(x == 1) //�ia chi cua d�ng thu hai l� 90H
		x = 0x90;
	else if(x == 2) //�ia chi cua d�ng thu ba l� 88H
		x = 0x88;
	else if(x==3)
		x = 0x98;
	
	pos = x + y;
	LCD12864_WriteCmd(pos);
}

/************************************************************************************
* T�n chuc nang: LCD12864_ClearScreen
* Chuc nang: o che do ve, lenh 01H cua LCD12864 kh�ng x�a duoc m�n h�nh n�n ban phai tu viet h�m r� r�ng hon.
* Chuc nang m�n h�nh
* �au v�o: Kh�ng c�
* �au ra: Kh�ng c�
************************************************************************************/
#ifdef LCD12864_PICTURE

void LCD12864_DrowPic(uchar *a)
{
	uchar i,j;

	LCD12864_ClearScreen();
	LCD12864_WriteCmd(0x34); //Bat tap lenh mo rong v� tat hien thi ban ve.
	
	for(i=0;i<32;i++) //V� LCD c� 32 taa do doc n�n viet ba muoi hai lan
	{
		LCD12864_WriteCmd(0x80+i); //�au ti�n ghi gi� tri toa do doc Y
		LCD12864_WriteCmd(0x80); //Viet gi� tri cua bieu do X
		for(j=0; j<16; j++) //C� 16 bit trong abscissa v� hai byte du lieu cung duoc ghi trong moi bit
		{ //Chi can viet 32 lan, nghi rang sau khi viet 2 byte th� bieu do se tu dong
			LCD12864_WriteData(*a); //Tu dong th�m 1 n�n kh�ng can ghi lai dia chi.
			a++;
		}
	}
	
	for(i=0;i<32;i++) //V� LCD c� 32 taa do doc n�n viet ba muoi hai lan
	{
		LCD12864_WriteCmd(0x80+i); //�au ti�n ghi gi� tri toa do doc Y
		LCD12864_WriteCmd(0x80); //Viet gi� tri cua bieu do X
		for(j=0; j<16; j++) //C� 16 bit trong abscissa v� hai byte du lieu cung duoc ghi trong moi bit
		{ //Chi can viet 32 lan, nghi rang sau khi viet 2 byte th� bieu do se tu dong
			LCD12864_WriteData(*a); //Tu dong th�m 1 n�n kh�ng can ghi lai dia chi.
			a++;
		}
	}

	LCD12864_WriteCmd(0x36); //Mo m�n h�nh
	LCD12864_WriteCmd(0x30); //Quay lai tap lenh co bon
}

/************************************************************************************
* T�n h�m: LCD12864_DrowPoint
* Ch?c nang: Chieu s�ng mot diem toi mot taa do nhat dinh, c� the d�ng de ve duong
* �au v�o: x, y
* �au ra: Kh�ng c�
************************************************************************************/

void LCD12864_DrowPoint(uchar x, uchar y)
{
	uint bt = 0, readValue = 0;
	uchar x_adr, y_adr, h_bit, l_bit;
	//Truc Y c� tong l� 64, nhung 12864 duoc chia th�nh nua tr�n cua m�n h�nh v� nua duoi cua m�n h�nh
  //Neu vuot qu� 32 th� d� l� nua duoi cua m�n h�nh
	
	//�ia chi phai bat dau lai tu so 0. V� vay, t�m phan c�n lai cua 32 de lay toa do cua truc Y, sau d� th�m dia chi co so cua 80H
	y_adr = 0x80 + y % 32; //T�nh dia chi truc Y

	//Khi Y lon hon 31 th� l� nua duoi cua m�n h�nh, X bat dau tu 88H v� l� 16 bit
	//Dia chi, modulo 16. �ia chi cua nua tr�n m�n h�nh bat dau tu 80H
	if(y>31)
		x_adr = 0x88 + x/16; //T�nh dia chi cua truc X
	else
		x_adr = 0x80 + x/16;

	//Vay t�m so du cua so n�y
	bt = 0x8000 >> (x % 16);

	LCD12864_WriteCmd(0x34); //Nhap tep lenh mo rong

	LCD12864_WriteCmd(y_adr); //Khi doc du lieu, truoc ti�n phai ghi dia chi cua du lieu duoc lay.
	LCD12864_WriteCmd(x_adr);

	LCD12864_ReadData(); //Kh�ng can doc byte dau ti�n.
	readValue = LCD12864_ReadData(); //Bat dau nhan tu byte thu hai.
	readValue <<= 8;
	readValue |= LCD12864_ReadData();
	bt = bt | readValue;
	h_bit = bt >> 8;
	l_bit = bt;

	LCD12864_WriteCmd(y_adr); //viet lai dia chi cua mot diem v� dia chi d� thay doi.
	LCD12864_WriteCmd(x_adr);

	LCD12864_WriteData(h_bit);
	LCD12864_WriteData(l_bit);

	LCD12864_WriteCmd(0x36); //Mo m�n h�nh
	LCD12864_WriteCmd(0x30); //��ng tap lenh ve
}

#endif
