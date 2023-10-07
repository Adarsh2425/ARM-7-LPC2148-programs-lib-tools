
#include <lpc214x.h>
#include "gpio.h"

void pinSelect(int pinNr, int spFunction) //spfunction 0(00),1(01),2(10),3(11)
{
///pinNr = 0 to 31 for P0, 100 to 131 for P1
/// spFunction = 0,1,2,3
	int bit0;
	int bit1;
	int dummy;
	if (spFunction==0)
	{ 
		bit1 = 0; bit0 = 0;
	}
	else if (spFunction==1)
	{ 
		bit1 = 0; bit0 = 1;
	}
	else if (spFunction==2){ 
		bit1 = 1; bit0 = 0;
	} //
	else if (spFunction==3){ 
		bit1 = 1; bit0 = 1;
	}
	else
	dummy=0;
	if (pinNr >=0 && pinNr <=15)
	{
		// Configue PINSEL0 ==> P0.0 to P0.15
		// Writing a 1
		if (bit0==1)
			PINSEL0 = PINSEL0 | (0x01 << pinNr*2);
		else
		// Writing a 0
			PINSEL0 = PINSEL0 & ~(0x01 << pinNr*2);
		if (bit1==1)
			PINSEL0 = PINSEL0 | (0x01 << (pinNr*2)+1);
		else
			PINSEL0 = PINSEL0 & ~(0x01 << (pinNr*2)+1);
	}
	else if (pinNr >=16 && pinNr <=31)
	{
		pinNr = pinNr-16;
		// Configure PINSEL1 ==> P0.16 to P0.31
		// Writing a 1
		if (bit0==1)
			PINSEL1 = PINSEL1 | (0x01 << pinNr*2);
		else
		// Writing a 0
			PINSEL1 = PINSEL1 & ~(0x01 << pinNr*2);
		if (bit1==1)
			PINSEL1 = PINSEL1 | (0x01 << (pinNr*2)+1);
		else
			PINSEL1 = PINSEL1 & ~(0x01 << (pinNr*2)+1);
	}
	else if (pinNr >=116 && pinNr <=131)
	{
		// Configure PINSEL2 ==> P1.16 to P1.31
		pinNr = pinNr - 116;
		// Writing a 1
		if (bit0==1)
			PINSEL2 = PINSEL2 | (0x01 << pinNr*2);
		else
			// Writing a 0
			PINSEL2 = PINSEL2 & ~(0x01 << pinNr*2);
		if (bit1==1)
			PINSEL2 = PINSEL2 | (0x01 << (pinNr*2)+1);
		else
			PINSEL2 = PINSEL2 & (~(0x01 << (pinNr*2)+1));
	}
	else
	{// do nothing
		dummy = 0;
	}
}
