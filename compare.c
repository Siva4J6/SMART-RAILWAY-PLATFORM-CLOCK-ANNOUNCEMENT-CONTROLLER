/*
 * compare.c
 *
 * Logic that decides which train is "current" (next to depart) and what
 * its status is, by comparing the schedule in TrainDB with the RTC time.
 */
#include<lpc21xx.h>
#include"types.h"
#include"rtc.h"
#include"train.h"
#include"compare.h"

 extern TrainInfo TrainDB[TOTAL_TRAINS];    // Train database (train.c)
 extern s32 hour;                           // Current RTC hour   (rtc.c)
 extern s32 min;                            // Current RTC minute (rtc.c)

 /*
  * FindCurrentTrain
  * Returns the index of the train whose departure time is the earliest one
  * that is still >= the given time. If every train has already departed
  * today, it wraps around and returns the train with the earliest
  * departure time overall (i.e. the first train of the next day).
  */
 u8 FindCurrentTrain(s32 hour,s32 min)
 {
 u8 i;
 u8 found=0;        // 1 once a candidate train has been found
 u8 index=0;        // Index of best candidate so far

 // Pass 1: look for the earliest departure that is not yet over
 for(i=0;i<TOTAL_TRAINS;i++)
 {
 // Does this train depart at/after the current time?
 if((TrainDB[i].UpdDepHour>hour)||((TrainDB[i].UpdDepHour==hour)&&(TrainDB[i].UpdDepMin>=min)))
 {
 if(found==0)
 {
 // First candidate
 index=i;
 found=1;
 }
 else
 {
 // Keep the one that departs earlier
 if((TrainDB[i].UpdDepHour<TrainDB[index].UpdDepHour)||((TrainDB[i].UpdDepHour==TrainDB[index].UpdDepHour)&&(TrainDB[i].UpdDepMin<TrainDB[index].UpdDepMin)))
 {
 index=i;
 }
 }
 }
 }
 if(found)
 {
 return index;
 }

 // Pass 2: all trains already departed -> pick the earliest departure of the day
 index=0;
  for(i=1;i<TOTAL_TRAINS;i++)
 {
 if((TrainDB[i].UpdDepHour<TrainDB[index].UpdDepHour)||((TrainDB[i].UpdDepHour==TrainDB[index].UpdDepHour)&&(TrainDB[i].UpdDepMin<TrainDB[index].UpdDepMin)))
 {
 index=i;
 }
 }
 return index;
 }

 /*
  * GetTrainStatus
  * Compares the current time (global hour/min) with the arrival and
  * departure times of the given train. All times are converted to
  * "minutes since midnight" to make comparison easy.
  */
 u8 GetTrainStatus(u8 index)
 {
 s32 currentTime;   // Current time in minutes
 s32 arrTime;       // Arrival time in minutes
 s32 depTime;       // Departure time in minutes

 currentTime=(hour*60)+min;

 arrTime=((TrainDB[index].UpdArrHour*60)+TrainDB[index].UpdArrMin);

 depTime=((TrainDB[index].UpdDepHour*60)+TrainDB[index].UpdDepMin);

 // A train with a delay is always reported as delayed
 if(TrainDB[index].Delay>0)
 {
 return TRAIN_DELAYED;
 }
 // Not arrived yet
 if(currentTime<arrTime)
  {
  return TRAIN_APPROACHING;
  }
 // Between arrival and departure
  if((currentTime>=arrTime)&&(currentTime<=depTime))
  {
  return TRAIN_ONTIME;
  }
 // Past departure time
  if(currentTime>=depTime)
  {
  return TRAIN_DEPARTED;
  }
  return TRAIN_NONE;
  }
