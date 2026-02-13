#include "header.h"
int votStartHR=0, votStartMIN=0, VotStartSEC=0, VotEndHR=0, votEndMIN=0, votEndSEC=0;
void setStartEndVoting(void)
{
	while(1)
	{
		/*Keeping flag for time edited*/
				i2c_eeprom_write(1, 0x50,1); 
		
		CmdLCD(0x80);
		StrLCD("1.Enter Start Time");
		CmdLCD(0xc0);
		StrLCD("2.Enter End Time");
		CmdLCD(0x94);
		StrLCD("3.Exit");

		switch(KeyScan())
		{
			case '1': delay_ms(200); CmdLCD(0x01); EditStartTime(); break;
			case '2': delay_ms(200); CmdLCD(0x01); EditEndTime(); break;
			case '3': delay_ms(500); CmdLCD(0x01); return;
			default: CmdLCD(0x01); StrLCD("invalid input"); delay_ms(500); CmdLCD(0x01);
		}
	}
}

void EditStartTime(void)
{
	int flag=0;
	while(1)
	{
		CmdLCD(0x80);
		StrLCD("1.Enter Start HR");
		CmdLCD(0xc0);
		StrLCD("2.Enter Start MIN");
		CmdLCD(0x94);
		StrLCD("3.Enter Start SEC");
		CmdLCD(0xd4);
		StrLCD("4.Exit");
		switch(KeyScan())
		{
			case '1': delay_ms(200); CmdLCD(0x01); EditStartHR(); break;
			case '2': delay_ms(200); CmdLCD(0x01);EditStartMIN(); break;
			case '3': delay_ms(200); CmdLCD(0x01);EditStartSEC(); break;
			case '4': delay_ms(500); CmdLCD(0x01); flag=1; break;
		}
		if(flag) break;
	}
}

