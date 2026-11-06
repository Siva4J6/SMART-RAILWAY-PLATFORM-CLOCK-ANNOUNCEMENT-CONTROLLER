/*
 * admin.h
 * Public interface of the admin module (see admin.c).
 */
#ifndef __ADMIN_H__
#define __ADMIN_H__
#include"types.h"

void Admin_Menu(void);      // Shows admin menu and handles the chosen option
void UpdateTrain(void);     // Update arrival/departure/platform/delay of a train
void UpdateRTCTime(void);   // Set RTC time, date and day of week
#endif
