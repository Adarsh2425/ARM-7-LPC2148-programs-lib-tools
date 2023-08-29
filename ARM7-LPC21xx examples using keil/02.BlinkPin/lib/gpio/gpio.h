#ifndef GPIO_H_
#define GPIO_H_

#define INPUT 0
#define OUTPUT 1
    
#define HIGH 1
#define LOW 0

#define SET 1
#define CLR 0


void gpio_pin_mode(unsigned char pin,unsigned char mode);
void gpio_pin_write(unsigned char pin,unsigned char bit_val);
unsigned char gpio_pin_read(unsigned char pin);


#endif
