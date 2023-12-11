#include "myuart.h"
#include "mygpio.h"
//ADC 
#define ADCCON         	(*(volatile unsigned int *)0x126C0000)
#define ADCDAT         	(*(volatile unsigned int *)0x126C000C)
#define ADCMUX         	(*(volatile unsigned int *)0x126C001C)


int main(void)
{ uart0_init();  
  //char rec;
  char bit3,bit2,bit1,bit0;
  unsigned int ADC_Value=0;
  ADCCON=0;
  ADCCON=(1<<16|1<<14|65<<6|0);
  ADCMUX=0x0; 
  puts("uart is ok\n"); 
  puts("adc is ready\n");
	while(1)
	  { 
         ADCCON = ADCCON |0x1;
		// puts("开始转换...");
		/*等待转换完成  ADCCON[15]=1转换完成*/
         while(!(ADCCON & (1 << 15))); 
		//转换完成，读取转换结果
		 ADC_Value = ADCDAT & 0xfff; 
		 ADC_Value = ADC_Value*1800;
		 ADC_Value = ADC_Value/4096;
		 bit3=ADC_Value/1000;
		 bit2=(ADC_Value%1000)/100;
		 bit1=(ADC_Value/10)%10;;
		 bit0=ADC_Value%10;
		 puts("voltage=");
		 putc(bit3+'0');
         putc(bit2+'0');
         putc(bit1+'0');
		 putc(bit0+'0');
		 puts("mv");
         putc('\r');
         putc('\n');
         mydelay_ms(1000);		 
	  }
	 
	  return 0;
}
void mydelay_ms(int time)
{
	int i, j;
	while(time--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}
void uart0_init()
{
	/*UART0 initialize*/
	GPA0.CON = GPA0.CON & (~(0xff)) | (0x22); //GPA0_0:RX;GPA0_1:TX
	UART0.ULCONn = 0x3; //Normal mode, No parity,One stop bit,8 data bits
	UART0.UCONn = 0x5;  //Interrupt request or polling mode
	//Baud-rate : src_clock:100Mhz
	UART0.UBRDIVn = 53;
	UART0.UFRACVALn = 0x4;
}

int strcmp(const char *src, const char *des)
{
	while(*src || *des)
	{
		if(*src > *des)
			return 1;
		else if(*src < *des)
			return -1;
		else
		{
			src++;
			des++;
		}
	}
	return 0;
}

void putc(const char data)
{
	while(!(UART0.UTRSTATn & 0X2));
	UART0.UTXHn = data;
	if(data == '\n')
		putc('\r');	//i dont know why! if '\n' print endless '\n'
}

char getc(void)
{
	char data;
	while(!(UART0.UTRSTATn & 0x1));
	data = UART0.URXHn;
	//if ((data == '\n')||(data == '\r'))	//'\n' is useless minicom dont know '\n'
	if(data == '\r')	//'\n' is useless minicom dont know '\n' enter key is '\r'
		putc('\n');	//is '\n' not '\r' '\r' cant print next line, '\n' + '\r' can print next line
	else
		putc(data);
	return data;
}

void puts(const char *pstr)
{
	while(*pstr != '\0')
		putc(*pstr++);
}

void gets(char *p)
{
	char data;
	while((data = getc()) != '\r')	
		*p++ = data;
	if(data == '\r')	//is '\r' not '\n'
		*p++ = '\n';	//example is wrong!!! is '\n' not '\r'!!!
	*p = '\0';
}

