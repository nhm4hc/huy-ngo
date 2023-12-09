
#include<REGX52.H>

typedef unsigned int u16;	
typedef unsigned char u8;

//PORT 0 = LED 
#define SMG_A_DP_PORT	P0	

// 3 chân input cho IC 74138
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

// 4 chân nút nh?n, trong dó co 2 chân có the dung lam interrupt 
sbit K1 = P3^1;
sbit K2 = P3^0;
sbit K3 = P3^2;
sbit K4 = P3^3;

unsigned int count  = 0;
// Mã led 7 doan tu 1 den 16

u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};


/*
void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}
				
				*/
// khai báo ng?t timer 
void btn_setup(){
	IT0 =1;
	IT1 = 1;
	EA =1;
	EX0 = 1;
	EX1 = 1;
}
void ISR_INT0(void) interrupt 0
{
			count =1;
}
void ISR_timer0(void) interrupt 1
{
	TH0 = 0xFC;
	TL0 = 0x18;
	count++;
}
void delayMS(unsigned int t){
	
		TMOD = 0x01;
		TH0 = 0xFC;
		TL0 = 0x18;
		IE = 0x82;
		count =0;
		TR0 =1;
		while(count < t);
		IE =0;
		TR0 =0;
		
	
}
/*******************************************************************************

void smg_display(void)
{
	u8 i=0;

	for(i=0;i<8;i++)
	{
	   	switch(i)//Î»Ñ¡
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;
		}
		SMG_A_DP_PORT=gsmg_code[i];//´«ËÍ¶ÎÑ¡Êý¾Ý
//		delay_10us(10000000);//ÑÓÊ±Ò»¶ÎÊ±¼ä£¬µÈ´ýÏÔÊ¾ÎÈ¶¨
		delayMS(1000);
		SMG_A_DP_PORT=0x00;//ÏûÒô
	}
}

/*******************************************************************************
* º¯ Êý Ãû       : main
* º¯Êý¹¦ÄÜ		 : Ö÷º¯Êý
* Êä    Èë       : ÎÞ
* Êä    ³ö    	 : ÎÞ
*******************************************************************************/

// DICH LED tu LED1 ve LED 8 : 0 1 2 3 4 5 6 7 
void smg_display1(void)
{
	u8 i=0;

	for(i=0;i<8;i++)
	{
	   	switch(i)//Î»Ñ¡
		{
			case 0: LSC=1;LSB=1;LSA=1;break;
			case 1: LSC=1;LSB=1;LSA=0;break;
			case 2: LSC=1;LSB=0;LSA=1;break;
			case 3: LSC=1;LSB=0;LSA=0;break;
			case 4: LSC=0;LSB=1;LSA=1;break;
			case 5: LSC=0;LSB=1;LSA=0;break;
			case 6: LSC=0;LSB=0;LSA=1;break;
			case 7: LSC=0;LSB=0;LSA=0;break;
		}
		SMG_A_DP_PORT=gsmg_code[i];//´«ËÍ¶ÎÑ¡Êý¾Ý
		//delay_10us(10000000);
		delayMS(1000);
		SMG_A_DP_PORT=0x00;//ÏûÒô
	}
}

// DICH LED tu LED7 ve LED 1 :7 6 5 4 3 2 1 0 
void smg_display2(void)
{
	u8 i=0;

	for(i=0;i<8;i++)
	{
	   	switch(i)//Î»Ñ¡
		{
	//		case 7: LSC=1;LSB=1;LSA=1;break;
			case 6: LSC=1;LSB=1;LSA=0;break;
			case 5: LSC=1;LSB=0;LSA=1;break;
			case 4: LSC=1;LSB=0;LSA=0;break;
			case 3: LSC=0;LSB=1;LSA=1;break;
			case 2: LSC=0;LSB=1;LSA=0;break;
			case 1: LSC=0;LSB=0;LSA=1;break;
			case 0: LSC=0;LSB=0;LSA=0;break;
		}
		SMG_A_DP_PORT=gsmg_code[i];//´«ËÍ¶ÎÑ¡Êý¾Ý
		//delay_10us(10000000);
		delayMS(1000);
		SMG_A_DP_PORT=0x00;//ÏûÒô
	}
}




void main()
{	
	btn_setup();
	while(1)
	{
		if(K1 == 0){
	   	smg_display();
			
		}
	if (K2 == 0){
			smg_display1();
			
		}
		
		else if (count == 1){
			smg_display2();
		}
	}		
}