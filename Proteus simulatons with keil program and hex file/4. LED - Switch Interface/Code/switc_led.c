#include<lpc213x.h>
int main()
{
    IO0DIR |=0xFFFFFFFF;                  //Port 0 is configured as output
    IO1DIR = 0x00000000;                  //Port 1 is configured as a input
    while(1)
    {
        if((IO1PIN & (1<<16)) == 0)        //Checking 16th pin of Port 1
            IO0SET|=0xFFFFFFFF;           //Sets all pins of Port 0 to HIGH (LED is ON)
        else
            IO0CLR|=0xFFFFFFFF;           //Sets all pins of Port 0 to LOW (LED is OFF)
    }
		return 0;
}       
        
void delay()                              //Function to generate a delay
{
    unsigned int i;
    for(i=0;i<30000;i++);
}