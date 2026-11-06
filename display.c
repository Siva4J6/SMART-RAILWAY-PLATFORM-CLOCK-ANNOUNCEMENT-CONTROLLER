/*
 * display.c
 * Routines to display train details (name, destination, arrival,
 * departure, platform, delay) from TrainDB on the LCD.
 */
#include <LPC21xx.H>
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"train.h"
#include"delay.h"
extern TrainInfo TrainDB[TOTAL_TRAINS];     // Train database (train.c)


/*void DisplayTrainNo(u8 index)
{
CmdLCD(CLEAR_LCD);
StrLCD("Train No");
CmdLCD(GOTO_LINE2_POS0);
U32LCD(TrainDB[index].TrainNo);
delay_ms(1000);
} */

/*
 * DisplayTrainName
 * Line 1 shows "TRN:<no> P:<platform>". Line 2 shows the train name
 * scrolling from left to right and back (marquee effect).
 */
void DisplayTrainName(u8 index)
{
s32 pos;
   CmdLCD(CLEAR_LCD);
StrLCD("TRN:");
U32LCD(TrainDB[index].TrainNo);
StrLCD(" P:");
U32LCD(TrainDB[index].Platform);

CmdLCD(GOTO_LINE2_POS0);
// Scroll name to the right
for(pos=0;pos<17;pos++)
{
CmdLCD(GOTO_LINE2_POS0);
StrLCD("                ");            // Erase line 2
CmdLCD(GOTO_LINE2_POS0+pos);          // Move to new start position


StrLCD(TrainDB[index].TrainName);
delay_ms(300);
}
// Scroll name back to the left
for(pos=15;pos>=0;pos--)
{
CmdLCD(GOTO_LINE2_POS0);
StrLCD("                ");
CmdLCD(GOTO_LINE2_POS0+pos);

StrLCD(TrainDB[index].TrainName);
delay_ms(300);
}
}
  

// Shows "DES:<destination>" for 1 second
void DisplayDestination(u8 index)
{
CmdLCD(CLEAR_LCD);
StrLCD("DES:");
//CmdLCD(GOTO_LINE2_POS0);
StrLCD(TrainDB[index].Destination);
delay_ms(1000);
}


// Shows updated arrival time as "A:HH:MM" on line 2
void DisplayArrival(u8 index)
{
//CmdLCD(CLEAR_LCD);
//StrLCD("Arrival");
CmdLCD(GOTO_LINE2_POS0);

StrLCD("A:");

// Split into digits and convert to ASCII (+48 = '0')
CharLCD((TrainDB[index].UpdArrHour/10)+48);
CharLCD((TrainDB[index].UpdArrHour%10)+48);
CharLCD(':');
CharLCD((TrainDB[index].UpdArrMin/10)+48);
CharLCD((TrainDB[index].UpdArrMin%10)+48);
delay_ms(200);
}


// Appends updated departure time as " D:HH:MM" after the arrival time
void DisplayDeparture(u8 index)
{
//CmdLCD(CLEAR_LCD);
//StrLCD("Departure");
//CmdLCD(GOTO_LINE2_POS0);
StrLCD(" D:");
CharLCD((TrainDB[index].UpdDepHour/10)+48);
CharLCD((TrainDB[index].UpdDepHour%10)+48);
CharLCD(':');
CharLCD((TrainDB[index].UpdDepMin/10)+48);
CharLCD((TrainDB[index].UpdDepMin%10)+48);
delay_ms(1000);
}
/*void DisplayPlatform(u8 index)
{
CmdLCD(CLEAR_LCD);
StrLCD("Platform");
CmdLCD(GOTO_LINE2_POS0);
U32LCD(TrainDB[index].Platform);
delay_ms(1000);
}	*/

// Shows "DELAY:<n>Min" for 1 second, then clears the LCD
void DisplayDelay(u8 index)
{
CmdLCD(CLEAR_LCD);
StrLCD("DELAY:");
//CmdLCD(GOTO_LINE2_POS0);
U32LCD(TrainDB[index].Delay);
StrLCD("Min");
delay_ms(1000);
CmdLCD(CLEAR_LCD);
}

// Shows all train details one after another
void DisplayTrainInfo(u8 index)
{
//DisplayTrainNo(index);
 DisplayTrainName(index);       // Train no, platform, scrolling name
DisplayDestination(index);      // Destination
DisplayArrival(index);          // Arrival time
DisplayDeparture(index);        // Departure time
//DisplayPlatform(index);
DisplayDelay(index);            // Delay in minutes
}
