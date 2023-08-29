//Using UART, transmit "Hello" whenever any character is entered
/*
Author: Abhinav Sushil Pawar
Date: 19-06-2023
*/
#include<lpc21xx.h>
unsigned char received;
void serial()
{
    PINSEL0=0x00000005;		//[0101]	config P0.1->RxD(UART0)[01], and P0.0->TxD(UART0)[01]
    U0LCR=0x83;						//1000 0011 (Line control register)
    U0DLL=0x61;
    U0LCR=0x03;	
}
void delay()
{
    int i;
    for(i=0;i<100;i++);
}
int main()
{
    unsigned int i;
    unsigned char msg[]={"Hello"};
    serial();				//UART initialise

		while(1)
		{
			i=0;			
			while(msg[i]!='\0')					//Send (till end of string)
			{
				//U0LSR.5->Transmit holding register empty (0->U0THR has valid data; 1=>U0THR empty) 
				while(!(U0LSR&0x20)); 	  //wait till U0THR is empty
				U0THR=msg[i];							//send chardata through UOTHR
				i++;
			}
			//U0LSR.0->Receiver data ready (0=>U0RBR is empty; 1=>U0RBR contains valid data)
			while(!(U0LSR&0x01));  //Receive		//wait till U0RBR contains valid data
			received=U0RBR;				//copy received data in a variable
			//U0THR=received;			//--> to print the entered character
			U0THR=' ';						//send space char
			delay();				//optional
		}
}
