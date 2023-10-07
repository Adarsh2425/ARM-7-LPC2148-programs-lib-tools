#include <LPC214x.h>

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 1000; j++);
}

int main(void) {
    // Configure P0.10 as an output pin for the buzzer
    IO0DIR |= (1 << 10);

    while (1) {
        // Turn ON the buzzer (set P0.10 HIGH)
        IO0SET |= (1 << 10);
        delay_ms(1000); // Delay for 1 second
        
        // Turn OFF the buzzer (set P0.10 LOW)
        IO0CLR |= (1 << 10);
        delay_ms(1000); // Delay for 1 second
    }
}