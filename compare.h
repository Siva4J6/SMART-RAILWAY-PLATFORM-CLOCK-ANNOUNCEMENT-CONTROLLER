/*
 * compare.h
 * Train selection / status logic based on the current RTC time.
 */
#ifndef __COMPARE_H__
#define __COMPARE_H__
#include"types.h"

// Train status codes returned by GetTrainStatus()
#define TRAIN_NONE 0            // No valid status
#define	TRAIN_APPROACHING 1     // Current time is before arrival time
#define	TRAIN_ONTIME 2          // Train is at the station (between arrival and departure)
#define	TRAIN_DELAYED 3         // Train has a delay > 0
#define	 TRAIN_DEPARTED 4       // Departure time has passed

u8 FindCurrentTrain(s32 hour,s32 min);  // Index of the next train to depart
u8 GetTrainStatus(u8 index);            // Status code of the given train
#endif
