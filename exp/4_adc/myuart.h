#ifndef _MYUART_H
#define _MYUART_H

struct UART_t
{
	unsigned int ULCONn;	//Specifies line control
	unsigned int UCONn;		//Specifies control
	unsigned int UFCONn;	//Specifies FIFO control
	unsigned int UMCONn;	//Specifies modem control
	unsigned int UTRSTATn;	//Specifies Tx/Rx status
	unsigned int UERSTATn;	//Specifies Rx error status
	unsigned int UFSTATn;	//Specifies FIFO status
	unsigned int UMSTATn;	//Specifies modem status
	unsigned int UTXHn;		//Specifies transmit buffer
	unsigned int URXHn;		//Specifies receive buffer
	unsigned int UBRDIVn;	//Specifies baud rate divisor
	unsigned int UFRACVALn;	//Specifies divisor fractional value
	unsigned int UINTPn;	//Specifies interrupt pending
	unsigned int UINTSPn;	//Specifies interrupt source pending
	unsigned int UINTMn;	//Specifies interrupt mask
};

typedef struct UART_t UART0_t;
//typedef struct UART_t UART2_t; 

#define UART0 (*(volatile UART0_t*)0x13800000)
//#define UART2 (*(volatile UART2_t*)0x13820000)

void uart0_init();
int strcmp(const char *src, const char *des);
void putc(const char data);
char getc(void);
void puts(const char *pstr);
void gets(char *p);

#endif
