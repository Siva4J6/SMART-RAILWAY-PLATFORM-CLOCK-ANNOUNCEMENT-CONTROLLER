/*
 * kpm.h
 * 4x4 matrix keypad driver interface.
 */
#include "types.h"

void Init_KPM(void);    // Configure row pins as outputs

u32 colscan(void);      // Returns 0 if any key is pressed, else 1

u32 rowcheck(void);     // Finds the row of the pressed key

u32 colcheck(void);     // Finds the column of the pressed key

u32 keyscan(void);      // Waits for a key press and returns its ASCII code

u32 ReadNum(void);      // Reads a multi-digit number from keypad ('=' to finish)
