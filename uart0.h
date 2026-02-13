#ifndef uart0_h
#define uart0_h
#include "types.h"
void UART0_Init(void);
void UART0_TxChar(u8 TxByte);
void UART0_RxChar(void) __irq;

#endif
