#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include "led.h"

#define FOSC 16000000 // Clock Speed
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1

int main () {
    
    //blink_led();
    
    uart_init(MYUBRR);
    
    char str[]="Dogge!!\n\r";
    char d = 'D';
    
    while(1){
        
        //uart_putstr(str);
    	//uart_putchar(d);
    	uart_echo();
    	//_delay_ms(2000); 
   }
   
   return 0;

}
