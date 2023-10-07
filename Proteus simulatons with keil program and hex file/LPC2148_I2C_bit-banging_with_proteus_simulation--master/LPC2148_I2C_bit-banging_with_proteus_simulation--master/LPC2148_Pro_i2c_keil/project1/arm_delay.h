
#ifndef __arm_delay
#define __arm_delay

void delay(unsigned int sec)
{
	int i,j;
		
	for(i=0;i<sec;i++)
	{
		for(j=0;j<i;j++)
		j=j;
	}
return ;
	
}


#endif
