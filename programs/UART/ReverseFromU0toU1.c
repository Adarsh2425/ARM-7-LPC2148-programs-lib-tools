//Read a string in UART0 and send it in reverse to UART1
/*
Author: Abhinav Sushil Pawar
Date: 25-06-2023
*/
#include<lpc21xx.h>
#define MAX 100
void serial()
{
    PINSEL0=0x00050005;		//config P0.9->RxD & P0.8->TxD (UART1) // P0.1->Rxd & P0.0->Txd (UART0)
    U0LCR=0x83;						//1000 0011 (Line control register)
    U0DLL=0x61;
    U0LCR=0x03;	
		U1LCR=0x83;						//1000 0011 (Line control register)
    U1DLL=0x61;
    U1LCR=0x03;	
}
void send_toU1(unsigned char data)
{
	while(!(U1LSR&0x20)); 	  //wait till U1THR is empty
	U1THR=data;						  	//send chardata through U1THR
}
unsigned char receive_fromU0()
{
	unsigned char data;
	while(!(U0LSR&0x01));  	//wait till U0RBR contains valid data
	data=U0RBR;							//copy received data in a variable
	return data;
}
int main()
{
	unsigned char string[MAX];
	while(1){
		unsigned char temp='\n';
		int i=0,size;
		serial();								//initialize UART
		while(temp!=' '){				//Read string from UART0
			temp=receive_fromU0();
			U0THR=temp;
			string[i]=temp;
			i++;
		}
		size=i-1;
		U0THR='\n';
		for(i=size-1;i>=0;i--)	//Print reverse string in UART1
			send_toU1(string[i]);
		send_toU1('\n');
	}
}
