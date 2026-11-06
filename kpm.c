//kpm.c
/*
 * 4x4 matrix keypad driver.
 * Rows  : P1.16 - P1.19 (outputs)
 * Columns: P1.20 - P1.23 (inputs)
 * A key press is detected by driving one row low at a time and checking
 * whether any column reads low.
 */
#include<lpc21xx.h>
#include"defines.h"
#include"kpm_defines.h"
#include"types.h"
#include"lcd_defines.h"
#include"kpm.h"
#include"lcd.h"

// Lookup table: key character for each [row][column] position
u32 KPMLUT[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};

// Configure the 4 row pins (P1.16-P1.19) as outputs; columns stay inputs
void Init_KPM(void)
{
  WRITENIBBLE(IODIR1,ROW0,15);
 }

/*
 * colscan
 * Returns 0 if at least one column is low (a key is pressed on the
 * currently driven row(s)), otherwise returns 1.
 */
u32 colscan(void)
{
	if(READNIBBLE(IOPIN1,COL0)<15)      // Any column bit low?
		return 0;
	else
		return 1;
}

/*
 * rowcheck
 * Drives each row low one at a time; the row for which a column goes
 * low is the row of the pressed key. Returns the row number (0-3).
 */
u32 rowcheck(void)
{
	u32 rno;
	for(rno=0;rno<4;rno++)
	{
		WRITENIBBLE(IOPIN1,ROW0,(~(1<<rno)));   // Only row 'rno' low
		if(colscan()==0)                        // Key found on this row
			break;
	}
	IOCLR1=15<<ROW0;                            // Drive all rows low again
	return rno;
}

/*
 * colcheck
 * Finds which column is low (all rows are low at this point).
 * Returns the column number (0-3).
 */
u32 colcheck(void)
{
	u32 cno;
	for(cno=0;cno<4;cno++)
	{
		if(READBIT(IOPIN1,(cno+COL0))==0)
			break;
	}
	return cno;
}

/*
 * keyscan
 * Blocks until a key is pressed and released, then returns the
 * ASCII code of that key from KPMLUT.
 */
u32 keyscan(void)
{
	u32 rno,cno,key;
	//wait for switch press
	while(colscan());
	//find rno
	rno=rowcheck();
	//find cno
	cno=colcheck();
	//collect key using kpmLut
	key=KPMLUT[rno][cno];
	//wait for switch release
	while(!colscan());
	return key;
}

/*
 * ReadNum
 * Reads a decimal number typed on the keypad and echoes digits on the LCD.
 *   '0'-'9' : append digit
 *   'C'     : delete last digit (backspace)
 *   '='     : finish entry and return the number
 */
u32 ReadNum(void)
{
	u8 key;
	u32 num=0;
	while(1)
	{
		key=keyscan();
		if(key>='0'&&key<='9')
		{
			num=(num*10)+(key-48);      // Add digit to number
			CharLCD(key);               // Echo digit on LCD
			// U32LCD(key);
		}
		else if(key=='=')
		{
			return num;                 // Enter/confirm
		}
		else if(key=='C')
		{
			if(num!=0)
			{
				num=num/10;             // Remove last digit
				CmdLCD(0x10);           // Move cursor left
				CharLCD(' ');           // Erase character on LCD
				CmdLCD(0x10);           // Move cursor left again
			}
		}
	}
}
