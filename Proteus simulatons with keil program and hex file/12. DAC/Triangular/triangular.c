#include <lpc214x.h>
void delay();


int main()
{
	PINSEL1=1<<19;
	DACR=0;
	while(1)
	{
	 for(int i=0; i<1024 ;i++)
	  {
		 DACR=i<<6;
		 delay();
	  }
		for(int i=1023; i>=0 ;i--)
	  {
		  DACR=i<<6;
			delay();
	  }
   }return 0;
}
	
		
void delay()                       // Delay Function
{
    unsigned int i;
    for(i=0;i<2000;i++);
}