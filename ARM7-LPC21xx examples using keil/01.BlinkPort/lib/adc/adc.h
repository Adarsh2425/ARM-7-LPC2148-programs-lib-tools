
#ifndef ADC_H_
#define ADC_H_
#include <stdint.h>

void adc0_init(void);
uint16_t adc0_read(unsigned char ch);

#endif
