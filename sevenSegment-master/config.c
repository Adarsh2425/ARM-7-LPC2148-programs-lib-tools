#include "config.h"

void delay_s (unsigned int x)
{
x=x*CCLK;
while(x--);
}
void delay_ms(unsigned int x)
{
  x=x*(CCLK/1000);
  while(x--);
}
void delay_us(unsigned int x)
{
x=x*(CCLK/1000000);
while(x--);
}
void pll_init(us8 msel, us8 psel)
{
  PLLCFG|=msel;
  PLLCFG|=(psel<<5);
  PLLFEED=0xAA;
  PLLFEED=0x55;
  PLLCON|=1;
  PLLFEED=0xAA;
  PLLFEED=0x55;

  while((PLLSTAT & (1<<10)) == 0);

  PLLCON|=(1<<1);
  PLLFEED=0xAA;
  PLLFEED=0x55;
}


		  //****** Milad Samani - 962059895 ********
//***************************