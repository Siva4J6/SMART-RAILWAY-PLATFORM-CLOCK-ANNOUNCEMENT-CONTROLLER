/*
 * rtc.h
 * Interface for the on-chip Real Time Clock (RTC) module.
 */
#ifndef __RTC_H__
#define __RTC_H__
#include"types.h"

// Global copies of the current time/date (defined in rtc.c)
extern s32 hour;
extern s32 min;
extern s32 sec;
extern s32 date;
extern s32 month;
extern s32 year;
extern s32 day;             // Day of week

void RTC_Init(void);        // Enable RTC and load default date/time

// Time
 void SetRTCTimeInfo(u32 hour, u32 minute, u32 second);
 void GetRTCTimeInfo(s32 *hour, s32 *minute, s32 *second);

// Date
void  SetRTCDateInfo(u32 date, u32 month, u32 year);
void GetRTCDateInfo(s32 *date, s32 *month, s32 *year);

// LCD display helpers
void DisplayRTCTime(u32 hour, u32 minute, u32 second);
void DisplayRTCDate(u32 date, u32 month, u32 year);
void DisplayRTCDay(u32 day);

// Day of week
void GetRTCDay(s32 *dow);
void SetRTCDay(u32 dow);

#endif
