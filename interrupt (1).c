#include<lpc21xx.h>
#include"types.h"
#include"interrupt.h"
#define EINT0_VIC_CHNO 14
#define EINT0_PIN_FUNC 0x0000000C
u32 AdminMode=0;
void EINT0_ISR(void) __irq
{
AdminMode=1;
EXTINT=(1<<0);
VICVectAddr=0;
}
void EINT0_Init(void)
{
  PINSEL0&=~(3<<2);
  PINSEL0|=EINT0_PIN_FUNC;
  VICIntEnable|=1<<EINT0_VIC_CHNO;
  VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;
  VICVectAddr0=(u32)EINT0_ISR;
  EXTMODE|=(1<<0);
  //EXTPOLAR&=~(1<<1);
  //VICIntSelect&=~(1<<15);
}

