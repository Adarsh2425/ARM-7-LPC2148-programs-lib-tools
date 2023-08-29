
#include "delay.h"

void delay_ms(unsigned int d)
{
	 int i,j;
	 for(i=0;i<d;i++)
			for(j=0;j<7500;j++);

}
void delay_us(unsigned int d)
{
 int i,j;
	 for(i=0;i<d;i++)
			for(j=0;j<7;j++);
}
