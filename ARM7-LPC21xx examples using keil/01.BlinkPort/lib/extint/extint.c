#include "system.h"
#include "irq.h"
#include "extint.h"

uint8_t EINT_init(uint32_t intt,uint32_t mode,uint32_t polar,void *fun)
{
	if(intt==0)
		EINT0_SEL;
	else if(intt==1)
		EINT1_SEL;		
	else if(intt==2)
		EINT2_SEL;
	else if(intt==3)
		EINT3_SEL;
	
	if(mode)
		EXTMODE |= ( 1 << intt );
	else 
		EXTMODE &= ~( 1 << intt );
	
	if(polar)
		EXTPOLAR |= ( 1 << intt );
	else 
		EXTPOLAR &= ~( 1 << intt );
	 
  if ( install_irq( intt + 14, fun ) == FALSE )
  {
		return (FALSE);
  }
	return (TRUE);

}

