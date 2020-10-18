#include <avr/io.h>
#include <util/delay.h>

#include "led.h"

#define BLINK_DELAY_MS 500


void blink_led (void)
{
    
    // Arduino digital pin 11 (pin 3 of PORTB) for output
    DDRB |= 0B001000; // PORTB3
    
    while(1) {
    
    	// turn LED on
        PORTB |= 0B001000; // PORTB3
    	_delay_ms(BLINK_DELAY_MS);
    
    	// turn LED off
    	PORTB &= ~ 0B001000; // PORTB3
    	_delay_ms(BLINK_DELAY_MS);
  }
}
