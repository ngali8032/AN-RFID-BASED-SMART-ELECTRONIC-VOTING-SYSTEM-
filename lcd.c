//lcd.c
#include <lpc21xx.h>
#include "types.h"
#include "lcd_defines.h"
#include "delay.h"

void WriteLCD(u8 byte)
{
	//select write operations
	IOCLR0 = 1<<LCD_RW;
	
	//write any byte onto data pins(d0-d7)
	IOPIN0 = ((IOPIN0 & ~(255<<LCD_DATA))|(byte<<LCD_DATA));
	
	//provide high to low pulse for latching
	IOSET0 = 1<<LCD_EN;
	delay_us(1);
	IOCLR0 = 1<<LCD_EN;
	
	//byte between byte time
	delay_ms(2);
}

void CmdLCD(u8 CmdByte)
{
	//select cmd register
	IOCLR0 = 1<<LCD_RS;
	
	//write to cmd register via data pins
	WriteLCD(CmdByte);
}

void Init_LCD(void)
{
	//cfg lcd 8 data pins & 3 control pins as gpio out
	IODIR0 = 255<<LCD_DATA|1<<LCD_RS|1<<LCD_RW|1<<LCD_EN;
	
	//power on delay
	delay_ms(15);
	
	//initilization sequence start
	CmdLCD(MODE_8BIT_1LINE);
	delay_us(4100);
	CmdLCD(MODE_8BIT_1LINE);
	delay_us(100);
	CmdLCD(MODE_8BIT_1LINE);
	CmdLCD(MODE_8BIT_2LINE);
	CmdLCD(DSP_ON_CUR_OFF);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
	//initilization sequence end
}

void CharLCD(u8 asciival)
{
	//select data register
	IOSET0 = 1<<LCD_RS;
	
	//write to ddram/display via data register
	WriteLCD(asciival);
}

void StrLCD(s8 *p)
{
	while(*p){
		delay_us(300);
		CharLCD(*p++);
	}
}

void U32LCD(u32 n)
{
	u8 digit[10]; s32 i=0;
	
	if(n==0) { CharLCD('0');}
	else
	{
		while(n>0)
		{
			digit[i++] = (n%10)+48;
			n /= 10;
		}
		for(--i; i>=0; i--)
		{
			CharLCD(digit[i]);
		}
	}
}

void S32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n = -n;
	}
	U32LCD(n);
}

void F32LCD(f32 fn, u32 nDP)
{
	u32 n, i;
	if(fn<0.0)
	{
		CharLCD('-');
		fn = -fn;
	}
	n = fn;
	U32LCD(n);
	CharLCD('.');
	for(i=0; i<nDP; i++)
	{
		fn = (fn-n)*10;
		n = fn;
		CharLCD(n+48);
	}
}


void BuildCGRAM(u8 *P, u8 nBytes)
{
	u32 i;
	
	//point to cgram start
	CmdLCD(GOTO_CGRAM_START);
	
	//select data register
	IOSET0 = 1<<LCD_RS;
	
	//write to cgram, reg bytes for custom char
	for(i=0; i<nBytes; i++)
	{
		WriteLCD(P[i]);
	}
	
	//point back to ddram
	CmdLCD(GOTO_LINE1_POS0);
}
