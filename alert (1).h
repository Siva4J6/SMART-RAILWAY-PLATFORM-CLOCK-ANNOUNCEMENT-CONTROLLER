//alert.h
#ifndef __ALERT_H__
#define __ALERT_H__
#include"types.h"
#include"compare.h"

void Alert_Init(void);
void GreenLED_ON(void);
void GreenLED_OFF(void);

void YELLOWLED_ON(void);
void YELLOWLED_OFF(void);

void REDLED_ON(void);
void REDLED_OFF(void);

void BUZZER_ON(void);
void BUZZER_OFF(void);

void TrainAlert(u8 TrainIndex);
#endif

