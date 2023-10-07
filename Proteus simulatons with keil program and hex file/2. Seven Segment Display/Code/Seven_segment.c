#include<lpc21xx.h>

void delay(unsigned int a)   //Delay Function
{
    for(a=1;a<=75000;a++);
}

int main()
{
   IO0DIR|=0xFFFFFFFF;  // Port 0 is configured as output
while(1)
 { 
	 int i;     //Variable declared as integer
   int a[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F}; // Initializing Integer Array with numbers for the Display
   
	 for(i=0;i<10;i++) //Loop to count from 0 to 9
    { 
	    IO0SET|=a[i];  //Sets corresponding pins HIGH
      delay(75000);  // Calls delay function
		  IO0CLR|=a[i];  //Sets corresponding pins LOW
	  }
  }
 return 0;
}
