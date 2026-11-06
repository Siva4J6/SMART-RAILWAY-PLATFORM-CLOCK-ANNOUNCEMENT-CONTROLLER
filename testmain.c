/*
 * testmain.c
 *
 * Main program of the railway train information system (LPC21xx).
 *
 * Operation:
 *  - Shows the RTC time, date and day on the LCD.
 *  - Finds the next train to depart, shows its details on the LCD and
 *    indicates its status with LEDs/buzzer.
 *  - If the admin switch (EINT0) is pressed, enters admin mode to update
 *    train details or the RTC.
 */
#include <LPC21xx.H>
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"rtc.h"
#include"train.h"
#include"display.h"
#include"compare.h"
#include"delay.h"
#include"kpm.h"
#include"admin.h"
#include"interrupt.h"
#include"alert.h"

 extern TrainInfo TrainDB[TOTAL_TRAINS];    // Train database (train.c)
u8 CurrentTrain;                            // Index of the train being shown

// Current time/date variables (defined in rtc.c)
extern s32 hour,min,sec;
extern s32 date,month,year;
extern s32 day;
u8 status;                                  // Status code of CurrentTrain

int main()
{

// ---- Initialise all peripherals ----
InitLCD();          // 16x2 LCD
Init_KPM();         // Keypad
RTC_Init();         // Real time clock (default time/date loaded)
EINT0_Init();       // External interrupt for admin switch
Alert_Init();       // LEDs and buzzer (all off)

// ---- Main loop ----
while(1)
{
// Admin switch pressed (flag set by EINT0 ISR)?
if(AdminMode==1)
  {
  Admin_Menu();         // Run admin menu
  AdminMode=0;          // Clear the flag
  }

// Read RTC and show time (line 1), date (line 2) and day of week
GetRTCTimeInfo(&hour,&min,&sec);
DisplayRTCTime(hour,min,sec);
GetRTCDateInfo(&date,&month,&year);
DisplayRTCDate(date,month,year);
GetRTCDay(&day);
DisplayRTCDay(day);
delay_ms(3000);         // Keep the clock screen for 3 seconds

 // Select the next train to depart and work out its status
 CurrentTrain=FindCurrentTrain(hour,min);
  status=GetTrainStatus(CurrentTrain);

  // Show the train details if the index is valid
  if(CurrentTrain<TOTAL_TRAINS)
  {
  DisplayTrainInfo(CurrentTrain);
 
 }
 delay_ms(1000);

 // Indicate status with LED/buzzer
 TrainAlert(status);
  
  }
}
