#include "header.h"
extern int uartCharCount;
extern char ch[10];
void officer_card_checking(void)
{
	while(1)
	{
		s8 arr[10];
		CmdLCD(0x80);
		StrLCD("Waiting for Card...");
		if(uartCharCount==10)
		{
		   i2c_eeprom_pageread(10, 0x50,arr,10);
		   if(strcmp(arr, ch)==0)
		   {
		   	CmdLCD(0x01);
			CmdLCD(0x80);
		   	StrLCD("Card Accepted");
			CmdLCD(0xc0);
			StrLCD(arr);
			CmdLCD(0x94);
			StrLCD(ch);
			delay_s(2);
			uartCharCount=0;
			CmdLCD(0x01);
			break;
		   }
		   else
		   {
		   		CmdLCD(0x01);
				CmdLCD(0x80);
		   		StrLCD("Card denied");
				CmdLCD(0xc0);
			    StrLCD(arr);
				CmdLCD(0x94);
			    StrLCD(ch);
				delay_s(2);
				uartCharCount=0;
				CmdLCD(0x01);
		   }
		}
	}
}
