/*
 * admin.c
 *
 * Admin-mode module for the LPC21xx based railway/train information system.
 *
 * Features:
 *   1. UpdateTrain()   - Admin enters new arrival/departure time, platform
 *                        and delay for a selected train (stored in TrainDB).
 *   2. UpdateRTCTime() - Admin sets the RTC time (HH:MM:SS), date
 *                        (DD/MM/YYYY) and day of week.
 *   3. Admin_Menu()    - Menu shown on LCD; keypad selects which action
 *                        to perform.
 *
 * Hardware used: 16x2 LCD, 4x4 matrix keypad, on-chip RTC.
 */

#include <LPC21xx.H>        // LPC21xx microcontroller register definitions
#include"types.h"           // Custom data types (u8, u32, s32, ...)
#include"lcd.h"             // LCD driver: CmdLCD(), StrLCD(), ...
#include"kpm.h"             // Keypad module: keyscan(), ReadNum()
#include"admin.h"           // Admin function prototypes
#include"delay.h"           // delay_ms()
#include"lcd_defines.h"     // LCD command macros (CLEAR_LCD, GOTO_LINE2_POS0, ...)
#include"train.h"           // TrainInfo structure, TOTAL_TRAINS
#include"rtc.h"             // RTC globals (hour, min, sec, date, ...) and setters

// Train database defined elsewhere (train.c); shared with this module
extern TrainInfo TrainDB[TOTAL_TRAINS];

/*
 * UpdateTrain
 * -----------
 * Asks the admin (via keypad + LCD) for the new schedule details of a train.
 * Each input is validated in its own loop: the prompt repeats until a valid
 * value is entered. Values are written to TrainDB only after ALL inputs are
 * valid, so a partially entered update never corrupts the database.
 */
void UpdateTrain(void)
{
	u32 trainno;    // Index of the train to update
	u32 arrhour;    // Updated arrival hour   (0-23)
	u32 arrmin;     // Updated arrival minute (0-59)
	u32 dephour;    // Updated departure hour   (0-23)
	u32 depmin;     // Updated departure minute (0-59)
	u32 platform;   // Platform number (0-9)
	u32 delay;      // Delay in minutes (0-99)

	// ---- Train number ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("TRAIN NO");
		CmdLCD(GOTO_LINE2_POS0);
		trainno=ReadNum();          // Read number typed on keypad

		if(trainno<TOTAL_TRAINS)    // Valid index into TrainDB
		{
			break;
		}
		// Invalid train number: show error and ask again
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID TRAIN");
		delay_ms(1000);
	}

	// ---- Arrival hour ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("ARRIVAL HH:");
		CmdLCD(GOTO_LINE2_POS0);
		arrhour=ReadNum();

		if(arrhour<=23)             // Hour must be 0-23
		{
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID HOUR");
		delay_ms(1000);
	}

	// ---- Arrival minute ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("ARRIVAL_MM:");
		CmdLCD(GOTO_LINE2_POS0);
		arrmin=ReadNum();

		if(arrmin<=59)              // Minute must be 0-59
		{
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID MIN");
		delay_ms(1000);
	}

	// ---- Departure hour ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("DAPART HH:");
		CmdLCD(GOTO_LINE2_POS0);
		dephour=ReadNum();

		if(dephour<=23)             // Hour must be 0-23
		{
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID HOUR");
		delay_ms(1000);
	}

	// ---- Departure minute ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("DEPART MM:");
		CmdLCD(GOTO_LINE2_POS0);
		depmin=ReadNum();

		if(depmin<=59)              // Minute must be 0-59
		{
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID MIN");
		delay_ms(1000);
	}

	// ---- Platform ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("PLATFORM");
		CmdLCD(GOTO_LINE2_POS0);
		platform=ReadNum();

		if(platform<=9)             // Single-digit platform number
		{
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID PLATFORM");
		delay_ms(1000);
	}

	// ---- Delay ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("DELAY");
		CmdLCD(GOTO_LINE2_POS0);
		delay=ReadNum();

		if(delay<=99)               // Delay limited to 2 digits
		{
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID DELAY");
		delay_ms(1000);
	}

	// ---- All inputs valid: commit to the train database ----
	TrainDB[trainno].UpdArrHour=arrhour;   // Updated arrival time
	TrainDB[trainno].UpdArrMin=arrmin;
	TrainDB[trainno].UpdDepHour=dephour;   // Updated departure time
	TrainDB[trainno].UpdDepMin=depmin;
	TrainDB[trainno].Platform=platform;    // Platform number
	TrainDB[trainno].Delay=delay;          // Delay in minutes

	// Confirmation message
	CmdLCD(CLEAR_LCD);
	StrLCD("TRAIN UPDATED");
	CmdLCD(CLEAR_LCD);
	delay_ms(1000);
}

