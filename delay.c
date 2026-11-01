void delay_us(unsigned int tdly)
{
	tdly*=12;
	while(tdly--);
	//~5 clock cycles
	//12*5=60 clock cycles
}
void delay_ms(unsigned int tdly)
{
	tdly*=12000;
	while(tdly--);
	//12000*5=60000 clock cycles
}
//Design a function for 1sec