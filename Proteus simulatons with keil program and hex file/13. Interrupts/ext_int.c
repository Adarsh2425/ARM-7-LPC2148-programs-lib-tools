#include <LPC214x.H>  
void delay(int count);
void init_ext_interrupt(void);
__irq void Ext_ISR(void);
int main (void) 
{
  init_ext_interrupt();   // initialize the external interrupt
  
  while (1)  
  {        
  }
}
void init_ext_interrupt()  //Initialize Interrupt
{
  EXTMODE = 0x4;           //Edge sensitive mode on EINT2
  
  EXTPOLAR &= ~(0x4);        //Falling Edge Sensitive
  PINSEL0 = 0x80000000;    //Select Pin function P0.15 as EINT2
  
  /* initialize the interrupt vector */
  VICIntSelect &= ~ (1<<16);            // EINT2 selected as IRQ 16
  VICVectAddr5 = (unsigned int)Ext_ISR; // address of the ISR
  VICVectCntl5 = (1<<5) | 16;            // 
  VICIntEnable = (1<<16);               // EINT2 interrupt enabled
  EXTINT &= ~(0x4);    
}
__irq void Ext_ISR(void) // Interrupt Service Routine-ISR 
{
 IO1DIR |= (1<<25);
 IO1CLR |= (1<<25);      // Turn ON Buzzer
 delay(100000);
 IO1SET |= (1<<25);      // Turn OFF Buzzer
 EXTINT |= 0x4;          //clear interrupt
 VICVectAddr = 0;      // End of interrupt execution
}
void delay(int count)
{
  int j=0,i=0;
  for(j=0;j<count;j++)
  {
    /* At 60Mhz, the below loop introduces
    delay of 10 us */
    for(i=0;i<35;i++);
  }
}