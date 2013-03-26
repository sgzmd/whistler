#include <avr/io.h>
#include <util/delay.h>

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// #include <printf.h>

void yield() {}

int main(void)
{
    RF24 rf(1,2);

    DDRD = 1 << 4;           /* make the LED pin an output */
    for(;;){
        char i;
        for(i = 0; i < 10; i++){
            _delay_ms(30);  /* max is 262.14 ms / F_CPU in MHz */
        }
        PORTD ^= 1 << 4;    /* toggle the LED */
    }
    return 0;               /* never reached */
}
