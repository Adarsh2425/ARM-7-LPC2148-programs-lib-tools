//LED's Blink
#include<lpc21xx.h>
void delay(unsigned int constant)
{
	unsigned int i,j;
	for(i=0;i<constant;i++)
	{
		for(j=0;j<10000;j++);
	}
}
int main()
{
	PINSEL1=0x00000000;			//Config. P0.16 to P0.31 as GPIO (Optional, as GPIO=00)
	IODIR0=0x000F0000;			//Config. P0.16 to P0.19 as Output
	while(1)
	{
		IOCLR0=0x000F0000;		//Turn ON LEDs connected to P0.16 to P0.19
		delay(10);
		IOSET0=0x000F0000;		//Turn OFF LEDs connected to P0.16 to P0.19
		delay(10);
	}
}
