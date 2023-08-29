//Read a string and send it in reverse (UART1)
/*
Author: Abhinav Sushil Pawar
Date: 21-06-2023
*/
#include<lpc21xx.h>
#define MAX 100
void serial()
{
    PINSEL0=0x00050000;		//[0101]	config P0.9->RxD(UART1)[01], and P0.8->TxD(UART1)[01]
    U1LCR=0x83;						//1000 0011 (Line control register)
    U1DLL=0x61;
    U1LCR=0x03;	
}
void delay()
{
    int i;
    for(i=0;i<100;i++);
}
void sendASCII(unsigned char data)
{
	while(!(U1LSR&0x20)); 	  //wait till U0THR is empty
	U1THR=data;						  	//send chardata through UOTHR
	//delay();
}
unsigned char receiveASCII()
{
	unsigned char data;
	while(!(U1LSR&0x01));  	//wait till U0RBR contains valid data
	data=U1RBR;							//copy received data in a variable
	return data;
}
int main()
{
	unsigned char string[MAX];
	unsigned char temp;
	int i=0,size;
	serial();
	while(temp!=' '){	
		temp=receiveASCII();
		U1THR=temp;
		string[i]=temp;
		i++;
	}
	size=i-1;
	sendASCII(' ');
	for(i=size-1;i>=0;i--)
		sendASCII(string[i]);
	sendASCII('\n');
}
