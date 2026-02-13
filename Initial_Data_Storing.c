#include <lpc21xx.h>
#include "header.h"
extern char ch[10];
extern int CardPlaced;  /*flag for uart interrupt*/ 
extern int uartCharCount; /*no.of bytes collected by the uart interrupt*/

int cardsCount=0;   /*No.Of users*/
static int cards_place = 100;
static int cards_place_flag=109;
static int password_place = 110;

int main()
{
	int flag=0, i, x;
	char buffer[11]; 
	int cardStored=0;
	int checkCardAvailable=20;
	s8 des[9];
	char *password = "1234";
	

	Init_i2c();
	Init_LCD();					  
	UART0_Init();
	Init_KPM();

	StrLCD("first storing flags");
	delay_ms(500);

	/*storing flags and time and count*/
	for(i=0; i<12; i++)
	{
		CmdLCD(0x01);
		StrLCD("No.Of Cards:");
		i2c_eeprom_write(i, 0x50,0);
		x = i2c_eeprom_read(i, 0x50);
		U32LCD(x);
		delay_ms(500);
	}

	/*officier card*/
	CmdLCD(0x01);
	while(1){
		CmdLCD(0x80);
		StrLCD("place officer card");
		if(CardPlaced && uartCharCount==10){
			CmdLCD(0xc0);
			i2c_eeprom_pagewrite(50, 0x50,ch+1, 8);
			delay_ms(100);
			i2c_eeprom_pageread(50, 0x50,des, 8);
			des[8]='\0';
			StrLCD(des);
			delay_s(3);
			flag=1;
			
			CardPlaced=0;
			uartCharCount=0;
		}
		if(flag) break;
	}
	
		/*CmdLCD(0x01);
		i2c_eeprom_pagewrite(60, 0x50,"1234567890", 10);
		delay_ms(100);
		CmdLCD(0x80);
		i2c_eeprom_pageread(60, 0x50,buffer, 10);
		StrLCD(buffer);
		delay_s(3);
		CmdLCD(0x01);*/

			/*storing passwords*/
				CmdLCD(0x01);
				i2c_eeprom_pagewrite(70, 0x50,password, 4);
				delay_ms(10);
				i2c_eeprom_pageread(70, 0x50,buffer,4);
				CmdLCD(0x80);
				StrLCD("password");
				CmdLCD(0xc0);
				StrLCD(buffer);
				delay_s(2);
				CmdLCD(0x01);

	while(1)
	{
		CmdLCD(0x80);
		StrLCD("Place a user ");
		U32LCD(i2c_eeprom_read(0, 0x50));
		StrLCD(" card");
		if(CardPlaced && uartCharCount==10)
		{
			checkCardAvailable=100;
			for(i=0; i<cardsCount; i++)
			{
				CmdLCD(0x01);
				i2c_eeprom_pageread(checkCardAvailable, 0x50,des, 8);
				CmdLCD(0x80);
				des[8]='\0';
				StrLCD(des);
				CmdLCD(0xc0);
				StrLCD(ch);
				delay_s(1);


				if(memcmp(des, ch+1, 8)==0){
					cardStored=1;
					break;
				}
				checkCardAvailable += 20;		
			}

			if(cardStored==0){
				CmdLCD(0x01);
				i2c_eeprom_pagewrite(cards_place, 0x50,ch+1, 8);
				delay_ms(10);
				i2c_eeprom_pageread(cards_place, 0x50,des, 8);
				CmdLCD(0x80);
				des[8]='\0';
				StrLCD(des);
				CmdLCD(0xc0);
				StrLCD(ch);
				CmdLCD(0x94);
				StrLCD("Card Accepted");
				delay_s(1);
				
				CardPlaced=0;	//make 0 for other card
				cards_place += 20;	//eeprom storage  
				cardsCount++;   //incrementing no.of cards
				uartCharCount=0;   //making char count again '0'
				cardStored=0;	   /*used for loop whether the data stored before*/
				
				CmdLCD(0xd4);	  /*Storing no.of cards*/
				i2c_eeprom_write(0x0000, 0x50,cardsCount);
				StrLCD("NO.Of Cards:-");
				U32LCD(i2c_eeprom_read(0x0000, 0x50));
				CharLCD(' ');
				
				/*Storing no.of cards flag*/
				i2c_eeprom_write(cards_place_flag, 0x50,0);
				U32LCD(i2c_eeprom_read(cards_place_flag, 0x50));
				cards_place_flag += 20;
				delay_s(2);

				/*storing passwords*/
				CmdLCD(0x01);
				i2c_eeprom_pagewrite(password_place, 0x50,password, 4);
				delay_ms(10);
				i2c_eeprom_pageread(password_place, 0x50,buffer,4);
				CmdLCD(0x80);
				StrLCD("password");
				CmdLCD(0xc0);
				StrLCD(buffer);
				delay_s(2);

				password_place += 20;
				CmdLCD(0x01);
			}

			else
			{
				CmdLCD(0x01);
				CmdLCD(0x80);
				StrLCD("Card Alread Placed");
				CmdLCD(0xc0);
				StrLCD(ch);
				CmdLCD(0x94);
				StrLCD(des);

				uartCharCount=0;	  /*Make uartCharcount=0*/
				CardPlaced=0;
				cardStored=0;		  /*Make card=0 for to allow other card*/
				delay_s(1);
				CmdLCD(0x01);
			}
		}
	}		
}