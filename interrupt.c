/*
 * interrupt.c
 * Configures external interrupt 0 (EINT0) on the LPC21xx. When the
 * admin switch is pressed, the ISR sets the AdminMode flag which the
 * main program checks to enter admin mode.
 */
#include <LPC21xx.H>
#include"types.h"
#include"interrupt.h"

#define EINT0_VIC_CHNO 14           // VIC channel number of EINT0
#define EINT0_PIN_FUNC 0x0000000C   // PINSEL0 bits[3:2]=11 -> P0.1 as EINT0

u32 AdminMode=0;                    // Flag: 1 = admin mode requested

/*
 * EINT0_ISR
 * Interrupt service routine for EINT0. Sets the AdminMode flag,
 * clears the interrupt flag and signals end of interrupt to the VIC.
 */
void EINT0_ISR(void) __irq
{
AdminMode=1;                // Tell main loop to enter admin mode
EXTINT=(1<<0);              // Clear EINT0 interrupt flag
VICVectAddr=0;              // Acknowledge interrupt to VIC (end of ISR)
}

/*
 * EINT0_Init
 * Sets up P0.1 as EINT0 and registers EINT0_ISR as a vectored IRQ.
 */
void EINT0_Init(void)
{
  PINSEL0&=~(3<<2);                     // Clear P0.1 function bits
  PINSEL0|=EINT0_PIN_FUNC;              // Select EINT0 function on P0.1
  VICIntEnable|=1<<EINT0_VIC_CHNO;      // Enable EINT0 interrupt in VIC
  VICVectCntl0=(1<<5)|EINT0_VIC_CHNO;   // Slot 0: enable + assign EINT0 channel
  VICVectAddr0=(u32)EINT0_ISR;          // Address of ISR for slot 0
  EXTMODE|=(1<<0);                      // EINT0 edge-sensitive
}
