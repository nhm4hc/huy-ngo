#ifndef __INTERRUPT_PUBLISH_H_
#define __INTERRUPT_PUBLISH_H_

#include<reg51.h>

#define SET_BIT(byte, bit)    ((byte) |= (1 << (bit)))
#define CLEAR_BIT(byte, bit)  ((byte) &= ~(1 << (bit)))
#define TOGGLE_BIT(byte, bit) ((byte) ^= (1 << (bit)))
#define CHECK_BIT(byte, bit)  ((byte) & (1 << (bit)))

sbit led = P2^0;

enum module_index {
    MODULE_0 = 0,
    MODULE_1,
    MODULE_2,
		MODULE_3,
		MODULE_4,
		MODULE_5,
		MODULE_6,
		MODULE_7
};

extern unsigned char c_interrupt;

void timer0(void);

#endif
