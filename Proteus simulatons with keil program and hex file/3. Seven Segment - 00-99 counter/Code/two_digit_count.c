#include<lpc21xx.h>

void delay(unsigned int a)   //Delay Function
{
    for(a=1;a<=60000;a++);
}

int main()
{
	
    IO0DIR|=0xFFFFFFFF;     //Port 0 is configured as output port

	while(1)
 { 
	 unsigned  long int j; //Variable declared as long integer
   int i;                //Variable declared as integer
   int a[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};   // Initializing Integer Array with numbers for the Display
   
   for(j=0;j<10;j++)       // For loop for tens place in the display 
    { 
	    IO0SET|=a[j];        //Sets corresponding pins HIGH
        for(i=0;i<10;i++)  // For loop for ones place in the display
         {
             IO0SET|=(a[i]<<8);  // integr array shifted by 8 bits (for ones place); Sets corresponding pins HIGH 
             delay(100000);      // Calls Delay Function
             IO0CLR|=(a[i]<<8);  //integr array shifted by 8 bits (for ones place); Sets corresponding pins LOW
          }
        IO0CLR|=a[j];    //Sets corresponding pins LOW
	  }
 } return 0;
}
