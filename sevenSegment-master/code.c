#include 
//****** Milad Samani - 962059895 ********
int i=0, l ,k;
unsigned char segment[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
int main (void){
pll_init(5,2);
IO0DIR=0x000007f0;
IO0CLR=0x000007f0;
while(1){
IO0SET |= (segment[i])<<4;
delay_ms(100);
IO0CLR |= (segment[i])<<4;
i++;
if(i==10)i=0;}
}
//****** Milad Samani - 962059895 ********

