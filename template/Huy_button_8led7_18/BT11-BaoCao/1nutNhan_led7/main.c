#include<REGX52.H>

#define LED P0
sbit K1 = P3^1;
sbit K2 = P3^0;
sbit K3 = P3^2;
sbit K4 = P3^3;


// hexa led 7 doan
unsigned char code veee[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delayMS(unsigned int t)
{
	int i,j;
	for(i = 0; i < t; i++){
		for( j = 0; j < 123; j++) {}
}
	}
// logic sang dan---------------
void sangdan()
{
	int i, j;
	LED = 0;
	delayMS(200);
	for(i = 0; i < 8;i++)
	{
		LED = (LED << 1) | 1;
		delayMS(200);
	}
	LED = 0;
	for(i = 0; i < 8; i++)
	{
		LED = (LED >> 1) | 128;
		delayMS(200);
	}
}
///-----------------------------
void dichLedGiamDan()
{
    int i, j;
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
int main(){

	while(1){
		if(K1 == 0){
			dichLedGiamDan();
	while(K1 == 0);
	}
		else if(K2 == 0){
		dichLedTangDan();
			while(K2 == 0);
		}
}
	}