#ifndef __ALERT_H__
#define __ALERT_H__
#include"types.h"
//#include"compare.h"
#include"compare.h"

void Alert_Init(void);

void GreenLED_ON(void);
void GreenLED_OFF(void);

void YellowLED_ON(void);
void YellowLED_OFF(void);

void RedLED_ON(void);
void RedLED_OFF(void);

void Buzzer_ON(void);
void Buzzer_OFF(void);


void TrainAlert(u8 TrainIndex);
#endif
