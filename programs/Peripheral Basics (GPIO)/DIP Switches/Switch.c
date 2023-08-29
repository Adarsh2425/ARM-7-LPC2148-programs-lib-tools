////Switch
#include<lpc21xx.h>
void delay(unsigned int j)
{
    int i,k;
    for(i=0;i<j;i++)
    {
        for(k=0;k<9999;k++);
    }
}
int main()
{
    unsigned int x;
    PINSEL2=0x00000000;
    IODIR0=0x000F0000;                //LED p0.16-p0.19        OUTPUT
    IODIR1=0x00000000;                //Switch p1.20-p1.23     INPUT
    while(1)
    {    
            x=IOPIN1;               //input from switch
            x=x & 0x00f00000;				//Consider only the state of pins connected to P1.20-P1.23
            delay(100);
            IOSET0=0x000F0000;			//OFF all the LEDS
            delay(100);
        if(x==0x00100000)				//if switch connected to P1.20 is ON
        {
           IOCLR0=0x00010000;				//ON LED connected to P0.16    
        }
        if(x==0x00200000)				//if switch connected to P1.21 is ON
        {
           IOCLR0=0x00020000;				//ON LED connected to P0.17 
        }
        if(x==0x00400000)				//if switch connected to P1.22 is ON
        {
           IOCLR0=0x00040000;   		//ON LED connected to P0.18     
        }
        if(x==0x00800000)				//if switch connected to P1.23 is ON
        {
           IOCLR0=0x00080000;				//ON LED connected to P0.19
        }
    }
}
