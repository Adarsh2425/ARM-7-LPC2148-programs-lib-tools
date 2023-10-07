#include "config.h"
//****** Milad Samani - 962059895 ********
unsigned char start, flag, i;
int main (void){
IO0DIR |=(0xFF<<8);
IO0CLR |=(0xFF<<8);
while(1){
if(((IO1PIN & (1<<26))==0) && (flag==0)){
flag=1;
start =!start;
IO0CLR |= (0xFF<<8);
i=0;}
else if ((IO1PIN & (1<<26))==0)flag=0;
if (start){
IO0SET |= (1<<(i+8));
i++;
if(i==9){
IO0CLR |=(0xFF<<8);
i=0;}
delay_ms(100);}
else if(!start){
IO0SET |=(1<<(i+8));
delay_ms(100);
IO0CLR |=(1<<(i+8));
i++;
if(i==9){
IO0CLR |= (0xFF<<8);
i=0;}}}}
//****** Milad Samani - 962059895 ********


