#ifndef _UART_H_
	#define _UART_H_

  #include <stdint.h>
	
	#define IER_RBR		0x01
	#define IER_THRE	0x02
	#define IER_RLS		0x04

	#define IIR_PEND	0x01
	#define IIR_RLS		0x03
	#define IIR_RDA		0x02
	#define IIR_CTI		0x06
	#define IIR_THRE	0x01

	#define LSR_RDR		0x01
	#define LSR_OE		0x02
	#define LSR_PE		0x04
	#define LSR_FE		0x08
	#define LSR_BI		0x10
	#define LSR_THRE	0x20
	#define LSR_TEMT	0x40
	#define LSR_RXFE	0x80


	#define RXBUFFERMAX 512
	
	
	extern uint8_t Serial0Status;
	
	extern uint8_t Serial1Status;
	
	uint8_t serial0_init( uint32_t Baudrate );
	uint8_t serial1_init( uint32_t Baudrate );

	void serial0_print( char *BufferPtr );
	void serial1_print( char *BufferPtr );
	
	void serial0_write( char ch );
	void serial1_write( char ch );
	
	char serial0_read( void );
	char serial1_read( void );
	
	uint16_t serial0_available(void);
	uint16_t serial1_available(void);
	
	void serial0_flush(void);
	void serial1_flush(void);
	
	void serial0_responce(char *Response,unsigned int timeout);
	void serial1_responce(char *Response,unsigned int timeout);
	
	
	void serial0_buff( char ch );
	void serial1_buff( char ch );
	
	void Serial0Handler (void) __irq; 
	void Serial1Handler (void) __irq;

#endif//_Serial_H_
