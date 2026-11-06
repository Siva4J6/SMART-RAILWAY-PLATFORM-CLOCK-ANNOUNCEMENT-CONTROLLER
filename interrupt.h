/*
 * interrupt.h
 * External interrupt 0 (EINT0) support, used to enter admin mode.
 */
#ifndef __INTERRUPT_H__

#define __INTERRUPT_H__

#include"types.h"

extern u32 AdminMode;       // Set to 1 by the EINT0 ISR when admin mode is requested

void EINT0_Init(void);      // Configure pin, VIC and mode for EINT0

#endif
