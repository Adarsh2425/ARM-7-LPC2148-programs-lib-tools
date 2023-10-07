//////////////////////////////////////////////
#include <lpc214x.h>
#include "gpio.h"

int pinRead (int pinNr)
{
	unsigned int mydata;
	if (pinNr < 100)
	{// Port0 Pin Eg pinNr= 14 P0.14
		// Set the Direction
		IODIR0 = (IODIR0 & (~(0x01 << pinNr)));
		// Read the Entire Port0
		mydata = IOPIN0 ;
		// Check for the target bit, return 0 or 1
		if ((mydata & (0x01<< pinNr))==0)
		return 0;
		else
		return 1;
	}
	else
	{// Port1 Pin
		pinNr = pinNr-100;
		// Set the direction of Port1 as intput
		IODIR1 = IODIR1 & (~(0x01 << pinNr)) ;
		// read the entire port
		mydata = IOPIN1;
		if (((mydata & (0x01 << pinNr))==0))
		return 0;
		else
		return 1;
	}	
}

//////////////////////////////////////////////
int portRead(int portNr)
{
	unsigned int mydata;
	if (portNr < 10)
	{// Port-0
		if (portNr == 0)
		{// Block0 of P0-> P0.0 t0 P0.7
			IODIR0 = IODIR0 & (0xFFFFFF00);
			mydata = IOPIN0;
			return (mydata & (0x000000FF));
		}
		else if(portNr==1)
		{// Block 1 of P0-> P0.8 to P0.15
			IODIR0 = IODIR0 & (0xFFFF00FF);
			mydata = IOPIN0;
			return (mydata & (0x0000FF00))>>8;
		}
		else if(portNr==2)
		{// Block 2 of P0-> P0.16 to P0.23
			IODIR0 = IODIR0 & (0xFF00FFFF);
			mydata = IOPIN0;
			return (mydata & (0x00FF0000))>>16;
		}
		else if(portNr==3)
		{// Block 3 of P0-> P0.24 to P0.31
			IODIR0 = IODIR0 & (0x00FFFFFF);
			mydata = IOPIN0;
			return (mydata & (0xFF000000))>>24;
		}
		else if(portNr==9)
		{// Complete P0
			IODIR0 = IODIR0 & (0x00000000);
			mydata = IOPIN0;
			return (mydata);
		}
	}
}