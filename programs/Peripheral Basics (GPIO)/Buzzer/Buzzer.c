////Buzzer

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
    PINSEL0=0x00000000;			//Configure P0.0 to P0.15 as GPIO
    IODIR0=0x00002000;			//Configure P0.13 as Output
    
    while(1)
    {
        IOSET0=0x00002000;	//ON Buzzer (P0.13->HIGH)
        delay(10);
        IOCLR0=0x00002000;	//OFF Buzzer (P0.13->LOW)
        delay(10);
    }
}