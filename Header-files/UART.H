void uart1_init()			  // Uart1 Initialization Function
{
 PINSEL0 =0x00050005;		 // GPIO1[9,8] = Uart Function 	// Select P0.8 = TxD(UART0) // Select P0.9 = RxD(UART0)
 
 U1LCR =0X80;				// Enable Programming of Divisor Latches
 U1DLL =97;					// Program Divisor Latch(391) for 9600 Baud
 U1LCR =0X03;				// Data Bit = 8 Bit
}

void uart1_data(unsigned char val)			//Write character to UART1 
{
 while(!(U1LSR & 0x20));				  // Wait TXD Buffer Empty
 U1THR =val;							  // Write Character
} 

void uart1_enter()
{
	uart1_data(13);
	main_delay(10);
	uart1_data(10);
}
	
unsigned char uart1_rx()				//Read character from UART1
{
 while(!(U1LSR & 0x01));			   // Wait RXD Receive Data Ready
 return(U1RBR);						   // Get Receice Data & Return
} 

void uart1_string( unsigned char *stringptr)		//String Display Function
{
  while (*stringptr)							// Cheack Data is there or not
   uart1_data(*stringptr++);					//Write character to UART1
}

void uart0_init()		// Uart0 Initialization Function
{
 PINSEL0 =0x0005005;   // GPIO1[1,0] = Uart Function 	// Select P0.0 = TxD(UART0) // Select P0.1 = RxD(UART0)
 					    
 U0LCR =0X80;		    // Enable Programming of Divisor Latches
 U0DLL =97;				// Program Divisor Latch(391) for 9600 Baud
 U0LCR =0X03;			// Data Bit = 8 Bit
}

void uart0_data(unsigned char val)		//Write character to UART0 
{										
 while(!(U0LSR & 0x20));			 // Wait TXD Buffer Empty
 U0THR =val;						 // Write Character
} 

unsigned char uart0_rx()			 //Read character from UART0
{
 while(!(U0LSR & 0x01));			// Wait RXD Receive Data Ready
 return(U0RBR);						// Get Receice Data & Return
} 

void uart0_string( char *stringptr)	//String Display Function
{
  while (*stringptr)				// Cheack Data is there or not
   uart0_data(*stringptr++);		//Write character to UART0
} 
