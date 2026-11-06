/*
 * train.h
 * Train data structure and database size.
 */
#ifndef __TRAIN_H__
#define __TRAIN_H__
#include"types.h"

#define TOTAL_TRAINS 3      // Number of trains stored in TrainDB

// Details of one train
typedef struct
{
u32 TrainNo;            // Train number (e.g. 12627)
s8 TrainName[20];       // Train name (max 19 characters + '\0')
s8 Destination[20];     // Destination station name
u8 ArrHour;             // Scheduled arrival hour   (0-23)
u8 ArrMin;              // Scheduled arrival minute (0-59)

u8 DepHour;             // Scheduled departure hour   (0-23)
u8 DepMin;              // Scheduled departure minute (0-59)

u8 UpdArrHour;          // Updated (actual/expected) arrival hour
u8 UpdArrMin;           // Updated arrival minute

u8 UpdDepHour;          // Updated departure hour
u8 UpdDepMin;           // Updated departure minute

u8 Platform;            // Platform number
u8 Delay;               // Delay in minutes (0 = on time)
}TrainInfo;
#endif 
