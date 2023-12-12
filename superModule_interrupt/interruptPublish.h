#ifndef __INTERRUPT_PUBLISH_H_
#define __INTERRUPT_PUBLISH_H_

#include<reg51.h>

#define SET_BIT(byte, bit)    ((byte) |= (1 << (bit)))
#define CLEAR_BIT(byte, bit)  ((byte) &= ~(1 << (bit)))
#define TOGGLE_BIT(byte, bit) ((byte) ^= (1 << (bit)))
#define CHECK_BIT(byte, bit)  ((byte) & (1 << (bit)))

enum module_index {
    MODULE_0 = 0,
    MODULE_1 = 1,
    MODULE_2 = 2,
		MODULE_3 = 3,
		MODULE_4 = 4,
		MODULE_5 = 5,
		MODULE_6 = 6,
		MODULE_7 = 7
};

extern unsigned char c_interrupt;

void interrupt_module1(void);
void interrupt_module2(void);
//void interrupt_module3(void);
//void interrupt_module4(void);
void interrupt_module5(void);
//void interrupt_module6(void);

void timer0(void);
void Time1(void); 

#endif
