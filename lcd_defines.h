//lcd_defines.h

//HD44780 Commands

#define CLEAR_LCD            0x01   // Clear display, cursor to home

#define RET_CUR_HOME         0x02   // Return cursor to home position

#define SHIFT_CUR_RIGHT      0x06   // Entry mode: cursor moves right after each character

#define SHIFT_CUR_LEFT       0x07   // Entry mode: display shifts left on write

#define DSP_OFF              0x08   // Display off

#define DSP_ON_CUR_OFF       0x0c   // Display on, cursor off

#define DSP_ON_CUR_ON        0x0E   // Display on, cursor on (underline)

#define DSP_ON_CUR_BLK       0x0F   // Display on, cursor blinking

#define SHIFT_DSP_LEFT       0x10   // Move cursor one position left (used as backspace)

#define SHIFT_DSP_RIGHT      0x14   // Move cursor one position right

#define MODE_8BIT_1LINE      0x30   // 8-bit interface, 1 line (also used in init sequence)

#define MODE_4BIT_1LINE      0x20   // 4-bit interface, 1 line

#define MODE_8BIT_2LINE      0x38   // 8-bit interface, 2 lines, 5x8 font

#define MODE_4BIT_2LINE      0x28   // 4-bit interface, 2 lines

#define GOTO_LINE1_POS0      0x80   // DDRAM address: line 1, position 0

#define GOTO_LINE2_POS0      0xC0   // DDRAM address: line 2, position 0

#define GOTO_LINE3_POS0      0x94   // DDRAM address: line 3 (20x4 LCD)

#define GOTO_LINE4_POS0      0xD4   // DDRAM address: line 4 (20x4 LCD)

#define GOTO_CGRAM_START     0x40   // Set CGRAM address to 0 (custom characters)


// LCD pin connections on PORT0
#define LCD_DATA 8//@p0.8(d0)-p0.15(d7)   (8-bit data bus)

#define LCD_RS   16//@p0.16   Register select (0=command, 1=data)

#define LCD_RW   18//@p0.18   Read/Write (0=write)

#define LCD_EN   17//@p0.17   Enable (pulse to latch data)
