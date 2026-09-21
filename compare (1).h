#ifndef __COMPARE_H__
#define __COMPARE_H__
#include "types.h"
#define TRAIN_NONE 0
#define TRAIN_APPROACHING 1
#define TRAIN_ONTIME 2
#define TRAIN_DELAYED 3
#define TRAIN_DEPARTED 4
u8 FindCurrentTrain(s32 hour,s32 min);
u8 GetTrainStatus(u8 index);
#endif
