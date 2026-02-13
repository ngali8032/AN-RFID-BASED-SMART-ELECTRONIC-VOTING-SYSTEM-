#ifndef header_h

#define header_h

#include <lpc21xx.h>

#include "lcd.h"

#include "kpm.h"

#include "delay.h"

#include "uart0.h"

#include "switch.h"

#include "types.h"

#include "rtc.h"

#include <string.h>

void Init_time(void);

void system_Init(void);

void Init_system(void);

void display_RTC(void);

void Init_i2c(void);

void i2c_eeprom_write(short int, unsigned char,char);

void i2c_eeprom_pagewrite(short int, unsigned char,char*, int);

void i2c_eeprom_pageread(short int, unsigned char, char*, int);

unsigned char i2c_eeprom_read(short int,char);

void officer_card_checking(void);

void StrLCD(s8 *);

void officer_menu(void);

u32 KeyScan(void);

void setStartEndVoting(void);

void startVoting(void);

void stopVoting(void);

void viewResults(void);

void resetVoting(void);


void Edit_RTC_Info(void);  /*declaration for Edit RTC info*/

void Edit_HOUR(void);  /*declaration for Edit HOUR*/ 

void Edit_MIN(void);   /*declaration for Edit minute*/

void Edit_SEC(void);  /*declaration for Edit second*/

void Edit_DAY(void);  /*declaration for Edit day*/

void Edit_DATE(void); /*declaration for Edit date*/

void Edit_MONTH(void); /*declaration for Edit month*/

void Edit_YEAR(void);  /*declaration for Edit year*/

void SetRTCTimeInfo(u32,u32,u32); 

void SetRTCDay(u32);

void SetRTCDateInfo(u32, u32, u32);


void EditStartTime(void);

void EditEndTime(void);


void EditStartHR(void);

void  EditStartMIN(void);

void EditStartSEC(void);


void EditEndHR(void);

void  EditEndMIN(void);

void EditEndSEC(void);


void startVoting(void);

void checking_point(void);

void user_voting(void);

void user_card_checking(void);
void viewResults(void);
void CHANGE_PASSWORD(int);

#endif
