/*
 * defines.h
 * Generic bit/byte/nibble manipulation macros used by the drivers
 * (LCD, keypad). WORD is normally a GPIO register such as IOPIN0/IOPIN1.
 */
#include"types.h"

// Write an 8-bit value (BYTE) into WORD starting at bit STARTBIT (other bits unchanged)
#define WRITEBYTE(WORD,STARTBIT,BYTE) WORD=(WORD&(u32)~0xFF<<STARTBIT)|(BYTE<<STARTBIT)

// Read a single bit (returns 0 or 1)
#define READBIT(WORD,BIT)((WORD>>BIT)&1)

// Write a single bit (BITLEVEL = 0 or 1) at position BIT
#define WRITEBIT(WORD,BIT,BITLEVEL) WORD=((WORD&~(1<<BIT))|(BITLEVEL<<BIT))

// Copy bit SBIT of WORD into bit DBIT of the same WORD
#define READWRITEBIT(WORD,DBIT,SBIT) WORD=((WORD&~(1<<DBIT))|(((WORD>>SBIT)&1)<<DBIT))

// Copy bit SBIT of SWORD into bit DBIT of DWORD
#define READWRITEBIT2(DWORD,DBIT,SWORD,SBIT) DWORD=((DWORD&~(1<<DBIT))|(((SWORD>>SBIT)&1)<<DBIT))

// Write a 4-bit value (NIBBLE) into WORD starting at bit STARTBIT
#define WRITENIBBLE(WORD,STARTBIT,NIBBLE)  WORD=(WORD&(u32)~0xF<<STARTBIT)|(NIBBLE<<STARTBIT)

// Read 4 bits starting at bit SBIT (returns 0-15)
#define READNIBBLE(WORD,SBIT) ((WORD>>SBIT)&15)

// Clear a single bit
#define CLRBIT(WORD,BIT) WORD&=~(1<<BIT)
