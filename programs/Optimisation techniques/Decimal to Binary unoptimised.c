//Decimal to binary by calculating during execution
#include<stdio.h>
int decimal_to_binary (int);
main()
{
    int binary;
    int lowerlimit=0,upperlimit=15;
    for(int i=lowerlimit;i<=upperlimit;i++)
    {
        binary=decimal_to_binary(i);
        printf("Decimal = %d\tBinary = %d \n",i,binary);
    }
}
int decimal_to_binary (int dec)
{
    int bin=0, p=1, rem;
    while(dec>0)          //or  d!=0
    {
        rem=dec%2;
        bin=bin+rem*p;
        dec=dec/2;
        p=p*10;
    }
    return (bin);
}
