#include "header.h"
extern int CardPlaced;
extern int uartCharCount;
extern char ch[11];
void officer_card_checking(void)
{
	int i;/*for password loop*/
	int passwordCnt=0;
	int menu_break=0;
	char des[9];
	char officerPassword[11];
	//int index=0;		 /*used for key scan indexing*/
	char str; /*use for key press*/

	i2c_eeprom_pageread(50, 0x50,des, 8); /*reading card from eeprom from officer location*/
	des[8]='\0';
	while(1)
	{
		CmdLCD(0x80);
		StrLCD("officer card....");
		
		if(CardPlaced && uartCharCount==10)
		{
			if(memcmp(des, ch+1, 8)==0){
				CmdLCD(0x01);
				StrLCD("Card Accepted");
				CmdLCD(0xc0);
				StrLCD(des);
				delay_s(2);

				CardPlaced=0;
				uartCharCount=0;
				CmdLCD(0x01);
				break;
			}
			else
			{
				CmdLCD(0x01);
				CmdLCD(0x80);
				StrLCD("Wrong Card");
				CmdLCD(0xc0);
				StrLCD(ch);
				delay_s(2);
				
				CardPlaced=0;
				uartCharCount=0;
				CmdLCD(0x01);
			}
		}	
	}
	i2c_eeprom_pageread(70, 0x50,officerPassword, 4); /*reading password from officer location from eeprom*/
	officerPassword[4]='\0';
	
	 while(1){
		  /*password count for officer*/
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("Enter the PIN");
		CmdLCD(0xc0);
		for(i=0; i<4; i++)
		{
			str = KeyScan();
			delay_ms(300);
			if(str=='C' && i!=0)
			{
					--i;
					CmdLCD(0XC0+i);
					CharLCD(' ');
					--i;
			}
			if(str=='E') break;
			if(str>='0' && str<='9'){
				CmdLCD(0XC0+i);
				CharLCD(str);
				des[i] = str;
			}
		}
		des[i]='\0';
		delay_ms(500);
		CmdLCD(0X01);
			if(strcmp(des,officerPassword)==0)
			{
				CmdLCD(0x80);
				StrLCD("Correct PIN");
				delay_s(1);
				CmdLCD(0x01);
				break;
			}
			else
			{
				CmdLCD(0x01);
				passwordCnt++;
				CmdLCD(0x80);
				StrLCD("incorrect PIN");	
				delay_s(1);
				CmdLCD(0x01);
			}
			if(passwordCnt==3)
			{
				CmdLCD(0x01);
				CmdLCD(0x80);
				StrLCD("Too many attempts");
				CmdLCD(0xc0);
				StrLCD("wait: ");
				for(passwordCnt=0; passwordCnt<15; passwordCnt++){
						U32LCD(passwordCnt);
						delay_s(1);
				}
				passwordCnt=0;
			}
	}
	while(1)
	{

		char ch;
		CmdLCD(0x80);
		StrLCD("1.SET V0 T2.START VT");
		CmdLCD(0xc0);
		StrLCD("3.STOP VOT4.VIEW RES");
		CmdLCD(0x94);
		StrLCD("5.RES VOTI6.RTC EDIT");
		CmdLCD(0xd4);
		StrLCD("7.EXIT");
		ch = KeyScan();
		switch(ch)
		{
			case '1': delay_ms(200); CmdLCD(0x01); setStartEndVoting(); break;
			case '2': delay_ms(300); CmdLCD(0x01); startVoting(); break;
			case '3': delay_ms(300); CmdLCD(0x01); stopVoting(); break;
			case '4': CmdLCD(0x01); viewResults(); break;
			case '5': resetVoting(); break;
			case '6': Edit_RTC_Info(); break;
			case '7': CmdLCD(0x01); delay_ms(500); menu_break=1; break;
			default: CmdLCD(0x01);
					StrLCD("Invalid Input");
					delay_ms(3);
		} 
		if(menu_break)
		{
			delay_ms(100);
			CmdLCD(0x01);
			break;
		}
	}
}

