#include "header.h"

int main()
{
	int i;
	char des[10];
	Init_i2c();
	Init_LCD();	
	for(i=0; i<2500; i+=8){
		CmdLCD(0x80);
		i2c_eeprom_pagewrite(i, 0x50,"Narendra", strlen("Narendra"));
		delay_ms(10);
		i2c_eeprom_pageread(i, 0x50,des, 8);
		des[8]='\0';
		StrLCD(des);
		delay_s(2);
	}
}