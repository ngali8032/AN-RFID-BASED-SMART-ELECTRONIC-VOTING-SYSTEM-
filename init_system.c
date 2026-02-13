/*init_system*/
#include <lpc21xx.h>
#include "header.h"
extern int CardPlaced;
extern int einto_interrupt;
extern int votStartHR, votStartMIN, VotStartSEC, VotEndHR, votEndMIN, votEndSEC;
extern int votingStarted;
void Init_system(void)
{
	int time;
	Init_LCD();
	Init_interrupt();
	Init_KPM();
	UART0_Init();
	Init_i2c();

	CmdLCD(0x80);
	StrLCD("RFID Based");
	CmdLCD(0xc0);
	StrLCD("Electronic Voting");\
	CmdLCD(0x94);
	StrLCD("System");
   delay_s(3);

   CmdLCD(0x01);

				/*Reading TIME from EEPROM*/

	if(i2c_eeprom_read(2, 0x50))
		votingStarted=1;
	/*else
		system_Init();*/
		
  if(i2c_eeprom_read(0x01, 0x50)==1)
	{		
   		time=i2c_eeprom_read(3,0x50);
		votStartHR = time;

   		time=i2c_eeprom_read(4,0x50);
		votStartMIN = time;
		
   		time=i2c_eeprom_read(5,0x50);
		VotStartSEC = time; 

   		time=i2c_eeprom_read(6,0x50);
		VotEndHR = time; 
		
   		time=i2c_eeprom_read(7,0x50);
		votEndMIN = time;  
   		
		time=i2c_eeprom_read(8,0x50);
		votEndSEC = time;
	}

}


void Init_time(void)
{
	RTC_Init();
	system_Init();
	display_RTC();
	delay_s(3);
	CmdLCD(0x01);
}


void Edit_RTC_Info(void) /*function defination for Edit RTC_Info*/
{
	u32 flag=0;
	while(1){
		CmdLCD(0x01);
		StrLCD("1-H 2-MI 3-S 4-D");
		CmdLCD(0xc0);
		StrLCD("5-D 6-MO 7-Y 8-E");
		delay_ms(300);
		switch(KeyScan())
		{
			case '1': Edit_HOUR(); /*Function call for Edit Hour*/break;
			case '2': Edit_MIN(); /*Function call for Edit minute*/break;
			case '3': Edit_SEC(); /*Function call for Edit second*/break;
			case '4': Edit_DAY(); /*Function call for Edit day*/break;
			case '5': Edit_DATE(); /*Function call for Edit date*/break;
			case '6': Edit_MONTH(); /*Function call for Edit date*/break;
			case '7': Edit_YEAR(); /*Function call for Edit date*/break;
			case '8': CmdLCD(0x01); flag=1; break;
			default : CmdLCD(0x01); StrLCD("Invalid Input");  
								delay_ms(1000);
								CmdLCD(0x01);
								break;
		}		
			if(flag) break;
	}
}

void Edit_HOUR() /*Function defination for Edit Hour*/
{
	s32 hr=0, i;
	char key;
	CmdLCD(0x01);
	StrLCD("ENTER HOUR");
	CmdLCD(0xc0);
	StrLCD("CHr:");
	U32LCD(HOUR);
	StrLCD(" EHr:");
	CmdLCD(0xc0+12);
	for(i=11; i<17; i++)
	{
		delay_ms(300);
		key = KeyScan();
		if(key=='C' && i!=11)
		{
				--i;
				CmdLCD(0XC0+i);
			 	CharLCD(' ');
				--i;
		}
		if(key=='E') break;
		if(key!='C'){
			CmdLCD(0XC0+i);
			CharLCD(key);
			hr = (key-48)+hr*10;
		}
	}
	if(hr>=0 && hr<=23){
		SetRTCTimeInfo(hr, MIN, SEC);
	}
	else
	{
		hr=0;
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("Invalid HOURS");
		delay_ms(500);
		CmdLCD(0x01);
	}
	delay_ms(500);
	CmdLCD(0x01);
}

void Edit_MIN() /*Function defination for Edit minute*/
{
	s32 min=0, i;
	char key;
	CmdLCD(0x01);
	StrLCD("ENTER MINUTES");

	CmdLCD(0xc0);

	StrLCD("CMI:");

	U32LCD(MIN);

	StrLCD("  EMI:");

	CmdLCD(0xc0+12);

	for(i=12; i<17; i++)

	{

		delay_ms(300);

		key = KeyScan();

		if(key=='C' && i!=13)

		{

				--i;

				CmdLCD(0XC0+i);

			 	CharLCD(' ');

				--i;

		}

		if(key=='E') break;

		if(key!='C'){

			CmdLCD(0XC0+i);

			CharLCD(key);

			min = (key-48)+min*10;

		}

	}

	if(min>=0 && min<=59){
		SetRTCTimeInfo(HOUR, min, SEC);
	}

	else

	{

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("Invalid minutes");

		delay_ms(500);

		CmdLCD(0x01);

	}

	delay_ms(500);

	CmdLCD(0x01);

}


