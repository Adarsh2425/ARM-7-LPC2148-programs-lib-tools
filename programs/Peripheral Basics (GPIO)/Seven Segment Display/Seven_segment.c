////Seven segment_0-9
//Segment select is at P0.28 and P0.29
#include<lpc21xx.h>

void delay()
{
    int i;
    for(i=0;i<2000000;i++);
}
int main()
{
    int j;
		//Below is the hex code for common cathode seven segment [HGFE DCBA] at pins P0.16 to P0.23
    int b[]={0x003F0000,0x00060000,0x005B0000,0x004F0000,0x00660000,0x006D0000,0x007D0000,0x00070000,
						 0x007F0000,0x006F0000,0x00770000,0x007C0000,0x00390000,0x005E0000,0x00790000,0x00710000};
    for(j=0;j<16;j++)
		{
			IODIR0=0x20FF0000;		//Configure segment select (P0.29) and Segment pins(P0.16-P0.23)
			IOSET0=0x20000000;		//Set P0.29 to select 7segment display connected to it
			IOSET0=b[j];					//Display corresponding number in the 7seg display
      delay();
      IOCLR0=b[j];  				//Clear previous number at display for next number to display
    }
}