//uart0.c
#include "header.h"
#include <LPC21xx.h>
#include "uart0_defines.h"
int CardPlaced=0;
int uartCharCount=0;
char ch[11];
void UART0_RxChar(void) __irq
{
	if(((U0IIR>>1)&0x07)==0x02)
	{
		ch[uartCharCount++] = U0RBR;
	}
	if(uartCharCount==10)
	{
		CardPlaced=1;
		ch[uartCharCount] = '\0';	
	}
	VICVectAddr = 0;
}

void UART0_Init(void)
{
	PINSEL0 |= 0x00000005;
	//configure UART0 line control for
	// -8 data bits, No parity, 1 stop bit, (8 N1)
	// -DLAB = 1 (to access baud rate divisor register)
	
	U0LCR = WORD_LEN | (1<<DLAB_BIT);
	U0DLL = DIVISOR;
	U0DLM = DIVISOR>>8;
	
	//Disable DLAB (to access THR and RBR sfrs)
	U0LCR &= ~(1<<DLAB_BIT);
	
	VICIntEnable |= 1<<6;
	VICVectCntl0 = 1<<5|6;
	VICVectAddr0 = (u32)UART0_RxChar;
	U0IER = 1;
}

void UART0_TxChar(u8 TxByte)
{
	//Load the data Byte into UART0 Transmit Buffer
	U0THR = TxByte;
	while(((U0LSR>>TEMT_BIT)&1)==0);
}
