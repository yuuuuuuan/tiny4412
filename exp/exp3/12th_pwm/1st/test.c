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

void (*printf)(char *, ...) = 0x43e11434;

void main(void)
{	
	unsigned long  vector_base = 0xffff0000;
	unsigned long  tt_base = 0x73000000;
	unsigned long *pdo_irq = 0x75000000;
	extern unsigned long vectors_start, vectors_end;

	memset(tt_base, 0x00, 16 * 1024);
	mmap(tt_base, vector_base, 0x70000000);	
	enable_mmu(tt_base);
	memcpy(vector_base, vectors_start, 0x100);
	*pdo_irq = do_irq;
	
	__asm__ __volatile__ (
		"cpsie i\n"
	);
 
	//----------------------------- 
	ICCICR_CPU0 = 1;
	ICCPMR_CPU0 =  0xff;  /*Priority Unmask All Interrupt*/

	//------ Timer0's IrqID is 69------------------
	ICDDCR = 1;    /**/
	ICDIPR17_CPU0 = ~(0xff << 8);  /* the Zero is Highest priority */
	ICDIPTR17_CPU0 = (1 << 8); /* for CPU0   , refer  PG815 */
	ICDISER2_CPU0 =  (1 << 5); /* enable interrupt 0  */

	//---------- Configure PWM Timer 0 --------------
	TCFG0  = 0xff;
	TCFG1  = 0x4;
	TINT_CSTAT = 1;
	
	TCNTB0 = 10000;	
	TCMPB0 = 10000;
	TCON   = (1 << 1);
	TCON   = 1 | (1 << 3);
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



