#include<lpc213x.h>
#define R0  (1<<24)
#define R1	(1<<25)
#define R2	(1<<26)
#define R3	(1<<27)
#define C0	0X10000000//(1<<28)
#define C1	0X20000000//(1<<29)
#define C2	0X40000000//(1<<30)
#define C3	0X80000000//(1<<31)



unsigned char keypad_matrix[4][4]= {{'7','8','9','%'},
                                    {'4','5','6','*'},
									{'1','2','3','-'},
									{'A','0','=','+'}};

void keypad_init()
{
 //PINSEL2 = 0x00000000;// Selecting the GPIO function of port 1 from P1.16 to P1.31
 IODIR1 &= ~(C0|C1|C2|C3);// Take the columns as inputs
 IODIR1 |= (R0|R1|R2|R3);// Take the columns as outputs
}

unsigned char key_detect()
{
 keypad_init();
 while(1)
 {
  IOCLR1 = R0;
  IOSET1 = R1|R2|R3;
  if((IOPIN1 & C0) == 0)
  {
   while((IOPIN1 & C0) == 0);
   return keypad_matrix[0][0]; 
  }
  if((IOPIN1 & C1) == 0)
  {
   while((IOPIN1 & C1) == 0);
   return keypad_matrix[0][1]; 
  }
  if((IOPIN1 & C2) == 0)
  {
   while((IOPIN1 & C2) == 0);
   return keypad_matrix[0][2]; 
  }
  if((IOPIN1 & C3) == 0)
  {
   while((IOPIN1 & C3) == 0);
   return keypad_matrix[0][3]; 
  }
  IOCLR1 = R1;
  IOSET1 = R0|R2|R3;
  if((IOPIN1 & C0) == 0)
  {
   while((IOPIN1 & C0) == 0);
   return keypad_matrix[1][0]; 
  }
  if((IOPIN1 & C1) == 0)
  {
   while((IOPIN1 & C1) == 0);
   return keypad_matrix[1][1]; 
  }
  if((IOPIN1 & C2) == 0)
  {
   while((IOPIN1 & C2) == 0);
   return keypad_matrix[1][2]; 
  }
  if((IOPIN1 & C3) == 0)
  {
   while((IOPIN1 & C3) == 0);
   return keypad_matrix[1][3]; 
  }
  IOCLR1 = R2;
  IOSET1 = R1|R0|R3;
  if((IOPIN1 & C0) == 0)
  {
   while((IOPIN1 & C0) == 0);
   return keypad_matrix[2][0]; 
  }
  if((IOPIN1 & C1) == 0)
  {
   while((IOPIN1 & C1) == 0);
   return keypad_matrix[2][1]; 
  }
  if((IOPIN1 & C2) == 0)
  {
   while((IOPIN1 & C2) == 0);
   return keypad_matrix[2][2]; 
  }
  if((IOPIN1 & C3) == 0)
  {
   while((IOPIN1 & C3) == 0);
   return keypad_matrix[2][3]; 
  }
  IOCLR1 = R3;
  IOSET1 = R0|R1|R2;
  if((IOPIN1 & C0) == 0)
  {
   while((IOPIN1 & C0) == 0);
   return keypad_matrix[3][0]; 
  }
  if((IOPIN1 & C1) == 0)
  {
   while((IOPIN1 & C1) == 0);
   return keypad_matrix[3][1]; 
  }
  if((IOPIN1 & C2) == 0)
  {
   while((IOPIN1 & C2) == 0);
   return keypad_matrix[3][2]; 
  }
  if((IOPIN1 & C3) == 0)
  {
   while((IOPIN1 & C3) == 0);
   return keypad_matrix[3][3]; 
  }
 }
}
