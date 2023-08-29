#include<stdio.h>
const char *bin[]=
{
   "0000","0001","0010","0011","0100","0101","0110","0111",
   "1000","1001","1010","1011","1100","1101","1110","1111"
};
void display(int max)
{
    int i;
    for(i=0;i<max;i++)
    {
        printf("Decimal = %d\tBinary = %s \n",i,bin[i]);
    }
}
int main()
{
    int max=sizeof(bin)/sizeof(char *);
    display(max);
}
