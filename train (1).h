#ifndef __TRAIN_H__
#define __TRAIN_H__
#include"types.h"
#define TOTAL_TRAINS 3
typedef struct 
{
  u32 TrainNo;
  s8 TrainName[20];
  s8 Destination[20];
  u8 ArrHour;
  u8 ArrMin;
  u8 DepHour;
  u8 DepMin;
  u8 UpdArrHour;
  u8 UpdArrMin;
  u8 UpdDepHour;
  u8 UpdDepMin;
  u8 Platform;
  u8 Delay;
  }TrainInfo;
 // TrainInfo TrainDB[TOTAL_TRAINS];
   #endif
