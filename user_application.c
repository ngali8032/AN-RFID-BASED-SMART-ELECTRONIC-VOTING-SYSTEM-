#include "header.h"
extern int einto_interrupt; /*officer card interrupt*/
extern int CardPlaced;
extern int uartCharCount;
extern int votingStarted;
extern char ch[10];
int party1Cnt=0, party2Cnt=0, party3Cnt=0;
int CheckingpartyCount=0;
int usercardplacestarts;
char userPassword[11]; /*buffer reading user password from the eeprom*/
s8 des[11]; /*buffer Taking input using keypad*/
void user_card_checking(void)
{
	int officer_flag=0;
	int menu_break=0, numberOfCards;
	int i;
	char str;
	int passwordCnt=0; /*count password attempts*/	
	while(1)
	{
	label:
			if(votingStarted==0)
				return;
				passwordCnt=0; /*Again start from 0 password allowed only 3 times*/
				CmdLCD(0x80);
				StrLCD("Voting started");
				CmdLCD(0xc0);
				StrLCD("waiting for card");
		
	  			if(einto_interrupt)
					{	
						CmdLCD(0x01);
						officer_card_checking();
						einto_interrupt=0;
					} 
					
		if(CardPlaced && uartCharCount==10)
		{
			usercardplacestarts=100;
			numberOfCards = i2c_eeprom_read(0,0x50);
			delay_s(1);
			for(i=0; i<numberOfCards; i++){
				i2c_eeprom_pageread(usercardplacestarts, 0x50,des, 8);
				des[8]='\0';
				
				if(memcmp(des, ch+1,8)==0){
					CmdLCD(0x01);
					StrLCD("Card Accepted");
					CmdLCD(0xc0);
					StrLCD(des);
					CmdLCD(0x94);
					StrLCD(ch);
					delay_s(1);
				
					CardPlaced=0;
					uartCharCount=0;
					CmdLCD(0x01);
					officer_flag=1;
					break;
				}
			
				usercardplacestarts += 20;
				CardPlaced=0;
				uartCharCount=0;

			}
			if(officer_flag==0){
				CmdLCD(0x01);
				CmdLCD(0x80);
				StrLCD("Card Not Found");
				CmdLCD(0xc0);
				StrLCD(ch);
				delay_s(2);
		
				CardPlaced=0;
				uartCharCount=0;
			}
			
		}	
		if(officer_flag)
		{ 
			officer_flag=0;
			break;
		}
	}
	i2c_eeprom_pageread(usercardplacestarts+10, 0x50,userPassword, 4);
	userPassword[4]='\0';
	while(1)
	{
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
			if(strcmp(des,userPassword)==0)
			{
				CmdLCD(0x80);
				StrLCD("Pin Correct");
				delay_s(2);
				CmdLCD(0x01);
				break;
			}
			else
			{
				CmdLCD(0x80);
				StrLCD("incorrect Pin");
				CmdLCD(0xc0);
				StrLCD(des);
				CmdLCD(0x94);
				StrLCD(userPassword);
				delay_s(2);
				CmdLCD(0x01);
				passwordCnt++;
			}
			if(passwordCnt==3)
			{
				CmdLCD(0x01);
				StrLCD("Too many attempts");
				CmdLCD(0xc0);
				StrLCD("Try Again Later");
				delay_s(2);
				goto label;
			}
	}
	while(1)
	{
		char ch;
		CmdLCD(0x80);
		StrLCD("1.Voting");
		CmdLCD(0xc0);
		StrLCD("2.Edit Password");
		CmdLCD(0x94);
		StrLCD("3.EXIT");
		ch = KeyScan();
		switch(ch)
		{
			case '1': if(i2c_eeprom_read(usercardplacestarts+9,0x50))
								{
									CmdLCD(0x01);
									StrLCD("Voted Casted Not");
									CmdLCD(0xc0);
									StrLCD(" Allowed to Again");
									delay_s(1);
									CmdLCD(0x01);
									break;
								}
						delay_ms(200); CmdLCD(0x01); user_voting(); break;
			case '2': delay_ms(300); CmdLCD(0x01); CHANGE_PASSWORD(usercardplacestarts+10); break;
			case '3': CmdLCD(0x01); delay_ms(500); menu_break=1; break;
			default: CmdLCD(0x01);
					StrLCD("Invalid Input");
					delay_ms(300);
		} 

		if(menu_break)
		{
			delay_ms(100);
			CmdLCD(0x01);
			break;
		}
	}
}


