#include "config.h"
#include <stdio.h>

//****** Milad Samani - 962059895 ********
//***************************
int i,j,k;
unsigned char segment[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char select[4]={8,4,2,1};
unsigned char data[4];

void display(void){
j=i;
for(k=0;k<4;k++){
data[k]=j%10;
j=j/10;
}
for(k=0;k<12;k++)
for(j=0;j<4;j++){
IO0SET|=(segment[data[j]])<<4;
IO0SET|=(select[j]<<12);
delay_us(200);
IO0CLR=0xffffffff;
}
}

int main (void){
IO0DIR=0x0000fff0;
IO0CLR=0xffffffff;
while(1){
display();
i++;
if(i==10000) i=0;}
}

//****** Milad Samani - 962059895 ********
//***************************
