#include "module_6.h"

unsigned char module6_n = 0;

void int0Init(void){
	TMOD&=0x0f;   
  TMOD|=0x01;   
  TH0=0xd8;
	TL0=0xef;   
  IE=0x82;
}

void timer0(void) interrupt 1{
	TH0=0xd8;   
	TL0=0xef;   
	module6_n--; 
}
 
void module6_delay(unsigned char m){   
 unsigned i=3*m;   
 while(--i);   
}   
   
void module6_delayms(unsigned char a){   
  while(--a);                   
} 

void module_6(void){
	int0Init();	
	//play:
	//a: 
	p=music_tab[i];   
  if(p==0x00)       
	{ 
		i=0; 
		module6_delayms(1000);
		//goto play;
	}        
	else if(p==0xff)  
	{
		i=i+1;
		module6_delayms(100);
		TR0=0;
		//goto a;
	}      
	else         
	{
		m=music_tab[i++]; 
		module6_n=music_tab[i++];
	}   
	TR0 = 1;
	while(module6_n!=0)
	{
		Beep=~Beep;
		module6_delay(m);
	}	
	
	TR0=0;
}