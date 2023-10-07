/*
  UART0 in LPC2148(ARM7) using Interrupt
  http://www.electronicwings.com/arm7/lpc2148-uart0
*/

#include <lpc214x.h>
#include <stdint.h>

char rx;

__irq void UART0_Interrupt(void);

void UART0_init(void)
{
	PINSEL0 = PINSEL0 | 0x00000005;	/* Enable UART0 Rx0 and Tx0 pins of UART0 */
	U0LCR = 0x83;	/* DLAB = 1, 1 stop bit, 8-bit character length */
	U0DLM = 0x00;	/* For baud rate of 9600 with Pclk = 15MHz */
	U0DLL = 0x61;	/* We get these values of U0DLL and U0DLM from formula */
	U0LCR = 0x03; /* DLAB = 0 */
	U0IER = 0x00000003;	/* Enable THRE and RBR interrupt */
}


__irq void UART0_Interrupt(void)
{
	int iir_value;
	iir_value = U0IIR;
	while ( !(iir_value & 0x01) );
	if( iir_value & 0x00000004 )
	{
		rx = U0RBR;
	}
		U0THR = rx;
		while( (U0LSR & 0x40) == 0 );
	VICVectAddr = 0x00;
}


int main(void)
{
	UART0_init();
	VICVectAddr0 = (unsigned) UART0_Interrupt;	/* UART0 ISR Address */
	VICVectCntl0 = 0x00000026;	/* Enable UART0 IRQ slot */
	VICIntEnable = 0x00000040;	/* Enable UART0 interrupt */
	VICIntSelect = 0x00000000;	/* UART0 configured as IRQ */
	while(1);
}

