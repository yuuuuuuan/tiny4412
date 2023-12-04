#include "gpio.h"

int delay(unsigned int i)
{
    while(--i)
        ;
}

int delay1()
{
    unsigned int i = 0xfffff;
    while(--i)
        ;
}

//Buzzer初始化
int bell_init(void)
{
    GPD0CON &= ~0xf;

    GPD0CON |= 0x1;

    return 0;
}

//Buzzer 开
int bell_on(void)
{
    GPD0DAT |= 0x1;

    return 0;
}


//Buzzer 关
int bell_off(void)
{
    GPD0DAT &= ~0x1;

    return 0;
}

int main(void)
{
    bell_init();

    while(1)
    {
        bell_on();
        delay1();
        bell_off();
        delay1();
    }

    return 0;
}