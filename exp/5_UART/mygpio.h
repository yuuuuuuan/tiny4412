#ifndef _MYGPIO_H
#define _MYGPIO_H

struct GPIO_t
{
	unsigned int CON;
	unsigned int DAT;
	unsigned int PUD;
	unsigned int DRV;
	unsigned int CONPDN;
	unsigned int PUDPDN;
};

typedef struct GPIO_t GPA0_t;
//typedef struct GPIO_t GPA1_t;
typedef struct GPIO_t GPD0_t;

#define GPA0 (*(volatile GPA0_t*)0x11400000)
//#define GPA1 (*(volatile GPA1_t*)0x11400020)
#define GPD0 (*(volatile GPD0_t*)0x114000A0)

#endif
