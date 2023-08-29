//Linear search
#include<stdio.h>
void linear_search(int array[],int n,int key)
{
    int flag=0;
    for(int i=0;i<n;i++)
    {
        printf("iteration number: %d\n",i);
        if(array[i]==key)
        {
            printf("%d found at index %d\n",key,i);
            flag=1;
        }
    }
    if(flag==0)
	    printf("%d is not present in the array\n",key);
}
void main()
{
    int array[]={3,5,7,1,6,8,4,2,9};
    int n=sizeof(array)/sizeof(array[0]);
    int key=4;
    linear_search(array,n,key);
}
