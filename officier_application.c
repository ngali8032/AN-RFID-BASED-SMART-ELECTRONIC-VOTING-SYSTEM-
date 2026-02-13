#include "header.h"
int votingStarted=0;
extern int party1Cnt, party2Cnt, party3Cnt;
void startVoting(void)
{
	int flag=0;
	while(1){
	CmdLCD(0x80);
	StrLCD("Start Voting");
	CmdLCD(0xc0);
	StrLCD("1.YES");
	CmdLCD(0x94);
	StrLCD("2.NO");
	switch(KeyScan())
	{
		  case '1': CmdLCD(0x01);	  //Flag for start voting
								i2c_eeprom_write(2, 0x50,1);
								
								flag=1;
								votingStarted=1;
		
								CmdLCD(0x80);
							StrLCD("Voting process");
							CmdLCD(0xc0);
							StrLCD("started:");
							U32LCD(i2c_eeprom_read(2, 0x50));
							delay_s(2);
							CmdLCD(0x01);
							break;
			case '2': flag=1; delay_ms(300); CmdLCD(0x01);break; 
		}
	if(flag) break;
	}
}


void stopVoting(void)
{
	int flag=0;
	while(1){
	CmdLCD(0x80);
	StrLCD("STOP Voting");
	CmdLCD(0xc0);
	StrLCD("1.YES");
	CmdLCD(0x94);
	StrLCD("2.NO");
	switch(KeyScan())
	{
		  case '1': CmdLCD(0x01);	  //Flag for start voting
								i2c_eeprom_write(2, 0x50,0);
								flag=1;
								votingStarted=0; /*flag for voting process*/
		
								CmdLCD(0x80);
								StrLCD("Voting process");
								CmdLCD(0xc0);
								StrLCD("stopped:");
								U32LCD(i2c_eeprom_read(2, 0x50));
								delay_s(2);
		
								CmdLCD(0x01);
								break;
			case '2': flag=1; delay_ms(300); CmdLCD(0x01);break; 
		}
	if(flag) break;
	}
}
void resetVoting(void)
{
	int i,no_of_users;  /*no.of cards*/
	char user_card[10]; /*buffer for no.of cards*/
	int cards_place = 100;  /*cards starts from*/
	int cards_place_flag=109; /*cards flag starting*/
	no_of_users = i2c_eeprom_read(0x00, 0x50);  /*read no.of cards*/
	
	/*Partys counts making all 0*/
	party1Cnt=0; i2c_eeprom_write(9, 0x50,0); /*party1*/
	party2Cnt=0; i2c_eeprom_write(10, 0x50,0); /*party2*/
	party3Cnt=0;  i2c_eeprom_write(11, 0x50,0); /*party3*/
	
	for(i=0; i<no_of_users; i++)
	{
		i2c_eeprom_pageread(cards_place, 0x50,user_card, 8);
		user_card[8]='\0';
		
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD(user_card);	
			/*Before reseting*/
		CmdLCD(0xc0);
		StrLCD("Befor reseting:");
		U32LCD(i2c_eeprom_read(cards_place_flag, 0x50));
		
			  /*After Reseting*/
		CmdLCD(0x94);
		i2c_eeprom_write(cards_place_flag, 0x50,0);
		StrLCD("After Reseting:");
		U32LCD(i2c_eeprom_read(cards_place_flag, 0x50));
		delay_s(2);
		
		cards_place_flag += 20;
		cards_place += 20;
	}
}

void viewResults(void)
{
	CmdLCD(0x01);
	StrLCD("Part1:");
	CharLCD(36);
	StrLCD("->");
	U32LCD(i2c_eeprom_read(9, 0x50));
	
	CmdLCD(0xc0);
	StrLCD("Part2:");
	CharLCD(206);
	StrLCD("->");
	U32LCD(i2c_eeprom_read(10, 0x50));
	
	CmdLCD(0x94);
	StrLCD("Part3:");
	CharLCD(224);
	StrLCD("->");
	U32LCD(i2c_eeprom_read(11, 0x50));
	
	CmdLCD(0xd4);
	StrLCD("4.Exit");
	delay_ms(500);
	switch(KeyScan())
	{
		case '4': delay_ms(300); break;
		default : delay_ms(300); break;
	}
}