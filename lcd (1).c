//lcd.c
#include<lpc21xx.h>
#include"types.h"
#include"delay.h"
#include"defines.h"
#include"lcd_defines.h"
void WriteLCD(u8 byte)
{
  WRITEBYTE(IOPIN0,LCD_DATA,byte);
  //select write operation
  IOCLR0=1<<LCD_RW;
  //PROVIDE HIGH TO LOW PULSE ON ENABLE PIN
  IOSET0=1<<LCD_EN;
  delay_us(1);
  IOCLR0=1<<LCD_EN;
  delay_ms(2);
  }
  void CmdLCD(u8 cmd)
  {
  //select cmd register
  IOCLR0=1<<LCD_RS;
  //WRIRE  INTO THE CMD REGISTER
  WriteLCD(cmd);
  }
  void InitLCD(void)
  {
    IODIR0|=((0xFF<<LCD_DATA)|(1<<LCD_RS)|(1<<LCD_RW)|(1<<LCD_EN));
	delay_ms(15);
	CmdLCD(0x30);
	delay_ms(4);
	delay_us(100);
	CmdLCD(0x30);
	delay_us(100);
	CmdLCD(0x30);
	CmdLCD(MODE_8BIT_2LINE);
    CmdLCD(DSP_ON_CUR_BLK);
	CmdLCD(CLEAR_LCD);
	CmdLCD(SHIFT_CUR_RIGHT);
	}
	void CharLCD(u8 asciival)
	{
	IOSET0=1<<LCD_RS;
	WriteLCD(asciival);
	}
	void StrLCD(s8* str)
	{
	  while(*str)
	  CharLCD(*str++);
	  }
	  void U32LCD(u32 n)
	  {
	  u8 a[10];
	  s32 i=0;
	  if(n==0)
	  {
	    CharLCD('0');
		}
		else
		{
		while(n>0)
		{
		a[i]=(n%10)+48;
		n/=10;
		i++;
		}
		}
		for(--i;i>=0;i--)
		{
		CharLCD(a[i]);
		}
		}
		void S32LCD(s32 n)
		{
		if(n<0)
		{
		CharLCD('-');
		n=-n;
		}
		U32LCD(n);
		}
		void F32LCD(f32 fn,u8 nDp)
		{
		 u32 n;
		 s32 i;
		 if(fn<0.0)
		 {
		 CharLCD('-');
		 fn=-fn;
		 }
		 n=fn;
		 U32LCD(n);
		 CharLCD('.');
		 for(i=0;i<nDp;i++)
		 {
		 fn=(fn-n)*10;
		 n=fn;
		 CharLCD(n+48);
		 }
		 }
		 void BuildCGRAM(u8*p,u8 nBytes)
		 {
		   u8 i;
		   CmdLCD(GOTO_CGRAM_START);
		   IOSET0=1<<LCD_RS;
		   for(i=0;i<nBytes;i++)
		   {

		     WriteLCD(p[i]);
			 }
			 CmdLCD(GOTO_LINE1_POS0);
			 }

