#include "system.h"
#include "spi.h"

void spi_init (void)
{
		PCONP	  |= 0x00000100;
		PINSEL0	|= 0x00001500;
		S0SPCCR	 = 0x8; 	
		S0SPCR   = 0x00000020 ;
}

uint8_t spi_data(uint8_t cmd)
{
		uint8_t data=0;
		S0SPDR = cmd;
		while (!(S0SPSR & 0x80)){}
		data = S0SPDR;
    
return ( data );	
}
