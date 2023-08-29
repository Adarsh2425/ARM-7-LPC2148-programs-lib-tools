#ifndef EXTINT_H_
#define EXTINT_H_

#define EINT0_SEL	PINSEL1|=0x00000001		//P0.16
//#define EINT0_SEL	PINSEL0|=0x0000000C	//P0.1
#define EINT1_SEL	PINSEL0|=0x20000000		//P0.14
//#define EINT1_SEL	PINSEL0|=0x000000C0	//P0.3
#define EINT2_SEL	PINSEL0|=0x80000000		//P0.15
//#define EINT2_SEL	PINSEL0|=0x0000C000	//P0.7			
#define EINT3_SEL	PINSEL1|=0x00000300		//P0.20
//#define EINT3_SEL	PINSEL1|=0x30000000	//P0.30
//#define EINT3_SEL	PINSEL0|=0x000C0000	//P0.9

#define EDGE					1
#define RISING_EDGE		1
#define FALLING_EDGE	0

#define LEVEL					0
#define HIGH_LEVEL		1
#define LOW_LEVEL			0
	
#define EINT0		0x00000001
#define EINT1		0x00000002
#define EINT2		0x00000004
#define EINT3		0x00000008

uint8_t EINT_init(uint32_t intt,uint32_t mode,uint32_t polar,void *fun);

#endif
