/*
 * 李柏章　Li Baizhang,  makelinux@gmail.com, 2013-08, 
 */


#include "regs.h"

void enable_mmu(unsigned long ttb);
void init_ttb(unsigned long *ttb_base);
void mmap(unsigned long *ttb_base, unsigned long va, unsigned long pa);
void memset(char *buf, char ch, int size);
void memcpy(char *dst, char *src, int size);
void do_irq(unsigned long regs[]);

void uart3_putc(unsigned char ch);
unsigned char uart3_getc(void);
void uart3_puts(char *s);
void uart3_gets(unsigned char *s);

void (*printf)(char *, ...) = 0x43e11434;
void main(void)
{	
	init_uart();
	uart3_puts("\n------------welcome--------------\n");
	while(1) {	
		unsigned char cmd[512];
		uart3_puts("[ Li Baizhang @Yogurt]# ");
		uart3_gets(cmd);
		uart3_puts(cmd);
		uart3_puts("is not supported.\n");
	}
}

void init_uart(void)
{
	GPA1CON	 &= ~(0xff << 16);	
	GPA1CON  |=  (0x22 << 16);
	
        ULCON3 = 3 ;
        UCON3 = 1 | ( 1 << 2)   ;
        UFCON3 = 0;

	UBRDIV3 = 0x35;
	UFRACVAL3 = 0x4;	
}

void uart3_putc(unsigned char ch)
{
	while(!(UTRSTAT3 & ( 1 << 1)))
		;
	UTXH3 = ch;
}

unsigned char uart3_getc(void)
{
	unsigned char ch;
	while(!(UTRSTAT3 & ( 1 << 0)))
		;

	ch = URXH3;
	return ch;
}


void uart3_puts(char *s)
{
	while(*s) {
		uart3_putc(*s);
		if (*s == '\n') {
			uart3_putc('\r');
		}
		s ++;
	}
}

void uart3_gets(unsigned char *s)
{
	unsigned char ch = 0;
	while(1) {
		ch = uart3_getc();
		uart3_putc(ch);
		if ((ch == '\r')) {
			uart3_putc('\n');
			break;
		}

		*s = ch;
		s ++;
	}
	*s = 0;
}

void do_irq(unsigned long regs[])
{
	printf("PWM Timer0: Time Out\n");
	
	TINT_CSTAT |= (1 << 5);
}

void enable_mmu(unsigned long ttb)
{	
	unsigned long c1_flags;

	init_ttb(ttb);

	c1_flags = 1 | (1 << 3) | ( 1 << 11) | ( 1 << 13) |  (1 << 28);

	__asm__ __volatile__ (
		"mvn r0, #0 \n"			
		"mcr p15, 0, r0, c3, c0, 0\n"

		"mcr p15, 0, %1, c2, c0, 0\n" //configure ttb

		"mrc p15, 0, r0, c1, c0, 0\n"
		"orr %0, r0, %0\n"
		"mcr p15, 0, %0, c1, c0, 0\n" //enable mmu
		:
		: "r" (c1_flags), "r" (ttb)
		: "r0"
	);
}

void init_ttb(unsigned long *ttb_base)
{
	unsigned long va, pa;

	for (va = 0x00000000; va < 0x10000000; va += 0x100000) { //Others
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) | 2;	
	}

	for (va = 0x10000000; va < 0x14000000; va += 0x100000) { //SFR
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) |  2;	
	}

	for (va = 0x40000000; va < 0x80000000; va += 0x100000) { //DRAM
		pa = va;
		ttb_base[ va >> 20] = (pa & 0xfff00000) | 2;	
	}
	
}


void mmap(unsigned long *ttb_base, unsigned long va, unsigned long pa)
{
	ttb_base[ va >> 20] = (pa & 0xfff00000) |  2;	
}

void memset(char *buf, char ch, int size)
{
	int i;
	for (i = 0; i < size; i ++)
		buf[i] = ch;
}

void memcpy(char *dst, char *src, int size)
{
	int i;
	for (i = 0; i < size; i ++) 
		dst[i] = src[i];	
}

__asm__ (
"vectors:\n"
	"b reset\n"
	"b und\n"
	"b swi\n"
	"b pre_abt\n"
	"b dat_abt\n"
	".word 0\n"
	"b irq\n"
	"b fiq\n"
"reset:\n"
"und:\n"
	"mov sp, #0x74000000\n"
	"stmfd sp!, {r0-r12, lr}\n"

	"mov r0, sp\n"
	"mov r3, #0x74000000\n"
	"ldr r3, [r3]\n"
	"blx r3\n"

	"mov sp, #0x74000000\n"
	"ldmea sp, {r0-r12, pc}^\n"
"swi:\n"
"pre_abt:\n"
"dat_abt:\n"
"fiq:\n"
"irq:\n"
	"mov sp, #0x75000000\n"
	"sub lr, lr, #4	\n"
	"stmfd sp!, {r0-r12, lr}\n"
	
	"mov r0, sp\n"
	"mov r3, #0x75000000\n"
	"ldr r3, [r3]\n"
	"blx r3\n"

	"mov sp, #0x75000000\n"
	"ldmea sp, {r0-r12, pc}^\n"
"EOV:\n"
"vectors_start:\n"
	".word vectors\n"
"vectors_end:\n"
	".word EOV\n"
);



