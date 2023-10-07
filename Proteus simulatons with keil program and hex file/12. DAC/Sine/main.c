//4. Generate a sine wave using DAC
#include "header.h"
#include <lpc214x.h>

int main()
{	
	PINSEL1=1<<19;  //P0.25 as DAC output
	int i=0,sine;
	while(1)
	{
	  while(i<50)
	{  
		 sine=get_sine(i);
		 write_to_dac(sine);
		 delay_microseconds(1);
		 i++;
	}
}
	return 0;
}
