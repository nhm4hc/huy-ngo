#ifndef __MODULE_6_H_ 
#define __MODULE_6_H_

#include<reg51.h>

#include <INTRINS.H>    

sbit Beep =  P2^5 ; 
   
extern unsigned char module6_n;
static unsigned char p,m;      
static unsigned char i=0;

// noi dung ban nhac
static unsigned char code music_tab[40] ={   
0x18, 0x30, 0x1C , 0x10,     
0x20, 0x40, 0x1C , 0x10,   
0x18, 0x10, 0x20 , 0x10,   
0x1C, 0x10, 0x18 , 0x40,   
0x1C, 0x20, 0x20 , 0x20,   
0x1C, 0x20, 0x18 , 0x20,   
0x20, 0x80, 0xFF , 0x20,   
0x30, 0x1C, 0x10 , 0x18,   
0x20, 0x15, 0x20 , 0x1C,   
0x20, 0x20, 0x20 , 0x26
};   

void int0Init(void);
void timer0(void);
void module6_delay(unsigned char m);
void module6_delayms(unsigned char a);
void module_6(void);

#endif


