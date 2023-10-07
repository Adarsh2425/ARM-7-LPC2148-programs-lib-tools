#include<lpc21xx.h>
void delay();
int main()
{
    IO0DIR |=0xFFFFFFFF;          //Port 0 is configured as a output pin
    while(1) 
			{
        IO0SET |=0xFFFFFFFF;      //Port 0's all pins are high now (LED is ON)
        delay();                  // Calls Delay Function
        IO0CLR |=0xFFFFFFFF;      //Port 0's all pins are low now (LED is OFF)
        delay();                  //Calls Delay Function
    }  
return 0;		
}       
        
void delay()                       // Delay Function
{
    unsigned int i;
    for(i=0;i<30000;i++);
}

