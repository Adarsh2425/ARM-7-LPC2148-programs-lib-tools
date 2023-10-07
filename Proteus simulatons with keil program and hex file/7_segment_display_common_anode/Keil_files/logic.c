/*
GPIO PINS:
1. PINSEL - multiplexed pins selection.
2. IOPIN - to read the value of the pin irrespective of the DIR.
3. IODIR - input or output mode (0 for input, 1 for output).
4. IOSET - sends volatge to the pin connected to it.
5. IOCLR - grounds the pin connected to it.
*/

#include <lpc214x.h>

void delay();
int array[10] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90};

int main()
{
	PINSEL0 = 0x00000000; // all port 0 pins as GPIO mode
	IODIR0  = 0x0000007F; // first 7 pins are made output
	
	while(1)
	{
		if((IOPIN0 & 0x00000400) == 0x00000400) //since switch is connected to pin 10 of port0
		{
			for(int i = 9; i>= 0; i--)
			{
				IOSET0 = array[i];
				delay();
				IOCLR0 = array[i];
			}
		}
		
		else 
		{
		 for(int i = 0; i<10; i++)
			{
				IOSET0 = array[i];
				delay();
				IOCLR0 = array[i];
			}
		}
	}
	return 0;
}

void delay()
{
	for (int i = 0; i<90000; i++);	
}