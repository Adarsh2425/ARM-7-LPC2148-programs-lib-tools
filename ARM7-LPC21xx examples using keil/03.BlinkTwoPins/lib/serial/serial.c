#include "LPC214x.h"
#include "system.h"
#include "target.h"
#include "irq.h"
#include "serial.h"
#include "Nstring.h"
#include "delay.h"

volatile char rxBuffer0[RXBUFFERMAX];
volatile int rx_Buffer0_Head=-1,rx_Buffer0_Tail=-1;

volatile char rxBuffer1[RXBUFFERMAX];
volatile int rx_Buffer1_Head=-1,rx_Buffer1_Tail=-1;

uint8_t Serial0Status;
uint8_t Serial1Status;

uint8_t serial0_init( uint32_t Baudrate )
{
			uint64_t Fdiv;
			PINSEL0 |= 0x00000005;       						/* Enable RxD0 and TxD0 */
			U0LCR = 0x83;               						/* 8 bits, no Parity, 0 Stop bit    */
			Fdiv = ( Fpclk / 16 ) / Baudrate ;			/*baud rate */
			U0DLM = Fdiv / 256;
			U0DLL = Fdiv % 256;
			U0LCR = 0x03;               						/* DLAB = 0                         */
			U0FCR = 0x07;														/* Enable and reset TX and RX FIFO. */

			if( install_irq( UART0_INT, (void *)Serial0Handler ) == FALSE )
			{
					return (FALSE);
			}
				
		U0IER = IER_RBR | IER_THRE | IER_RLS;			/* Enable Serial0 interrupt */
    return (TRUE);
}

uint8_t serial1_init( uint32_t Baudrate )
{
				uint64_t Fdiv;
				PINSEL0 |= 0x00050000;       					/* Enable RxD0 and TxD0 */
				U1LCR = 0x83;               					/* 8 bits, no Parity, 1 Stop bit    */
				Fdiv = ( Fpclk / 16 ) / Baudrate ;		/*baud rate */
				U1DLM = Fdiv / 256;
				U1DLL = Fdiv % 256;
				U1LCR = 0x03;               					/* DLAB = 0                         */
				U1FCR = 0x07;													/* Enable and reset TX and RX FIFO. */

				if( install_irq( UART1_INT, (void *)Serial1Handler ) == FALSE )
				{
						return (FALSE);
				}

				U1IER = IER_RBR | IER_THRE | IER_RLS;	/* Enable Serial0 interrupt */

				return (TRUE);
}

void serial0_write( char ch )
{
			U0IER = IER_THRE | IER_RLS;							/* Disable RBR */
			while (!( U0LSR & LSR_THRE ));
			U0THR = ch;
			U0IER = IER_THRE | IER_RLS | IER_RBR;		/* Re-enable RBR */
}

void serial1_write( char ch )
{
			U1IER = IER_THRE | IER_RLS;							/* Disable RBR */
			while (!( U1LSR & LSR_THRE ));
			U1THR = ch;
			U1IER = IER_THRE | IER_RLS | IER_RBR;		/* Re-enable RBR */

}
	
void serial0_print( char *str)
{
			while(*str)
				serial0_write(*str++);

			return;
}

void serial1_print( char *str)
{
		while(*str)
				serial1_write(*str++);
	return;
}

char serial0_read( void )
{
	char ch;
if(rx_Buffer0_Head == -1)
		return 0;
	    ch=rxBuffer0[rx_Buffer0_Head];
	
		if(rx_Buffer0_Head == rx_Buffer0_Tail)
		{
				rx_Buffer0_Head = rx_Buffer0_Tail = -1;
		}
		else
		{
			rx_Buffer0_Head++;
     	if(rx_Buffer0_Head == RXBUFFERMAX)
			rx_Buffer0_Head=0;
		}
	return ch;
}

char serial1_read( void )
{
	char ch;
	if(rx_Buffer1_Head == -1)
		return 0;
	    ch=rxBuffer1[rx_Buffer1_Head];
	
		if(rx_Buffer1_Head == rx_Buffer1_Tail)
		{
				rx_Buffer1_Head = rx_Buffer1_Tail = -1;
		}
		else
		{
			rx_Buffer1_Head++;
     	if(rx_Buffer1_Head == RXBUFFERMAX)
			rx_Buffer1_Head=0;
		}
return ch;
}	

uint16_t serial0_available(void)
{
if(rx_Buffer0_Head==-1) 
			return 0;
	if(rx_Buffer0_Head < rx_Buffer0_Tail)
			return(rx_Buffer0_Tail - rx_Buffer0_Head + 1);
	else if(rx_Buffer0_Head > rx_Buffer0_Tail)
			return (RXBUFFERMAX - rx_Buffer0_Head + rx_Buffer0_Tail + 1);
	else
		return 1;
}

uint16_t serial1_available(void)
{
if(rx_Buffer1_Head==-1) 
			return 0;
	if(rx_Buffer1_Head < rx_Buffer1_Tail)
			return(rx_Buffer1_Tail - rx_Buffer1_Head + 1);
	else if(rx_Buffer1_Head > rx_Buffer1_Tail)
			return (RXBUFFERMAX - rx_Buffer1_Head + rx_Buffer1_Tail + 1);
	else
		return 1;
}

void serial0_flush(void)
{
		while(serial0_available())
			serial0_read();
}

void serial1_flush(void)
{
		while(serial1_available())
			serial1_read();
}

