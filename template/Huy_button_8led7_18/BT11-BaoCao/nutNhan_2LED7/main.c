// 4 button, 2 led 7
#include<REGX52.H>

typedef unsigned int u16;	
typedef unsigned char u8;


sbit KEY1=P3^1;  // up
sbit KEY2=P3^0;  // down
sbit KEY3=P3^2;  // stop
sbit KEY4=P3^3;	// dao



#define LED P0
#define LED2 P1


#define KEY1_PRESS	1
#define KEY2_PRESS	2
#define KEY3_PRESS	3
#define KEY4_PRESS	4
#define KEY_UNPRESS	0	


// hexa led 7 doan
unsigned char code veee[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};


void delay_10us(u16 ten_us)
{
	while(ten_us--);	
}


u8 key_scan(u8 mode)
{
	static u8 key=1;

	if(mode)key=1;//连续扫描按键
	if(key==1&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))//任意按键按下
	{
		delay_10us(1000);//消抖
		key=0;
		if(KEY1==0)
			return KEY1_PRESS;
		else if(KEY2==0)
			return KEY2_PRESS;
		else if(KEY3==0)
			return KEY3_PRESS;
		else if(KEY4==0)
			return KEY4_PRESS;	
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)	//无按键按下
	{
		key=1;			
	}
	return KEY_UNPRESS;		
}
/*******************************************************************************
* 函 数 名       : main
* 函数功能		 : 主函数
* 输    入       : 无
* 输    出    	 : 无
*******************************************************************************/


void delayMS(unsigned int t)
{
	int i,j;
	for(i = 0; i < t; i++){
		for( j = 0; j < 123; j++) {}
}
	}
void dichLedGiamDan()
{
    int i;
    for(i = 10; i > 0; i--)
    {
        LED = veee[i-1];
        delayMS(500);
    }
    LED = 0;
    delayMS(200);
}

void dichLedTangDan()
{
    int i, j;
    for(i = 0; i < 10; i++)
    {
        //LED = (1 << i); // Shift a single LED to the left
        //delayMS(500);
				LED = veee[i+1];
			delayMS(500);
    }
		LED = 0;
		delayMS(500);
}


void main()
{	
	u8 key=0;

	while(1)
	{
	   	key=key_scan(0);
		if(KEY1 == 0){
		dichLedGiamDan();
			while(KEY1 == 0);
	}		
	else if(KEY2 == 0){
		dichLedTangDan();
		while(KEY2 == 0);
	}		
}
}