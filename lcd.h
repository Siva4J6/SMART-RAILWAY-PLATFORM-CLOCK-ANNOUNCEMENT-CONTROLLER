//lcd.h
/*
 * 16x2 character LCD (HD44780) driver interface.
 */
#include "types.h"

void WriteLCD(u8);          // Write a raw byte to the LCD data pins + pulse EN
void CmdLCD(u8);            // Send a command byte
void InitLCD(void);         // Initialise the LCD
void CharLCD(u8);           // Display one character
void StrLCD(s8 *);          // Display a string
void U32LCD(u32);           // Display an unsigned integer
void S32LCD(s32);           // Display a signed integer
void F32LCD(f32,u8);        // Display a float with given decimal places
void BuildCGRAM(u8 *,u8 );  // Load custom characters into CGRAM
