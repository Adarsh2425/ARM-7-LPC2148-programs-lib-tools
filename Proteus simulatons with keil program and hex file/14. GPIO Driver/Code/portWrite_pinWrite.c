
#include <lpc214x.h>
#include "gpio.h"

void pinWrite(int pinNr, int pinValue)
{
	// pinNr = 0 to 31 for P0
	// pinNr = 100 to 131 for P1
	// pinValue = 0 or 1
	// find whether the pin is in P0 or P1
	// Eg pinWrite(29,1); //P0.29, 1
	// Eg pinWrite(129,0); // port1 pin 29 P1.29 value 0
	if (pinNr < 100)
	{
		// Port 0
		// Eg pinWrite(29,1);
		// Set the Direction of PinNr as Output
		IODIR0 = IODIR0 | (0x01 << pinNr);
		// Check for pinValue.
		if (pinValue == 0)
			IOCLR0 = IOCLR0 | (0x01 << pinNr);
		else
			IOSET0 = IOSET0 | (0x01 << pinNr);
		}
	else
	{
		// Port1
		pinNr = pinNr - 100;
		// Set the Direction of Port-1
		IODIR1 = IODIR1 | (0x01 << pinNr);
		// Check the pin Value
		if (pinValue == 0)
			IOCLR1 = IOCLR1 | (0x01 << pinNr);
		else
			IOSET1 = IOSET1 | (0x01 << pinNr);
	}

}




void portWrite(int portNr, int portValue)
{
	int i;
	// check whether it is P0 or P1
	if (portNr < 10)
	{ // Port 0
		if (portNr == 0) // Block0-> P0.0 to P0.7
		{
			IODIR0 = IODIR0 | (0xFF);
			IOSET0 = IOSET0 | (portValue);
			IOCLR0 = IOCLR0 | ~(portValue);
			// Method - 1
			// for(i=0;i<8;i++)
			// {
			// if((portValue & (0x01 << i))==0)
			// pinWrite(i,0);

			// else
			// pinWrite(i,1);
		// }
		}
		else if(portNr==1) // Port0 B1 -> P0.8 to P0.15
		{	
			IODIR0 = IODIR0 | (0xFF00);
			IOSET0 = IOSET0 | (portValue << 8);
			IOCLR0 = IOCLR0 | (~(portValue)) <<8;
		}
		else if(portNr==2) // Port0 B2 -> P0.16 to P0.23
		{
			IODIR0 = IODIR0 | (0xFF0000);
			IOSET0 = IOSET0 | (portValue << 16);
			IOCLR0 = IOCLR0 | (~(portValue)) <<16;
		}
		else if(portNr==3) // Port0 B3 -> P0.24 to P0.31
		{
			IODIR0 = IODIR0 | (0xFF000000);
			IOSET0 = IOSET0 | (portValue << 24);
			IOCLR0 = IOCLR0 | (~(portValue)) <<24;
		}
		else if(portNr==9) // Port0 -> P0.0 t0 P0.31
		{
			IODIR0 = IODIR0 | (0xFFFFFFFF);
			IOSET0 = IOSET0 | (portValue);
			IOCLR0 = IOCLR0 | ~(portValue) ;
		}		
	}
	else
	{
	// Port-1
		if(portNr==12) // Port1 B2 -> P1.16 to P1.23
		{
			IODIR1 = IODIR1 | (0x00FF0000);
			IOSET1 = IOSET1 | (portValue << 16);
			IOCLR1 = IOCLR1 | (~(portValue)) << 16;
		}
		else if(portNr==13) // Port1 B3 -> P1.24 to P1.31
		{
			IODIR1 = IODIR1 | (0xFF000000);
			IOSET1 = IOSET1 | (portValue << 24);
	    IOCLR1 = IOCLR1 | (~(portValue)) << 24;
		}
		else if(portNr== 19) // Port1 -> P1.0 to P1.31
		{
			IODIR1 = IODIR1 | (0xFFFFFFFF);
			IOSET1 = IOSET1 | (portValue);
			IOCLR1 = IOCLR1 | ~(portValue) ;
		}
		
	}
}