/*
 * UpdateRTCTime
 * -------------
 * Lets the admin set the RTC: time (hour, minute, second), date
 * (date, month, year) and day of week. Every field is validated; the
 * prompt repeats until a valid value is entered. The RTC is programmed
 * after the time group, the date group and the day are each complete.
 * hour, min, sec, date, month, year, day are RTC globals declared in rtc.h.
 */
void UpdateRTCTime(void)
{
	s32 temp;   // Temporary holder for the value typed on the keypad

	// ---- Hour ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("SET HOUR:");
		CmdLCD(GOTO_LINE2_POS0);
		temp=ReadNum();

		if(temp<=23)                // Valid: 0-23
		{
			hour=temp;
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID HOUR");
		delay_ms(1000);
	}

	// ---- Minutes ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("SET MINUTES:");
		CmdLCD(GOTO_LINE2_POS0);
		temp=ReadNum();

		if(temp<=59)                // Valid: 0-59
		{
			min=temp;
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID MINUTES");
		delay_ms(1000);
	}

	// ---- Seconds ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("SET SECONDS:");
		CmdLCD(GOTO_LINE2_POS0);
		temp=ReadNum();

		if(temp<=59)                // Valid: 0-59
		{
			sec=temp;
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID SEC");
		delay_ms(1000);
	}

	// Write the new time into the RTC registers
	SetRTCTimeInfo(hour,min,sec);

	// ---- Date (day of month) ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("SET DATE:");
		CmdLCD(GOTO_LINE2_POS0);
		temp=ReadNum();

		if(temp>=1&&temp<=31)       // Valid: 1-31
		{
			date=temp;
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID DATE");
		delay_ms(1000);
	}

	// ---- Month ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("SET MONTH:");
		CmdLCD(GOTO_LINE2_POS0);
		temp=ReadNum();

		if(temp>=1&&temp<=12)       // Valid: 1-12
		{
			month=temp;
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID MONTH");
		delay_ms(1000);
	}

	// ---- Year ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("SET YEAR:");
		CmdLCD(GOTO_LINE2_POS0);
		temp=ReadNum();

		if(temp>=2000&&temp<=2099)  // Valid: 2000-2099
		{
			year=temp;
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID YEAR");
		delay_ms(1000);
	}

	// Write the new date into the RTC registers
	SetRTCDateInfo(date,month,year);

	// ---- Day of week ----
	while(1)
	{
		CmdLCD(CLEAR_LCD);
		StrLCD("SET DAY:");
		CmdLCD(GOTO_LINE2_POS0);
		temp=ReadNum();

		if(temp>0&&temp<=7)         // Valid: 1-7 (day of week)
		{
			day=temp;
			break;
		}
		CmdLCD(CLEAR_LCD);
		StrLCD("INVALID DAY");
		delay_ms(1000);
	}

	// Write the day of week into the RTC register
	SetRTCDay(day);
}

/*
 * Admin_Menu
 * ----------
 * Entry point for admin mode. Shows the menu on the LCD and waits for a key:
 *   '1' -> update train details
 *   '2' -> set RTC date/time
 *   '0' -> exit admin mode
 * Any other key is ignored. The function returns after one action.
 */
void Admin_Menu(void)
{
	u8 key;     // Key pressed on the keypad

	// Display the menu
	CmdLCD(CLEAR_LCD);
	StrLCD("ADMIN MODE");
	CmdLCD(GOTO_LINE2_POS0);
	StrLCD("1 UP 0 EX 2 RTC");

	// Wait until a valid menu key is pressed
	while(1)
	{
		key=keyscan();              // Blocking read of one keypad key

		if(key=='1')                // Update train info
		{
			UpdateTrain();
			return;
		}
		if(key=='2')                // Set RTC time/date/day
		{
			UpdateRTCTime();
			return;
		}
		if(key=='0')                // Exit admin mode
		{
			CmdLCD(CLEAR_LCD);
			StrLCD("EXIT ADMIN");
			delay_ms(1000);
			return;
		}
	}
}
