#include <reg51.h>
#include "lcd.h"

#define GPIO_KEY P1

unsigned char KeyValue;
// Bien luu tru gia tri phim doc duoc
unsigned char KeyState;
// Bien luu trang thai nut nhan
unsigned char PuZh[] = " Liem__21139076 ";
void Delay10ms(); // Ham tao do tre 10ms
void KeyDown();   // Ham kiem tra nut nhan

/*******************************************************************************
Chuong trinh: Ham main
*******************************************************************************/
void main(void)
{
    unsigned char i;
    LcdInit();
    KeyState = 0;
	// Ghi lan luot chuoi ra man hinh LCD
    for (i = 0; i < 16; i++)
    {
        LcdWriteData(PuZh[i]);
    }
    while (1)
    {
        KeyDown();  
        if (KeyState)
        {
            KeyState = 0;
					// Dua con tro den dau hang thu hai de hien thi KeyValue len LCD
            LcdWriteCom(0x80 + 0x40);
            LcdWriteData('0' + KeyValue);
        }
    }
}

/*******************************************************************************
* Ten ham          : KeyDown
* Chuc nang         : Kiem tra va doc gia tri nut nhan
*******************************************************************************/
void KeyDown(void)
{
    char a;
    GPIO_KEY = 0x0f;
    if (GPIO_KEY != 0x0f)
    {
        Delay10ms();
        if (GPIO_KEY != 0x0f)
        {
            KeyState = 1;
            // Kiem tra hang
            GPIO_KEY = 0X0F;
            switch (GPIO_KEY)
            {
            case (0X07):
                KeyValue = 0;
                break;
            case (0X0b):
                KeyValue = 1;
                break;
            case (0X0d):
                KeyValue = 2;
                break;
            case (0X0e):
                KeyValue = 3;
                break;
            }
            // Kiem tra cot
            GPIO_KEY = 0XF0;
            Delay10ms();
            switch (GPIO_KEY)
            {
            case (0X70):
                KeyValue = KeyValue;
                break;
            case (0Xb0):
                KeyValue = KeyValue + 4;
                break;
            case (0Xd0):
                KeyValue = KeyValue + 8;
                break;
            case (0Xe0):
                KeyValue = KeyValue + 12;
                break;
            }
            while ((a < 50) && (GPIO_KEY != 0xf0))
            {
                Delay10ms();
                a++;
            }
            a = 0;
        }
    }
}

void Delay10ms(void) // Ham tao do tre 10ms
{
    unsigned char a, b, c;
    for (c = 1; c > 0; c--)
        for (b = 38; b > 0; b--)
            for (a = 130; a > 0; a--);
}
