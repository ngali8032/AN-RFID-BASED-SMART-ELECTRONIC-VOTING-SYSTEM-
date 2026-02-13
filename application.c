#include "header.h"
#include <lpc21xx.h>
extern int votStartHR, votStartMIN, VotStartSEC, VotEndHR, votEndMIN, votEndSEC;
extern int votingStarted;
extern int einto_interrupt;
void checking_point(void)
{
	while(1){
		if(HOUR>=votStartHR && HOUR<=VotEndHR)
		{
			if(votingStarted)
			{
				user_card_checking();
			}
			else
			{
				CmdLCD(0x80);
				StrLCD("Start the voting");
				CmdLCD(0xc0);
				StrLCD("process");
			}
		}
		else
		{
			CmdLCD(0x80);
			StrLCD("Enter Starting and");
			CmdLCD(0xc0);
			StrLCD("Ending Hours");
		}
		if(einto_interrupt)
		{
			CmdLCD(0x01);
			officer_card_checking();
			einto_interrupt=0;
		} 
	}

}