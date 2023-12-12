#include "displayLCD.h"
#include "LCD1602.h"
#include "module_1.h"
#include "module_2.h"
//#include "module_3.h"
//#include "module_4.h"
#include "module_5.h"
//#include "module_6.h"
#include "interruptPublish.h"

void IrInit(void){
	checkRun = 0;
	module = 0;
	IT0 = 1;
	EX0 = 1;
	EA = 1;	
	IRIN = 1;
}

void DelayMs(unsigned int x){
	unsigned char i;
  while(x--)
	{
		for (i = 0; i<13; i++){}
	}
}

void ReadIr(void) interrupt 0 {
	unsigned char j,k;
	unsigned int err;
	Time=0;					 
	DelayMs(70); //Goi ham delay de tao do tre 70ms
	if(IRIN==1) //Kiem tra xem tin hieu hong ngoai co dang nhan duoc khong	
	{	
		err=1000;	//Dat 1 gia tri timeout	
		while((IRIN==0)&&(err>0))	//wait den khi TRIN len muc 1 hoac timeout
		{			
			DelayMs(1);
			err--;
		} 
		if(IRIN==1)	//Neu tin hieu len muc 1		
		{
			err=500;
			while((IRIN==1)&&(err>0))// Wait cho den khi TRIN xuong muc 0 hoac timeout		 
			{
				DelayMs(1);
				err--;
			}
			for(k=0;k<4;k++) //Nhan 1 byte du lieu
			{				
				for(j=0;j<8;j++) //Nhan 8 bitt du lieu	
				{
					err=60;		
					while((IRIN==0)&&(err>0)) // Wait cho den khi TRIN xuong muc 1 hoac timeout
					{
						DelayMs(1);
						err--;
					}
					err=500;
					while((IRIN==1)&&(err>0)) // Wait cho den khi TRIN xuong muc 0 hoac timeout	
					{
						DelayMs(1);
						Time++;
						err--;
						if(Time>30) //Neu thoi gian TRIN o muc 1 qua 30ms
						{
							EX0=1; //Cho ph?p ngat ngoai vi
							return; //Thoat khoi ham ngat
						}
					}
					IrValue[k]>>=1;	//bitt 0 se duoc day vao bitt cao nhat cua IrValue[k] 
					if(Time>=8)	//Neu thoi gian TRIN muc cao lon hon 8ms		
					{
						IrValue[k]|=0x80; //bitt 1 se duoc day vao bitt cao nhat cua IrValue[k] 
					}
					Time=0;	// set time ve 0							
				}
			}
		}
		if(IrValue[2]!=~IrValue[3]) //Kiem tra tinh nhat quan cua du lieu
		{
			return;
		}
	}			
}

void hienThiChuc(int x){
	LcdWriteCom(0x80+0x09);
	LcdWriteData(x+0x30);	
}

void hienThiDonVi(int x){
	LcdWriteCom(0x80+0x0a);
	LcdWriteData(x+0x30);	
}
	
void reset(void){
	int i;
	checkRun = 0;
	IrValue[2] = 0;
	module = 0;
	hienThiDonVi(0x6B);
	hienThiChuc(0x6B);	
	LcdWriteCom(0x80+0x40);
	for(i=0;i<9;i++)
	{
		LcdWriteData(CDIS2[i]);	
	}
}

void xuLi(int x){
	if(checkRun==0)
	{
		module = x*10 + module;
		hienThiChuc(x);
		checkRun = 1;
		IrValue[2] = 0;
	}
	else if(checkRun==1)
	{
		module = x + module;
		hienThiDonVi(x);
		checkRun =3;
		IrValue[2] = 0;
	}
}

void runModule(int x){
	switch (x) 
	{
    case 1:
				module_1();
				break;
    case 2:
				module_2();
				break;
    case 3:
				//module_3();
				break;
		case 4:
				//module_4();
				break;
		case 5:
				module_5();
				break;
		case 6:
				//module_6();
				break;
		case 7:
				//LCD12864_DrowPic(&ars);
				//module 7 in here
				break;
		case 8:
				//module_8();
				break;
		case 9:
				//module_9();
				break;
    case 10:
				// module 10 in here
				// Using LCD16x2 for displaying, so dont call again
				break;
    case 11:
				//module_11();
				break;
    case 12:
				//module_12();
				break;
		case 13:
				// empty
				break;
		case 14:
				// empty
				break;
		case 15:
				//module_15();
				break;
    default:
        reset();
        break;
	}
}

void disableInterrupt(void){
	ET1 = 0;
	ET0 = 0;
	c_interrupt = 0;
}

void displayLCD(void){
	unsigned char i;
	LcdWriteCom(0x80); 
	for(i=0;i<9;i++)
	{
		LcdWriteData(CDIS1[i]);	
	}
	LcdWriteCom(0x80+0x40);
	for(i=0;i<9;i++)
	{
		LcdWriteData(CDIS2[i]);	
	}
}

void signalRecieved(void){
	unsigned char i;
	IrValue[4]=IrValue[2]>>4;
	IrValue[5]=IrValue[2]&0x0f;	
	if(IrValue[4]==0x00 && IrValue[5]==0x0D)
	{     //0		0D
		nutBam = 0;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x00 && IrValue[5]==0x0C)
	{	//1		0C	
		nutBam = 1;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x01 && IrValue[5]==0x08)
	{		//2		18
		nutBam = 2;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x05 && IrValue[5]==0x0E)
	{		//3		5E
		nutBam = 3;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x00 && IrValue[5]==0x08)
	{     //4		08
		nutBam = 4;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x01 && IrValue[5]==0x0C)
	{	//5		1C	
		nutBam = 5;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x05 && IrValue[5]==0x0A)
	{		//6		5A
		nutBam = 6;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x04 && IrValue[5]==0x02)
	{		//7		42
		nutBam = 7;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x05 && IrValue[5]==0x02)
	{     //8		52
		nutBam = 8;
		xuLi(nutBam);
	}
	if(IrValue[4]==0x04 && IrValue[5]==0x0A)
	{	//9		4A
		nutBam = 9;
		xuLi(nutBam);
	}
	
	if(IrValue[4]==0x04 && IrValue[5]==0x04)
	{		//mode		44H
		if(module < 20)
		{
			runModule(module);
		}
		else
		{
			LcdWriteCom(0x80+0x40);
			for(i=0;i<9;i++)
			{
				LcdWriteData(CDIS4[i]);	
			}
			DelayMs(7000);
		}
		//reset();
	}
	if(IrValue[4]==0x04 && IrValue[5]==0x06)
	{		//stop		46H
		IrValue[2] = 0;
		disableInterrupt();
	}
	
	if(IrValue[4]==0x04 && IrValue[5]==0x05)
	{		//nguon		45H
		reset();
	}
}

