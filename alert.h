/*
 * alert.h
 * Interface for the alert module: status LEDs and buzzer control.
 */
#ifndef __ALERT_H__
#define __ALERT_H__
#include"types.h"
//#include"compare.h"
#include"compare.h"         // Train status codes (TRAIN_APPROACHING, ...)

void Alert_Init(void);      // Configure LED/buzzer pins as outputs (all OFF)

// Green LED (train on time)
void GreenLED_ON(void);
void GreenLED_OFF(void);

// Yellow LED (train approaching)
void YellowLED_ON(void);
void YellowLED_OFF(void);

// Red LED (train delayed)
void RedLED_ON(void);
void RedLED_OFF(void);

// Buzzer
void Buzzer_ON(void);
void Buzzer_OFF(void);

// Drives LEDs/buzzer according to the given train status code
void TrainAlert(u8 TrainIndex);
#endif
