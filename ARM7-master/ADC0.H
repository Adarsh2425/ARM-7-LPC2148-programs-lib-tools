void adc0_init(void)
{
 // Enable ADC0
 AD0CR &= 0x00000000;		// Clear All Bit Control
 AD0CR |= 0x00000400;		// ADC Clock = VPB(PCLK) / 8
 AD0CR &= 0xFFFEFFFF;		// Busrt = 0			- Conversions are software controlled and reguire 11 clocks
 AD0CR &= 0xFFF1FFFF;		// CLKS  = 000		- 10Bit : 11 Cycle Clock Conversion
 AD0CR |= 0x00200000;		// PDN   = 1			- Active ADC Module
}


unsigned int adc0_channel_1(void)
{
 unsigned int	val;
 // Initial AD0.1 (P0.28) By Set PINSEL1[25:24=01] 
 // xxxx xx01 xxxx xxxx xxxx xxxx xxxx xxxx
 PINSEL1 |= 0x01000000;	   //  channel 0 in adc0

 AD0CR &= 0xffffff00;
 AD0CR |= 0x00000002;		// Select ADC = AD0.1  
  // START = 001 = Start Conversion Now
 AD0CR |= 0x01000000;
 // Wait ADC Conversion to Complete and Read A/D Data Register
 
 while((AD0DR1 & 0x80000000) == 0);
 // Shift ADC Result to Integer
 val = (unsigned int)(AD0DR1 >> 6) & 0x000003FF;
 AD0CR &= 0xF8FFFFFF;	    //STOP THE ADC
 return (val);
}

unsigned int adc0_channel_2(void)
{
 unsigned int	val1;
 // Initial AD0.2 (P0.29) By Set PINSEL1[27:26=01] 
 // xxxx 01xx xxxx xxxx xxxx xxxx xxxx xxxx
 PINSEL1 |= 0x04000000;	   //  channel 1 in adc0

 AD0CR &= 0xffffff00;
 AD0CR |= 0x00000004;		// Select ADC = AD0.2  
  // START = 001 = Start Conversion Now
 AD0CR |= 0x01000000;
 // Wait ADC Conversion to Complete and Read A/D Data Register
 
 while((AD0DR2 & 0x80000000) == 0);
 // Shift ADC Result to Integer
 val1 = (unsigned int)(AD0DR2 >> 6) & 0x000003FF;
 AD0CR &= 0xF8FFFFFF;	    //STOP THE ADC
 return (val1);
}
