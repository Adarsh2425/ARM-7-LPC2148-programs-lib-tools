
#include "LPC214x.h"			/* LPC23XX Peripheral Registers	*/
#include "system.h"
#include <stdint.h>
#include "irq.h"

void DefaultVICHandler (void) __irq
{
    /* if the IRQ is not installed into the VIC, and interrupt occurs, the
    default interrupt VIC address will be used. This could happen in a race 
    condition. For debugging, use this endless loop to trace back. */
    /* For more details, see Philips appnote AN10414 */
    VICVectAddr = 0;		/* Acknowledge Interrupt */ 
    while ( 1 );
}

void init_VIC(void) 
{
    uint32_t i = 0;
    uint32_t *vect_addr, *vect_cntl;
   	
    /* initialize VIC*/
    VICIntEnClr = 0xffffffff;
    VICVectAddr = 0;
    VICIntSelect = 0;

    /* set all the vector and vector control register to 0 */
    for ( i = 0; i < VIC_SIZE; i++ )
    {
				vect_addr = (uint32_t *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
				vect_cntl = (uint32_t *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
				*vect_addr = 0;	
				*vect_cntl = 0;
    }

    /* Install the default VIC handler here */
    VICDefVectAddr = (uint32_t)DefaultVICHandler;   
    return;
}

uint8_t install_irq( uint32_t IntNumber, void *HandlerAddr )
{
    uint32_t i;
    uint32_t *vect_addr;
    uint32_t *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
				/* find first un-assigned VIC address for the handler */

				vect_addr = (uint32_t *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
				vect_cntl = (uint32_t *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
				if ( *vect_addr == (uint32_t)NULL )
				{
						*vect_addr = (uint32_t)HandlerAddr;	/* set interrupt vector */
						*vect_cntl = (uint32_t)(IRQ_SLOT_EN | IntNumber);
						break;
				}
    }
    if ( i == VIC_SIZE )
    {
				return( FALSE );		/* fatal error, can't find empty vector slot */
    }
    VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
    return( TRUE );
}

uint8_t uninstall_irq( uint32_t IntNumber )
{
    uint32_t i;
    uint32_t *vect_addr;
    uint32_t *vect_cntl;
      
    VICIntEnClr = 1 << IntNumber;	/* Disable Interrupt */
    
    for ( i = 0; i < VIC_SIZE; i++ )
    {
	/* find first un-assigned VIC address for the handler */
				vect_addr = (uint32_t *)(VIC_BASE_ADDR + VECT_ADDR_INDEX + i*4);
				vect_cntl = (uint32_t *)(VIC_BASE_ADDR + VECT_CNTL_INDEX + i*4);
				if ( (*vect_cntl & ~IRQ_SLOT_EN ) == IntNumber )
				{
						*vect_addr = (uint32_t)NULL;	/* clear the VIC entry in the VIC table */
						*vect_cntl &= ~IRQ_SLOT_EN;	/* disable SLOT_EN bit */	
						break;
				}
    }
    if ( i == VIC_SIZE )
    {
					return( FALSE );		/* fatal error, can't find interrupt number 
					in vector slot */
    }
    VICIntEnable = 1 << IntNumber;	/* Enable Interrupt */
    return( TRUE );
}