void serial0_responce(char *str,unsigned int timeout)
{
	int delay=0,i=0;
	while(timeout > delay)
	{
		while(serial0_available() > 0)
		{
			char ch=serial0_read();
			str[i++]=ch;
		}
		delay_ms(1);
		delay++;
	}
	str[i]='\0';
}

void serial1_responce(char *str,unsigned int timeout)
{
	int delay=0,i=0;
	while(timeout > delay)
	{
		while(serial1_available() > 0)
		{
			char ch=serial1_read();
			str[i++]=ch;
		}
		delay_ms(1);
		delay++;
	}
	str[i]='\0';
}

void serial0_buff( char ch )
{
char rxData=ch;
		
			if((rx_Buffer0_Tail == RXBUFFERMAX-1 && (rx_Buffer0_Head == 0)) || ((rx_Buffer0_Tail + 1) == rx_Buffer0_Head))
			{
				rx_Buffer0_Head++;
			}
			
			if(rx_Buffer0_Head == RXBUFFERMAX || rx_Buffer0_Head == -1)
				rx_Buffer0_Head=0;
			
			if(rx_Buffer0_Tail == RXBUFFERMAX - 1) 
					rx_Buffer0_Tail=0;
			else 
					rx_Buffer0_Tail++;
			rxBuffer0[rx_Buffer0_Tail]=rxData;
}
void serial1_buff( char ch )
{
			char rxData=ch;
		
			if((rx_Buffer1_Tail == RXBUFFERMAX-1 && (rx_Buffer1_Head == 0)) || ((rx_Buffer1_Tail + 1) == rx_Buffer1_Head))
			{
				rx_Buffer1_Head++;
			}
			
			if(rx_Buffer1_Head == RXBUFFERMAX || rx_Buffer1_Head == -1)
				rx_Buffer1_Head=0;
			
			if(rx_Buffer1_Tail == RXBUFFERMAX - 1) 
					rx_Buffer1_Tail=0;
			else 
					rx_Buffer1_Tail++;
			rxBuffer1[rx_Buffer1_Tail]=rxData;

}
	

void Serial0Handler (void) __irq
{
    uint8_t IIRValue, LSRValue;
    volatile uint8_t Dummy,rdata;

    IENABLE;					/* handles nested interrupt */
    IIRValue = U0IIR;

    IIRValue >>= 1;				/* skip pending bit in IIR */
    IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
   
		if ( IIRValue == IIR_RLS )	/* Receive Line Status */
    {
		LSRValue = U0LSR;
		/* Receive Line Status */
		if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
		{
		    /* There are errors or break interrupt */
		    /* Read LSR will clear the interrupt */
		    Serial0Status = LSRValue;
		    Dummy = U0RBR;		/* Dummy read on RX to clear interrupt, then bail out */
		    IDISABLE;
		    VICVectAddr = 0;	/* Acknowledge Interrupt */
		    return;
		}
		
		if ( LSRValue & LSR_RDR )	/* Receive Data Ready */
		{
		    /* If no error on RLS, normal ready, save into the data buffer. */
		    /* Note: read RBR will clear the interrupt */
		    rdata = U0RBR;
		    serial0_buff(rdata); 
		
		}
    }
    else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
    {
		/* Receive Data Available */
		    rdata = U0RBR;
		    serial0_buff(rdata); 
		
    }
    else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
    {
				/* Character Time-out indicator */
				Serial0Status |= 0x100;		/* Bit 9 as the CTI error */
    }

    IDISABLE;
    VICVectAddr = 0;				/* Acknowledge Interrupt */
}

void Serial1Handler (void) __irq
{
		uint8_t IIRValue, LSRValue;
    volatile uint8_t Dummy,rdata;

    IENABLE;					/* handles nested interrupt */
    IIRValue = U1IIR;

    IIRValue >>= 1;				/* skip pending bit in IIR */
    IIRValue &= 0x07;			/* check bit 1~3, interrupt identification */
    if ( IIRValue == IIR_RLS )	/* Receive Line Status */
    {
		LSRValue = U1LSR;
		/* Receive Line Status */
		if ( LSRValue & (LSR_OE|LSR_PE|LSR_FE|LSR_RXFE|LSR_BI) )
		{
		    /* There are errors or break interrupt */
		    /* Read LSR will clear the interrupt */
		    Serial1Status = LSRValue;
		    Dummy = U1RBR;		/* Dummy read on RX to clear interrupt, then bail out */
		    IDISABLE;
		    VICVectAddr = 0;	/* Acknowledge Interrupt */
		    return;
		}
		if ( LSRValue & LSR_RDR )	/* Receive Data Ready */
		{
		    /* If no error on RLS, normal ready, save into the data buffer. */
		    /* Note: read RBR will clear the interrupt */
		    rdata = U1RBR;
		    serial1_buff(rdata); 
		}
    }
    else if ( IIRValue == IIR_RDA )	/* Receive Data Available */
    {
		/* Receive Data Available */		
		    rdata = U1RBR;
		    serial1_buff(rdata); 
		
    }
    else if ( IIRValue == IIR_CTI )	/* Character timeout indicator */
    {
		/* Character Time-out indicator */
		Serial1Status |= 0x100;		/* Bit 9 as the CTI error */
    }

    IDISABLE;
    VICVectAddr = 0;				/* Acknowledge Interrupt */

}
