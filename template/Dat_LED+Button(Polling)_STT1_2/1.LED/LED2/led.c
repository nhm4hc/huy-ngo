#include<reg51.h>
#include<intrins.h>	//dung de dich trai phai			 

#define GPIO_LED P2		//dat ten P2 la GPIO_LED

void Delay10ms(unsigned int);   //tao ham

void main(void)
{
	unsigned char n;
	GPIO_LED=0xfe;//fe = 1111_1110   ->1111_1101
	while(1)
	{
		for(n=0;n<7;n++)//dich trai 7 lan
		{
			GPIO_LED=_crol_(GPIO_LED,1);//dich trai 1 lan
			Delay10ms(50); //delay 500ms
		}
		for(n=0;n<7;n++)//dich phai 7 lan
		{
			GPIO_LED=_cror_(GPIO_LED,1);//dich phai 1 lan
			Delay10ms(50); //delay 500ms
		}	
	}	
}


void Delay10ms(unsigned int c)   //Hàm delay 10ms
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}