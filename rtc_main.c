#include <lpc214x.h>
#include "rtc.h"
s32 hour=12,min=14,sec=0,date=11,month=2,year=2026,day=4;
// Main function
void system_Init()
{
  // Set the initial time (hours, minutes, seconds)
	SetRTCTimeInfo(hour,min, sec);
	SetRTCDateInfo(date,month,year);
	SetRTCDay(day);
}

 
void display_RTC(){
    // Get and display the current time on LCD
		GetRTCTimeInfo(&hour,&min,&sec);
		DisplayRTCTime(hour,min,sec);
		GetRTCDateInfo(&date,&month,&year);
		DisplayRTCDate(date,month,year);
		GetRTCDay(&day);
		DisplayRTCDay(day);
}


