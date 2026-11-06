/*
 * delay.c
 * Software delay routines using busy-wait loops.
 * Calibrated for a 60 MHz CPU clock (CCLK), where one loop iteration
 * takes roughly 5 clock cycles.
 */

// Delay of tdly microseconds
void delay_us(unsigned int tdly)
{
	tdly*=12;           // 12 iterations per microsecond
	while(tdly--);
	//~5 clock cycles
	//12*5=60 clock cycles
}
// Delay of tdly milliseconds
void delay_ms(unsigned int tdly)
{
	tdly*=12000;        // 12000 iterations per millisecond
	while(tdly--);
	//12000*5=60000 clock cycles
}
//Design a function for 1sec
