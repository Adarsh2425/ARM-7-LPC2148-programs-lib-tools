#include<lpc213x.h>
#define fpclk 15000000
#define BAUD_BPS 9600

// UART0 Initialization with / without interrupt in Vectored IRQ mode
void UART0_Init()
{
	 int baud16 = (fpclk/(16*BAUD_BPS));
	 PINSEL0 = PINSEL0 & (~(1<<3)|(1<<2)|(1<<1)|(1<<0));//For clearing the required bits
	 PINSEL0 = PINSEL0 | ((0x1<<0)|(0x1<<2)); //For selecting the UART mode of P0.0 to P0.1 
	 U0LCR = 0x83;// to select word length and for enabling DLAB
	 U0DLL = baud16%256;// For desired baud rate
	 U0DLM = baud16/256; // For desired baud rate
	 U0LCR = 0x03;// set DLAB to 0 again for futher operation
	 /*U0IER = 0x01; // RBR interrupt enable
	 VICIntSelect &= ~(1<<6); // Selecting the IRQ option
	 VICVectAddr = (long)ISR_UART0; // Assigning the ISR value to the VICVectAddr
	 VICVectCntl0 = (0x20 | 6) ;//  Selecting the Vectored IRQ mode*/ 
}

void UART0_Send_Byte(char ch)
{
	 U0THR = ch; // Transmission Buffer has the value for transmission
	 while((U0LSR & 0x40) == 0); // check (TEMT bit) 
	                             //Waiting till the transmission has completed
}

char UART_Receive_Byte()
{
	 while((U0LSR & 0x01) == 0 );// Check (RDR bit)
	                            // Wait till the complete data is received
	 return U0RBR; // return the received Byte which is stored in received buffer 
}

void UART0_Send_String(char *str)
{
	 while(*str)
	 {
	  UART0_Send_Byte(*str++);
	 }
}

