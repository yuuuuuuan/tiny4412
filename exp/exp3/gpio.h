#ifndef __GPIO_H__
#define __GPIO_H__

typedef volatile unsigned int U32;
typedef volatile unsigned short U16;
typedef volatile unsigned char U8;

//LED
#define GPM4CON *(U32*)0x110002e0
#define GPM4DAT *(U32*)0x110002e4

//Key
#define GPX3CON *(U32*)0x11000c60
#define GPX3DAT *(U32*)0x11000c64

//Buzzer
#define GPD0CON *(U32*)0x114000a0
#define GPD0DAT *(U32*)0x114000a4


//LED初始化
int led_init(void);
//LED 全亮
int led_allon(void);
//LED 全灭
int led_alloff(void);


#endif/*__GPIO_H__*/