void Edit_SEC() /*Function defination for Edit second*/

{

	s32 sec=0, i;

	char key;

	CmdLCD(0x01);

	StrLCD("Enter SECONDS");

	CmdLCD(0xc0);

	StrLCD("CSE:");

	U32LCD(SEC);

	StrLCD("  ESE:");

	CmdLCD(0xc0+12);

	for(i=12; i<17; i++)

	{

		delay_ms(300);

		key = KeyScan();

		if(key=='C' && i!=13)

		{

				--i;

				CmdLCD(0XC0+i);

			 	CharLCD(' ');

				--i;

		}

		if(key=='E') break;

		if(key!='C'){

			CmdLCD(0XC0+i);

			CharLCD(key);

			sec = (key-48)+sec*10;

		}

	}

	if(sec>=0 && sec<=59){
		SetRTCTimeInfo(HOUR, MIN, sec);
	}

	else

	{

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("Invalid Seconds");

		delay_ms(500);

		CmdLCD(0x01);

	}

	delay_ms(500);

	CmdLCD(0x01);

}


void Edit_DAY(void) /*Function defination for Edit day*/

{

	s32 day;

	CmdLCD(0x01);

	StrLCD("Chose Choice");

	delay_ms(500);

	CmdLCD(0x01);

	StrLCD("0SU 1MO 2TU 3WED");

	CmdLCD(0xc0);

	StrLCD("4THU 5FRI 6SAT");

	day = KeyScan()-48;

	if(day>=0 && day<=6)
	{
		SetRTCDay(day);
	}

	else

	{

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("Invalid day");

		delay_ms(500);

		CmdLCD(0x01);

	}

}


void Edit_DATE() /*Function defination for Edit date*/

{

	s32 date=0, i;

	char key;

	CmdLCD(0x01);

	StrLCD("Enter DATE");

	CmdLCD(0xc0);

	StrLCD(" Date:-");

	CmdLCD(0xc0+7);

	for(i=7; i<11; i++)

	{

		delay_ms(300);

		key = KeyScan();

		if(key=='C' && i!=7)

		{

				--i;

				CmdLCD(0XC0+i);

			 	CharLCD(' ');

				--i;

			date /= 10;

		}

		if(key=='E') break;

		if(key!='C'){

			CmdLCD(0XC0+i);

			CharLCD(key);

			date = (key-48)+date*10;

		}

	}

	if(date>=1 && date<=31)
	{
		SetRTCDateInfo(date, MONTH, YEAR);
	}
	else

	{

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("Invalid date");

		delay_ms(500);

		CmdLCD(0x01);

	}

	delay_ms(500);

	CmdLCD(0x01);

}


void Edit_MONTH() /*Function defination for Edit month*/

{

	s32 month=0, i;

	char key;

	CmdLCD(0x01);

	StrLCD("Enter MONTH");

	CmdLCD(0xc0);

	StrLCD("Month:-");

	CmdLCD(0xc0+7);

	for(i=7; i<11; i++)

	{

		delay_ms(300);

		key = KeyScan();

		if(key=='C' && i!=7)

		{

				--i;

				CmdLCD(0XC0+i);

			 	CharLCD(' ');

				--i;

			month /= 10;

		}

		if(key=='E') break;

		if(key!='C'){

			CmdLCD(0XC0+i);

			CharLCD(key);

			month = (key-48)+month*10;

		}

	}

	if(month>=1 && month<=12)
	{
		SetRTCDateInfo(DOM, month, YEAR);
	}

	else

	{

		CmdLCD(0x01);

		CmdLCD(0x80);

		StrLCD("Invalid MONTH");

		delay_ms(500);

		CmdLCD(0x01);

	}

	delay_ms(500);

	CmdLCD(0x01);

}


void Edit_YEAR() /*Function defination for Edit year*/

{

	s32 year=0, i;

	char key;

	CmdLCD(0x01);

	StrLCD("Enter YEAR");

	CmdLCD(0xc0);

	StrLCD(" Year:-");

	CmdLCD(0xc0+7);

	for(i=7; i<11; i++)

	{

		delay_ms(300);

		key = KeyScan();

		if(key=='C' && i!=7)

		{

				--i;

				CmdLCD(0XC0+i);

			 	CharLCD(' ');

				--i;

				year /= 10;

		}

		if(key=='E') break;

		if(key!='C'){

			CmdLCD(0XC0+i);

			CharLCD(key);

			year = (key-48)+year*10;

		}

	}

	if(year>=1 && year<=4095)
	{
		SetRTCDateInfo(DOM, MONTH, year);
	}
	else
	{
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("Invalid YEAR");
		delay_ms(500);
		CmdLCD(0x01);
	}
	delay_ms(500);
	CmdLCD(0x01);
}