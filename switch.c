/*External Interrupt*/
#include "header.h"
#include <lpc21xx.h>
#include "types.h"
int einto_interrupt=0;
void eint2_isr(void) __irq
{
	einto_interrupt=1;
	EXTINT = 1<<2;
	VICVectAddr = 0;
}
void Init_interrupt(void)
{
	PINSEL0 |= 0x0000C000;
	VICIntEnable = 1<<16;
	VICVectCntl1 = 1<<5|16;
	VICVectAddr1 = (u32)eint2_isr;
	
	EXTMODE = 1<<2;
}
