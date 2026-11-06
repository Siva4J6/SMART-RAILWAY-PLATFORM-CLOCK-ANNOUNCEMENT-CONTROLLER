//lcd.c
/*
 * HD44780 16x2 LCD driver (8-bit mode).
 * Data  : P0.8 - P0.15
 * RS/EN/RW : P0.16 / P0.17 / P0.18 (see lcd_defines.h)
 */

#include <LPC21xx.h>

#include "types.h"

#include "defines.h"

#include "delay.h"

#include "lcd_defines.h"


/*
 * WriteLCD
 * Places a byte on the data pins, selects write mode and generates
 * the enable pulse that makes the LCD latch the byte.
 */
void WriteLCD(u8 byte)
{
	//write any byte on data pins
	WRITEBYTE(IOPIN0,LCD_DATA,byte);

	//sel write operation
	IOCLR0=1<<LCD_RW;

	//provide high to low pulse on enable pin
	IOSET0=1<<LCD_EN;
	delay_us(1);
	IOCLR0=1<<LCD_EN;

	delay_ms(2);        // Wait for LCD to finish the operation
}


/*
 * CmdLCD
 * Sends a command byte (RS=0).
 */
void CmdLCD(u8 cmd)
{
	//select cmd register
	IOCLR0=1<<LCD_RS;
	IOCLR0=1<<LCD_RS;

	//write to cmd register
	WriteLCD(cmd);
}


/*
 * InitLCD
 * Configures the pins and runs the HD44780 start-up sequence
 * (8-bit, 2-line, display on, cursor off).
 */
void InitLCD(void)
{
	//cfg p0.8-p0.15,p0.16,17,18 as gpio out pins
	IODIR0|=((0xFF<<LCD_DATA)
	        |(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));

	delay_ms(15);               // Power-on wait (>15 ms)
	CmdLCD(0x30);               // Wake-up sequence (3 times)
	delay_ms(4);
	delay_us(100);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);    // 8-bit interface, 2 lines
	CmdLCD(DSP_ON_CUR_OFF);     // Display on, cursor off
	CmdLCD(CLEAR_LCD);          // Clear screen
	CmdLCD(SHIFT_CUR_RIGHT);    // Cursor moves right after each character
}


/*
 * CharLCD
 * Displays one ASCII character at the current cursor position (RS=1).
 */
void CharLCD(u8 asciiVal)
{
	//select data register
	IOSET0=1<<LCD_RS;

	//write to display screen/ddram via data reg
	WriteLCD(asciiVal);
}


// Displays a null-terminated string
void StrLCD(s8 *str)
{
	while(*str)
		CharLCD(*str++);
}


/*
 * U32LCD
 * Displays an unsigned integer in decimal. Digits are extracted from the
 * least significant end into an array, then printed in reverse order.
 */
void U32LCD(u32 n)
{
	u8 a[10];       // Holds up to 10 digits of a 32-bit number
	s32 i=0;
	if(n==0)
	{
		CharLCD('0');
	}
	else
	{
		while(n>0)
		{
			a[i]=(n%10)+48;     // Digit -> ASCII
			n/=10;
			i++;
		}
		for(--i;i>=0;i--)       // Print most significant digit first
			CharLCD(a[i]);
	}
}


// Displays a signed integer (prints '-' for negative numbers)
void S32LCD(s32 n)
{
	if(n<0)
	{
		CharLCD('-');
		n=-n;
	}
	U32LCD(n);
}

/*
 * F32LCD
 * Displays a float with nDP digits after the decimal point.
 */
void F32LCD(f32 fn,u8 nDP)
{
	u32 n; s32 i;
	if(fn<0.0)
	{
		CharLCD('-');
		fn=-fn;
	}
	n=fn;               // Integer part
	U32LCD(n);
	CharLCD('.');
	for(i=0;i<nDP;i++)  // Fractional digits, one at a time
	{
		fn=(fn-n)*10;
		n=fn;
		CharLCD(n+48);
	}
}


/*
 * BuildCGRAM
 * Stores custom character patterns (nBytes bytes from array p) into the
 * LCD's CGRAM, then returns the cursor to the start of line 1.
 */
void BuildCGRAM(u8 *p,u8 nBytes)
{
	u8 i;
	//cmd for goto cgram start
	CmdLCD(GOTO_CGRAM_START);
	//write into cgram
	//select data reg
	IOSET0=1<<LCD_RS;
	for(i=0;i<nBytes;i++)
	{
		WriteLCD(p[i]);
	}
	//point back to ddram start
	CmdLCD(GOTO_LINE1_POS0);
}
