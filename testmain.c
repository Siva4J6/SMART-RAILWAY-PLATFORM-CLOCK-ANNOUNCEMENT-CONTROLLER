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
 extern TrainInfo TrainDB[TOTAL_TRAINS];
u8 CurrentTrain;

extern s32 hour,min,sec;
extern s32 date,month,year;
extern s32 day;
u8 status;

int main()
{

InitLCD();
Init_KPM();
RTC_Init();
EINT0_Init();
Alert_Init();
while(1)
{
if(AdminMode==1)
  {
  Admin_Menu();
  AdminMode=0;
  }
GetRTCTimeInfo(&hour,&min,&sec);
DisplayRTCTime(hour,min,sec);
GetRTCDateInfo(&date,&month,&year);
DisplayRTCDate(date,month,year);
GetRTCDay(&day);
DisplayRTCDay(day);
delay_ms(3000);
 CurrentTrain=FindCurrentTrain(hour,min);
  status=GetTrainStatus(CurrentTrain);
  if(CurrentTrain<TOTAL_TRAINS)
  {
  DisplayTrainInfo(CurrentTrain);
 
 }
 delay_ms(1000);
 TrainAlert(status);
  
  }
}










