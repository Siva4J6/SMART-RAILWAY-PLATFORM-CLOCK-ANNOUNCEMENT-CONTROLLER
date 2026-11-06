/*
 * rtc.c
 * Driver for the LPC21xx on-chip Real Time Clock: initialisation,
 * setting/getting time, date and day of week, and showing them on the LCD.
 */
#include <lpc21xx.h>					
#include "lcd.h"
#include "lcd_defines.h"
#include"rtc.h"


#define FOSC 12000000       // Crystal frequency (12 MHz)
#define CCLK (5*FOSC)       // CPU clock (60 MHz, PLL x5)
#define PCLK (CCLK/4)       zzzzz // Peripheral clock (15 MHz) - NOTE: stray 'zzzzz' kept from original; remove it

// Prescaler values (only needed when the RTC runs from PCLK, e.g. LPC2129)
#define PREINT_VAL  ((int)(PCLK/32768)-1)
#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768)-1)

// CCR (clock control register) bits
#define RTC_ENABLE (1<<0)   // Enable clock
#define RTC_RESET (1<<1)    // Reset clock tick counter
#define RTC_CLKSRC (1<<4)   // Use external 32.768 kHz oscillator (LPC2148)

// Global time/date variables shared with other modules
s32 hour,min,sec;
s32 date,month,year;
s32 day;                    // Day of week (0=SUN ... 6=SAT)

// Day names indexed by day of week
char week[][4]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
#define SUN 0
#define MON 1
#define	TUE 2
#define	WED 3
#define	THU 4
#define	FRI 5
#define	SAT 6

#define CPU_LPC2148         // Target MCU is LPC2148 (has dedicated RTC clock source)

/*
 * RTC_Init
 * Resets and enables the RTC, then loads a default time/date:
 * 18:26:00, 21/09/2026, Wednesday.
 */
void RTC_Init(void) 

{
	CCR = RTC_RESET;            // Reset the clock

  #ifndef CPU_LPC2148
    // LPC2129 etc.: derive 32.768 kHz from PCLK using the prescaler
    PREINT = PREINT_VAL;

	PREFRAC = PREFRAC_VAL;

	CCR = RTC_ENABLE;  

	#else
	// LPC2148: use the external 32.768 kHz crystal as clock source
	CCR = RTC_ENABLE | RTC_CLKSRC; 
	
	#endif
 
	 SetRTCTimeInfo(18,26,0);       // Default time
	  SetRTCDateInfo(21,9,2026);    // Default date
	   SetRTCDay(WED);              // Default day of week
}

// Reads current time from RTC registers
void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second)

{
	*hour = HOUR;
	*minute = MIN;
	*second = SEC;
}

// Shows time as HH:MM:SS on line 1 of the LCD
void DisplayRTCTime(u32 hour, u32 minute, u32 second)

{
	CmdLCD(GOTO_LINE1_POS0);

	CharLCD(hour/10+48);        // +48 converts digit to ASCII
	CharLCD(hour%10+48);
	CharLCD(':');

	CharLCD(minute/10+48);
	CharLCD(minute%10+48);

	CharLCD(':');

	CharLCD(second/10+48);
	CharLCD(second%10+48);
}


// Reads current date from RTC registers
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year)

{
	*date = DOM;
	*month = MONTH;
	*year = YEAR;
}

// Shows date as DD/MM/YYYY on line 2 of the LCD
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

// Writes a new time into the RTC registers
void SetRTCTimeInfo(u32 hour, u32 minute, u32 second)

{
	HOUR = hour;
	MIN = minute;
	SEC = second;
}

// Writes a new date into the RTC registers
void SetRTCDateInfo(u32 date, u32 month, u32 year)

{
	DOM = date;
	MONTH = month;
	YEAR = year;
}

// Reads the day of week from the RTC
void GetRTCDay(s32 *dow)

{
	*dow = DOW; 
}

// Shows the 3-letter day name (SUN..SAT) on line 1, column 10
void DisplayRTCDay(u32 day)

{
	CmdLCD(GOTO_LINE1_POS0 + 10);
	StrLCD(week[day]);  
}

// Writes the day of week (0-6) into the RTC
void SetRTCDay(u32 dow)

{
	DOW = dow;
}
