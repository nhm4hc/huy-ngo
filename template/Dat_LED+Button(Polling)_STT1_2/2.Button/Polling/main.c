#include<reg51.h>
#include<intrins.h>	//dung de dich trai phai

#define GPIO_LED P2//dat ten P2 la GPIO_LED
sbit K1=P3^1;//dat ten P3.1 la K1
void Delay10ms( );  //tao ham delay


void main(void)
{
	unsigned int i,j;
	j=0xfe; //fe = 1111 1110
	
	while(1)
	{	
		GPIO_LED = j;	 
		if(K1==0)		
		{
			Delay10ms();	//delay de khong bi giat
			if(K1==0)//kiem tra nut co nhan khong
			{
				j=_cror_(j,1);//dich phai 1 lan
				while((i<50)&&(K1==0))	//neu an giu lau hon 500ms thi den se dich
				{
					Delay10ms();
					i++;//i tang moi 10ms
				}
				i=0;//khi tha tay sau khi an thi i = 0
			}
		}		

	}				
}

void Delay10ms(void)  //ham delay 10ms
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}