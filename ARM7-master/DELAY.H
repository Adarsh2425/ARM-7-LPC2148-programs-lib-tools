//Delay Hedar File

void delay(unsigned long int);

void delay(unsigned long int m)
{
	unsigned long int i,j;
	
	for(i=0;i<m;i++)
		for(j=0;j<1000;j++);
}
