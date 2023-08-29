#include <LPC214X.H>
#include "system.h"
#include "adc.h"

void adc0_init(void)
{
	PINSEL1 |= 0x15000F00 ; // P0.28, AD0.1
	PINSEL0 |= 0x00000F00 ;
}

uint16_t adc0_read(unsigned char ch)
{
 unsigned int adcdata;
 AD0CR = 0x01200300 | (1<<ch) ; // Select AD0.1, Select clock for ADC, Start of conversion
 while(!((adcdata = AD0GDR) & 0x80000000)) // Check end of conversion (Done bit) and read result
 {
 
 }
 return((adcdata >> 6) & 0x3ff) ; // Return 10 bit result
}