void user_voting(void)
{
	int flag=0,flag1=0;
	while(1)
	{
		CmdLCD(0x80);
		StrLCD("1.Party1:");
		CharLCD(36);
		CmdLCD(0xc0);
		StrLCD("2.Party2:");
		CharLCD(206);
		CmdLCD(0x94);
		StrLCD("3.Party3:");
		CharLCD(224);

		CmdLCD(0xd4);
		StrLCD("4.Exit");

		switch(KeyScan())
		{
			case '1':	flag=1;
						party1Cnt++;
						i2c_eeprom_write(9, 0x50,party1Cnt);
						delay_ms(300);
						CmdLCD(0x01);
						CmdLCD(0x80);
						StrLCD("Vote casted ");
						CmdLCD(0xc0);
						StrLCD("successfully Party1:");
						CharLCD(36);
						CheckingpartyCount=i2c_eeprom_read(9,0x50);
						CmdLCD(0x94);
						U32LCD(CheckingpartyCount);
						delay_s(1);
						break;
			case '2': party2Cnt++;
						flag=1;
					i2c_eeprom_write(10, 0x50,party2Cnt);
					delay_ms(300);
					CmdLCD(0x01);
					CmdLCD(0x80);
					StrLCD("Vote casted ");
					CmdLCD(0xc0);
					StrLCD("successfully part2:");
					CharLCD(206);
					CheckingpartyCount=i2c_eeprom_read(10,0x50);
					CmdLCD(0x94);
					U32LCD(CheckingpartyCount);
					delay_s(1);
					break;

			case '3': 	flag=1;
						party3Cnt++;
					i2c_eeprom_write(11, 0x50,party3Cnt);
					delay_ms(300);
					CmdLCD(0x01);
					CmdLCD(0x80);
					StrLCD("Vote casted ");
					CmdLCD(0xc0);
					StrLCD("successfully part3:");
					CharLCD(224);
					CheckingpartyCount=i2c_eeprom_read(11,0x50);
					CmdLCD(0x94);
					U32LCD(CheckingpartyCount);
					delay_s(1);
					break;
			case '4': flag1=1; delay_ms(300); break;
			default: delay_ms(300); 
							CmdLCD(0x01); 
							StrLCD("Invalid Vote");
							delay_s(2);
		}
		if(flag){
			i2c_eeprom_write(usercardplacestarts+9, 0x50,1);
			break;
		}
		else if(flag1) break;
	}
	CmdLCD(0x01);
	user_card_checking();
}

int checkOldPin(char *ptr)
{
	int j,i, index=0;
	char ch,pinbuffer[5];
	CmdLCD(0xc0);
	for(i=0; i<100; i++)
	{
		ch=KeyScan();
		delay_ms(300);
		
		if(ch>='0' && ch<='9'){
			CmdLCD(0xc0+index);
			CharLCD(ch);
			pinbuffer[index++]=ch;
			if(index==4) break;
		}
		else
		{
			CmdLCD(0xd4);
			StrLCD("use only digits");
			CmdLCD(0xd4);
			for(j=0; j<20; j++)
			{
				CharLCD(' ');
				delay_ms(50);
			}
		}
		CmdLCD(0x94);
		U32LCD(i);
	}
	pinbuffer[4]='\0';
	if(strcmp(pinbuffer, ptr)==0)
		return 1;
	else
		return 0;
}

void enterNewPin(char *pinbuffer)
{
	unsigned int j,i, index=0;
	char ch;
	CmdLCD(0xc0);
	for(i=0; i<4; i++)
	{
		ch=KeyScan();
		delay_ms(300);
		
		if(ch>='0' && ch<='9'){
			CmdLCD(0xc0+index);
			CharLCD(ch);
			pinbuffer[index++]=ch;
			if(index==4) break;
		}
		else
		{
			CmdLCD(0xd4);
			StrLCD("use only digits");
			CmdLCD(0xd4);
			for(j=0; j<20; j++)
			{
				CharLCD(' ');
				delay_ms(50);
			}
		}
	}
	pinbuffer[4]='\0';
}

void CHANGE_PASSWORD(int address)
{
	char oldpin[5], newpin[5];
	i2c_eeprom_pageread(address, 0x50,oldpin, 4); /*reading from eeprom*/
	oldpin[4]='\0';
	
	CmdLCD(0x01);
	StrLCD("Enter Pin");
	if(!(checkOldPin(oldpin)))
	{
		CmdLCD(0x01);
		StrLCD("Old pin Not Matched");
		delay_s(1);
		return;
	}
	CmdLCD(0x01);
	StrLCD("Enter New PIN");
	enterNewPin(newpin); /*for new pin*/
	
	CmdLCD(0x01);
	StrLCD("Enter confrom PIN");
	if(!(checkOldPin(newpin)))
	{
		CmdLCD(0x01);
		StrLCD("New pin Conform");
		CmdLCD(0xc0);
		StrLCD("Not matched");
		delay_s(1);
		return;
	}
	i2c_eeprom_pagewrite(address,0x50,newpin, 4);
	return;
}
