#include <LPC21xx.H>
#include"types.h"
#include"lcd.h"
#include"lcd_defines.h"
#include"train.h"
#include"delay.h"
extern TrainInfo TrainDB[TOTAL_TRAINS];


/*void DisplayTrainNo(u8 index)
{
CmdLCD(CLEAR_LCD);
StrLCD("Train No");
CmdLCD(GOTO_LINE2_POS0);
U32LCD(TrainDB[index].TrainNo);
delay_ms(1000);
} */
void DisplayTrainName(u8 index)
{
s32 pos;
   CmdLCD(CLEAR_LCD);
StrLCD("TRN:");
U32LCD(TrainDB[index].TrainNo);
StrLCD(" P:");
U32LCD(TrainDB[index].Platform);

CmdLCD(GOTO_LINE2_POS0);
for(pos=0;pos<17;pos++)
{
CmdLCD(GOTO_LINE2_POS0);
StrLCD("                ");
CmdLCD(GOTO_LINE2_POS0+pos);


StrLCD(TrainDB[index].TrainName);
delay_ms(300);
}
for(pos=15;pos>=0;pos--)
{
CmdLCD(GOTO_LINE2_POS0);
StrLCD("                ");
CmdLCD(GOTO_LINE2_POS0+pos);

StrLCD(TrainDB[index].TrainName);
delay_ms(300);
}
}
  

void DisplayDestination(u8 index)
{
CmdLCD(CLEAR_LCD);
StrLCD("DES:");
//CmdLCD(GOTO_LINE2_POS0);
StrLCD(TrainDB[index].Destination);
delay_ms(1000);
}


void DisplayArrival(u8 index)
{
//CmdLCD(CLEAR_LCD);
//StrLCD("Arrival");
CmdLCD(GOTO_LINE2_POS0);

StrLCD("A:");

CharLCD((TrainDB[index].UpdArrHour/10)+48);
CharLCD((TrainDB[index].UpdArrHour%10)+48);
CharLCD(':');
CharLCD((TrainDB[index].UpdArrMin/10)+48);
CharLCD((TrainDB[index].UpdArrMin%10)+48);
delay_ms(200);
}


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
void DisplayTrainInfo(u8 index)
{
//DisplayTrainNo(index);
 DisplayTrainName(index);
DisplayDestination(index);
DisplayArrival(index);
DisplayDeparture(index);
//DisplayPlatform(index);
DisplayDelay(index);
}
































