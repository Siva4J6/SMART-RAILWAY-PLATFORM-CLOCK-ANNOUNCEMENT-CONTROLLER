#include<lpc21xx.h>
#include"types.h"
#include"lcd.h"
#include"kpm.h"
#include"train.h"
#include"admin.h"
#include"delay.h"
#include"lcd_defines.h"
#include"rtc1.h"
extern TrainInfo TrainDB[TOTAL_TRAINS];

void  UpdateTrain(void)
{
  u32 trainno;
  u32 arrhour;
  u32 arrmin;
  u32 dephour;
  u32 depmin;
  u32 platform;
  u32 delay;
  //select train
  while(1)
  {
  CmdLCD(CLEAR_LCD);
  StrLCD("TRAIN NO");
  CmdLCD(GOTO_LINE2_POS0);
  trainno=ReadNum();

  if(trainno<TOTAL_TRAINS)
  {
    break;
   }
    CmdLCD(CLEAR_LCD);
	StrLCD("INVALID TRAIN");
	delay_ms(1500);
  }
  //arrival hour
  while(1)
  {
  CmdLCD(CLEAR_LCD);
  StrLCD("ARRIVAL HH:");
  CmdLCD(GOTO_LINE2_POS0);
  arrhour=ReadNum();
  if(arrhour<=23)
  {
    break;
	}
    CmdLCD(CLEAR_LCD);
	StrLCD("INVALID HOUR");
	delay_ms(1000);
  }
  //arrival minutes
  while(1)
  {
   CmdLCD(CLEAR_LCD);
  StrLCD("ARRIVAL MM:");
  CmdLCD(GOTO_LINE2_POS0);
  arrmin=ReadNum();
  if(arrmin<=59)
  {
    break;
	}
    CmdLCD(CLEAR_LCD);
	StrLCD("INVALID MIN");
	delay_ms(1000);
  }
  //departure hour
  while(1)
  {
   CmdLCD(CLEAR_LCD);
  StrLCD("DEPART HH:");
  CmdLCD(GOTO_LINE2_POS0);
  dephour=ReadNum();
  if(dephour<=23)
  {
    break;
	}
    CmdLCD(CLEAR_LCD);
	StrLCD("INVALID HOUR");
	delay_ms(1000);
  }
  //departure minutes
  while(1)
  {
   CmdLCD(CLEAR_LCD);
  StrLCD("DEPART MM:");
  CmdLCD(GOTO_LINE2_POS0);
  depmin=ReadNum();
  if(depmin<=59)
  {
    break;
	}
    CmdLCD(CLEAR_LCD);
	StrLCD("INVALID MIN");
	delay_ms(1000);
  }
  //platform
  while(1)
  {
  CmdLCD(CLEAR_LCD);
  StrLCD("PLATFORM");
  CmdLCD(GOTO_LINE2_POS0);
  platform=ReadNum();
  if(platform<=9)
  {
  break;
  }
    CmdLCD(CLEAR_LCD);
	StrLCD("INVALID PLATFORM");
	delay_ms(1000);
  }
  //delay
  while(1)
  {
  CmdLCD(CLEAR_LCD);
  StrLCD("DELAY");
  CmdLCD(GOTO_LINE2_POS0);
  delay=ReadNum();
  if(delay<=99)
  {
  break;
  }
    CmdLCD(CLEAR_LCD);
	StrLCD("INVALID DELAY");
	delay_ms(1000);
	}
	TrainDB[trainno].UpdArrHour=arrhour;
	TrainDB[trainno].UpdArrMin=arrmin;
	TrainDB[trainno].UpdDepHour=dephour;
	TrainDB[trainno].UpdDepMin=depmin;
	TrainDB[trainno].Platform=platform;
	TrainDB[trainno].Delay=delay;
	 
	 CmdLCD(CLEAR_LCD);
	 StrLCD("TRAIN UPDATED");
	 CmdLCD(CLEAR_LCD);
	 delay_ms(1000);
	 }
	 void UpdateRTCTime(void)
	 {
	  s32 temp;
	  while(1)
	  {
	  	 CmdLCD(CLEAR_LCD);
	 StrLCD("SET HOUR:");
	 CmdLCD(GOTO_LINE2_POS0);
	 temp=ReadNum();
	 if(temp<=23)
	 {
	 hour=temp;
	 break;
	 }
	 CmdLCD(CLEAR_LCD);
	 StrLCD("INVALID HOUR");
	 delay_ms(1000);
	 }
	   while(1)
	  {
	  	 CmdLCD(CLEAR_LCD);
	 StrLCD("SET MIN:");
	 CmdLCD(GOTO_LINE2_POS0);
	 temp=ReadNum();
	 if(temp<=59)
	 {
	min=temp;
	 break;
	 }
	 CmdLCD(CLEAR_LCD);
	 StrLCD("INVALID MIN");
	 delay_ms(1000);
	 }
	  while(1)
	  {
	  	 CmdLCD(CLEAR_LCD);
	 StrLCD("SET SEC:");
	 CmdLCD(GOTO_LINE2_POS0);
	 temp=ReadNum();
	 if(temp<=59)
	 {
	sec=temp;
	 break;
	 }
	 CmdLCD(CLEAR_LCD);
	 StrLCD("INVALID SEC");
	 delay_ms(1000);
	 }
	 SetRTCTimeInfo(hour,min,sec);
	  while(1)
	  {
	  	 CmdLCD(CLEAR_LCD);
	 StrLCD("SET DATE:");
	 CmdLCD(GOTO_LINE2_POS0);
	 temp=ReadNum();
	 if(temp>=1&&temp<=31)
	 {
	date=temp;
	 break;
	 }
	 CmdLCD(CLEAR_LCD);
	 StrLCD("INVALID DATE");
	 delay_ms(1000);
	 }
	  while(1)
	  {
	  	 CmdLCD(CLEAR_LCD);
	 StrLCD("SET MONTH:");
	 CmdLCD(GOTO_LINE2_POS0);
	 temp=ReadNum();
	 if(temp>=1&&temp<=12)
	 {
	month=temp;
	 break;
	 }
	 CmdLCD(CLEAR_LCD);
	 StrLCD("INVALID MONTH");
	 delay_ms(1000);
	 }
	  while(1)
	  {
	  	 CmdLCD(CLEAR_LCD);
	 StrLCD("SET YEAR:");
	 CmdLCD(GOTO_LINE2_POS0);
	 temp=ReadNum();
	 if(temp>=2000&&temp<=2099)
	 {
	year=temp;
	 break;
	 }
	 CmdLCD(CLEAR_LCD);
	 StrLCD("INVALID YEAR");
	 delay_ms(1000);
	 }
	 SetRTCDateInfo(date,month,year);
	  while(1)
	  {
	  	 CmdLCD(CLEAR_LCD);
	 StrLCD("SET DAY:");
	 CmdLCD(GOTO_LINE2_POS0);
	 temp=ReadNum();
	 if(temp>=0&&temp<=7)
	 {
	day=temp;
	 break;
	 }
	 CmdLCD(CLEAR_LCD);
	 StrLCD("INVALID DAY");
	 delay_ms(1000);
	 }
	 SetRTCDay(day);
	 }
	 //admin mode
	 void Admin_Menu(void)
	 {
	   u8 key;
	   CmdLCD(CLEAR_LCD);
	   StrLCD("ADMIN MODE");
	   CmdLCD(GOTO_LINE2_POS0);
	   StrLCD("1 UP 0 EX 2 RTC");
	   while(1)
	   {
	    key=keyscan();
		if(key=='1')
		{
		UpdateTrain();

		return;
		}
		if(key=='2')
		{
		UpdateRTCTime();
		return;
		}
		
		if(key=='0')
		{
		  CmdLCD(CLEAR_LCD);
		  StrLCD("EXIT ADMIN");
		  delay_ms(1000);
		  return;
		  }
		  }
		  }
		  


