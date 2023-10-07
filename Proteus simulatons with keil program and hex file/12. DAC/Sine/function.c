#include<lpc214x.h>
#include "header.h"
#define bit(x) (1<<x)

void pll_init(void)                  
{
    PLL0CON=0x01;
    PLL0CFG=0x24;
    PLL0FEED=0xAA;
    PLL0FEED=0x55;
    while(!(PLL0STAT&(1<<10)));
    PLL0CON=0x03;
    PLL0FEED=0xAA;
    PLL0FEED=0x55;
    VPBDIV=0x01;
}


void delay_milliseconds(unsigned int milliseconds)
{
   T0CTCR = 0x0;  //Select the timer mode
	 T0TCR = 0x00;  //Timer off
	 T0PR = 59999;  //Prescale value
	 T0TCR = 0x02;  //Timer reset
	 T0TCR = 0x01;  // Timer on
	 while(T0TC < milliseconds); //Check for the count of time
	 T0TCR = 0x00;     //Timer off
	 T0TC = 0;        // Clear the TC
}

void delay_microseconds(unsigned int microseconds)
{
   T0CTCR = 0x0;  //Select the timer mode
	 T0TCR = 0x00;  //Timer off
	 T0PR = 59;  //Prescale value
	 T0TCR = 0x02;  //Timer reset
	 T0TCR = 0x01;  // Timer on
	 while(T0TC < microseconds); //Check for the count of time
	 T0TCR = 0x00;     //Timer off
	 T0TC = 0;        // Clear the TC
}

void write_to_dac(int i)
{ 
	DACR=(1<<16)|(i<<6);
}

int get_sine(int i)
{ 
	int arr[]={512,574,635,695,752,805,854,898,936,968,993,1010,1021,1023,1019,1006,          //Array initialization for sine values  
		         986,960,926,886,841,791,737,679,619,512,449,388,328,271,218,169,125,
		         87,55,30,13,2,0,4,17,37,63,97,137,182,232,286,344,404};
	if(i<50) 
	return arr[i];
	else 
	return 0;
}
