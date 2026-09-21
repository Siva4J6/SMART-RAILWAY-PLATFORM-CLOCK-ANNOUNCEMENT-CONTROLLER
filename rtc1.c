#include<lpc21xx.h>
#include"lcd.h"
#include"lcd_defines.h"
#include"rtc1.h"

#define FOSC 12000000
#define CCLK (5*FOSC)
#define PCLK (CCLK/4)

#define PREINT_VAL ((int)(PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

#define RTC_ENABLE (1<<0)
#define RTC_RESET (1<<1)
#define RTC_CLKSRC (1<<4)

s32 hour,min,sec;
s32 date,month,year;
s32 day;

char week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
#define SUN 0
#define MON 1
#define TUE 2
#define WED 3
#define THU 4
#define FRI 5
#define SAT 6

#define CPU_LPC2148

void RTC_Init(void) 

{

  // Disable and reset the RTC

	CCR = RTC_RESET;

  #ifndef CPU_LPC2148

  // Set prescaler integer and fractional parts

	PREINT = PREINT_VAL;

	PREFRAC = PREFRAC_VAL;

  

  // Enable the RTC

	CCR = RTC_ENABLE;  

	#else

	// Enable the RTC with external clock source

	CCR = RTC_ENABLE | RTC_CLKSRC;  

	#endif
	SetRTCTimeInfo(19,2,0);
	 SetRTCDateInfo(11,8,2026);
	 SetRTCDay(TUE);


}
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)

{

	*hour = HOUR;

	*minute = MIN;

	*second = SEC;

}

void DisplayRTCTime(u32 hour, u32 minute, u32 second)

{

	CmdLCD(GOTO_LINE1_POS0);

	CharLCD(hour/10+48);

	CharLCD(hour%10+48);

	CharLCD(':');

	CharLCD(minute/10+48);

	CharLCD(minute%10+48);

	CharLCD(':');

	CharLCD(second/10+48);

	CharLCD(second%10+48);

}

void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)

{

	*date = DOM;

	*month = MONTH;

	*year = YEAR;

}

void DisplayRTCDate(u32 date, u32 month, u32 year)

{

	CmdLCD(GOTO_LINE2_POS0);

	CharLCD(date/10+48);

	CharLCD(date%10+48);

	CharLCD('/');

	CharLCD(month/10+48);

	CharLCD(month%10+48);

	CharLCD('/');

	U32LCD(year);

}
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{

	HOUR = hour;

	MIN = minute;

	SEC = second;

}

void SetRTCDateInfo(u32 date, u32 month, u32 year)

{

	DOM = date;

	MONTH = month;

	YEAR = year;

}

void GetRTCDay(s32 *dow)

{

	*dow = DOW; 

}


/*

Display the current day of the week on LCD

dow (Day of Week) (0=Sunday, ..., 6=Saturday)

*/

void DisplayRTCDay(u32 day)

{

	CmdLCD(GOTO_LINE1_POS0 + 10);

	StrLCD(week[day]);  

}
void SetRTCDay(u32 dow)

{

	DOW = dow;

}

