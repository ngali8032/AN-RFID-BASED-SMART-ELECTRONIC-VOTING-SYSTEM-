//uart0_defines.h
#ifndef UART0_DEFINES_H
#define UART0_DEFINES_H

/*UART PIN Configuration definations*/
#define PIN_FUN1 0
#define PIN_FUN2 1
#define PIN_FUN3 2
#define PIN_FUN4 3

#define TXD0_PIN_0_0 PIN_FUN2
#define RXD0_PIN_0_1 PIN_FUN2

/*
	Baud Rate = PCLK/(16*DIVISOR)
	where,
			DIVISOR = (U0DLM*256)+U0DLL;
*/

/*Clock and Baud rate definations*/
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4) /*PCLK = 15MHZ (startup setting)*/
#define BAUD 9600  /*Desired baud rate*/
#define DIVISOR (PCLK/(16*BAUD))

//U0LCR Register Bit definations
#define _8BIT 3
		/*
			determine the word length
			00 -> 5-bit data
			01 -> 6-bit data
			10 -> 7-bit data
			11 -> 8-bit data
			so, 3(binary 11) selects 8-bit data mode
		*/
#define WORD_LEN _8BIT
#define DLAB_BIT 7

//U0LSR Register Bit definations
#define RDR_BIT 0 //Bit 0 of U0LSR Receiver data ready
#define THRE_BIT 5
#define TEMT_BIT 6

#endif
