#include <lpc214x.h>
void delay();

void analog_write(unsigned int data)
	{
		 DACR=data<<6;
	}
	
int main()
{
	PINSEL1=1<<19;
	while(1)
	{
	 for(int i=0; i<100 ;i++)
	  {
		 analog_write(1023);
		 delay(10);
		 analog_write(0);
		 delay(10);
	  }
   }return 0;
}
	
		
void delay()                       // Delay Function
{
    unsigned int i;
    for(i=0;i<30000;i++);
}