void EditStartHR(void) /*Function defination for Edit start HR*/
{
	s32 hr=0, i;
	char key;
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("ENTER start HOUR");
	CmdLCD(0xc0);
	for(i=0; i<17; i++)
	{
		delay_ms(300);
		key = KeyScan();
		if(key=='C' && i!=0)
		{
				--i;
				CmdLCD(0XC0+i);
			 	CharLCD(' ');
				--i;
				hr /= 10;
		}
		if(key=='E') break;
		if(key!='C'){
			CmdLCD(0XC0+i);
			CharLCD(key);
			hr = (key-48)+hr*10;
		}
	}
	if(hr>=0 && hr<=23)
	{
		votStartHR=hr;
		i2c_eeprom_write(3, 0x50,hr);   
			CmdLCD(0x01);
   		CmdLCD(0x80);
   		StrLCD("VOT STARTING HOUR: ");
   		U32LCD(i2c_eeprom_read(3,0x50));
			CmdLCD(0xc0);
			U32LCD(hr);
   		delay_ms(500);
		CmdLCD(0x01);
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

void EditStartMIN(void) /*Function defination for Edit start HR*/
{
	s32 min=0, i;
	char key;
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("ENTER start MIN");
	CmdLCD(0xc0);
	for(i=0; i<17; i++)
	{
		delay_ms(300);
		key = KeyScan();
		if(key=='C' && i!=0)
		{
				--i;
				CmdLCD(0XC0+i);
			 	CharLCD(' ');
				--i;
				min /= 10;
		}
		if(key=='E') break;
		if(key!='C'){
			CmdLCD(0XC0+i);
			CharLCD(key);
			min = (key-48)+min*10;
		}
	}
	if(min>=0 && min<=59){
		votStartMIN=min;
		i2c_eeprom_write(4, 0x50,min);   		
   		CmdLCD(0x80);
   		StrLCD("VOT STARTING MIN:- ");
   		U32LCD(i2c_eeprom_read(4,0x50));
   		delay_ms(500);
		CmdLCD(0x01);
	}	
	else
	{
		min=0;
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("Invalid MINS");
		delay_ms(500);
		CmdLCD(0x01);
	}
	delay_ms(500);
	CmdLCD(0x01);
}


void EditStartSEC(void) /*Function defination for Edit start HR*/
{
	s32 sec=0, i;
	char key;
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("ENTER start SEC");
	CmdLCD(0xc0);
	for(i=0; i<17; i++)
	{
		delay_ms(300);
		key = KeyScan();
		if(key=='C' && i!=0)
		{
				--i;
				CmdLCD(0XC0+i);
			 	CharLCD(' ');
				--i;
				sec /= 10;
		}
		if(key=='E') break;
		if(key!='C'){
			CmdLCD(0XC0+i);
			CharLCD(key);
			sec = (key-48)+sec*10;
		}
	}
	if(sec>=0 && sec<=59)
	{
		VotStartSEC=sec;	
		i2c_eeprom_write(5, 0x50,sec);   		
   		CmdLCD(0x80);
   		StrLCD("VOT STARTING SEC:- ");
   		U32LCD(i2c_eeprom_read(5,0x50));
   		delay_ms(500);
		CmdLCD(0x01);
	}
	else
	{
		sec=0;
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("Invalid HOURS");
		delay_ms(500);
		CmdLCD(0x01);
	}
	delay_ms(500);
	CmdLCD(0x01);
}
void EditEndTime(void)
{
	int flag=0;
	while(1)
	{
		CmdLCD(0x80);
		StrLCD("1.Enter End HR");
		CmdLCD(0xc0);
		StrLCD("2.Enter End MIN");
		CmdLCD(0x94);
		StrLCD("3.Enter End SEC");
		CmdLCD(0xd4);
		StrLCD("4.Exit");

		switch(KeyScan())
		{
			case '1': EditEndHR(); break;
			case '2': EditEndMIN(); break;
			case '3': EditEndSEC(); break;
			case '4': CmdLCD(0x01); delay_ms(500); flag=1; break;
		}
		if(flag) break;
	}
}

void EditEndHR(void) /*Function defination for Edit start HR*/
{
	s32 hr=0, i;
	char key;
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("ENTER End HOUR");
	CmdLCD(0xc0);

	for(i=0; i<17; i++)
	{
		delay_ms(300);
		key = KeyScan();
		if(key=='C' && i!=0)
		{
				--i;
				CmdLCD(0XC0+i);
			 	CharLCD(' ');
				--i;
				hr /= 10;
		}
		if(key=='E') break;
		if(key!='C'){
			CmdLCD(0XC0+i);
			CharLCD(key);
			hr = (key-48)+hr*10;
		}
	}

	if(hr>=0 && hr<=23)
	{
			VotEndHR=hr;	
			i2c_eeprom_write(6, 0x50,hr);   		
   		CmdLCD(0x80);
   		StrLCD("VOT END HOUR: ");
   		U32LCD(i2c_eeprom_read(6,0x50));
   		delay_ms(500);
			CmdLCD(0x01);
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
}

void EditEndMIN(void) /*Function defination for Edit start HR*/
{
	s32 min=0, i;
	char key;
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("ENTER End MIN");
	CmdLCD(0xc0);
	for(i=0; i<17; i++)
	{
		delay_ms(300);
		key = KeyScan();
		if(key=='C' && i!=0)
		{
				--i;
				CmdLCD(0XC0+i);
			 	CharLCD(' ');
				--i;
				min /= 10;
		}
		if(key=='E') break;
		if(key!='C'){
			CmdLCD(0XC0+i);
			CharLCD(key);
			min = (key-48)+min*10;
		}
	}
	if(min>=0 && min<=59)
	{
		votEndMIN=min;	
		i2c_eeprom_write(7, 0x50,min);   		
   		CmdLCD(0x80);
   		StrLCD("VOT END MIN:- ");
   		U32LCD(i2c_eeprom_read(7,0x50));
		CharLCD(min);
		delay_ms(500);
		CmdLCD(0x01);
	}
	else
	{
		min=0;
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("Invalid MINS");
		delay_ms(500);
		CmdLCD(0x01);
	}
}


void EditEndSEC(void) /*Function defination for Edit start HR*/
{
	s32 sec=0, i;
	char key;
	CmdLCD(0x01);
	CmdLCD(0x80);
	StrLCD("ENTER End SEC");
	CmdLCD(0xc0);
	for(i=0; i<17; i++)
	{
		delay_ms(300);
		key = KeyScan();
		if(key=='C' && i!=0)
		{
				--i;
				CmdLCD(0XC0+i);
			 	CharLCD(' ');
				--i;
				sec /= 10;
		}
		if(key=='E') break;
		if(key!='C'){
			CmdLCD(0XC0+i);
			CharLCD(key);
			sec = (key-48)+sec*10;
		}
	}
	if(sec>=0 && sec<=59)
	{
		votEndSEC=sec;
		i2c_eeprom_write(8, 0x50,sec);   		
   		CmdLCD(0x80);
   		StrLCD("VOT END SEC:- ");
   		U32LCD(i2c_eeprom_read(8,0x50));
   		delay_ms(500);
		CmdLCD(0x01);
	}
	else
	{
		sec=0;
		CmdLCD(0x01);
		CmdLCD(0x80);
		StrLCD("Invalid SECS");
		delay_ms(500);
		CmdLCD(0x01);
	}
	delay_ms(500);
	CmdLCD(0x01);
}