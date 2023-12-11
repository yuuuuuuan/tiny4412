#ifndef _MYBEEP_H
#define _MYBEEP_H

typedef struct
{
	unsigned int TCFG0;
	unsigned int TCFG1;
	unsigned int TCON;
	unsigned int TCNTB0;
	unsigned int TCMPB0;
	unsigned int TCNTO0;
	unsigned int TCNTB1;
	unsigned int TCMPB1;
	unsigned int TCNTO1;
	unsigned int TCNTB2;
	unsigned int TCMPB2;
	unsigned int TCNTO2;
	unsigned int TCNTB3;
	unsigned int TCMPB3;
	unsigned int TCNTO3;
	unsigned int TCNTB4;
	unsigned int TCNTO4;
	unsigned int TINT_CSTAT;
}pwm_t;

#define PWM (* (volatile pwm_t *)0x139D0000)

void pwm_init(void);
void beep_on(void);
void beep_off(void);

#endif
