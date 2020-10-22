#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"
#include <string.h>
#include <stdbool.h> 

char rc;
const int numChars = 5;
char receivedChars[5];
int num = 0;


void uart_init(unsigned int ubrr){
    
    /*Set USART baud rate for the 8bit registers 
	UBRR0H Loads upper 8-bits of the baud rate value into the high byte of the UBRR register
	UBRR0L Loads lower 8-bits of the baud rate value into the low byte of the UBRR register*/
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    //Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    UCSR0C = 0
    | (0<<UMSEL01) | (0<<UMSEL00)   // Asynchronous USART
    | (0<<UPM01) | (0<<UPM00)       // Parity Disabled
    | (0<<USBS0)                    // 1 stop bit
    | (1<<UCSZ01) | (1<<UCSZ00)     // 8-bit character size
	;
     

}

void uart_putchar(unsigned char data){ 
    
    if(data == '\n'){
		//wait while previous byte is completed /* Wait for empty transmit buffer       */
		while((UCSR0A & (1<<UDRE0)) == 0);
		UDR0 = '\r';
    }
	while((UCSR0A & (1<<UDRE0)) == 0);
	// Transmit data /* Put data into buffer, sends the data */
	UDR0 = data;
}

void uart_putstr(const char *str){
    
    while(*str != 0){
		uart_putchar(*str);
		str++; 
    } 
}

char uart_getchar(void){
    
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

void uart_echo(void){

    char c;
    
    while(1){

        c = uart_getchar();
        uart_putchar('[');
    	uart_putchar(c);
    	uart_putchar(']');    	
    	}
}


void uart_led() {

    // Sets Arduino digital pin 11 (pin 3 of PORTB) for output
    DDRB |= 0B001000; // PORTB3


    while (1) {
		//Gets the next char in the buffer	
        rc = uart_getchar();

        if (rc != '\r' && rc != '\n') {

            receivedChars[num] = rc;
            num++;
			
			//to not exceed the max limited char in the array overwrite the last one
            if (num >= numChars) {
                num = numChars - 1;
            }
        }

        else {		
			// puts Null char after finding Carriage retur \r and New Line \n
            receivedChars[num] = '\0';
            num = 0;
			
			ledOnOff();
        }
    }
}

void ledOnOff(void){
	
	char ledOn[3] = "on";
    char ledOff[4] = "off";
	
	////Compares the inputed string 
	if (strcmp(receivedChars, ledOn) == 0) {
		//Arduino digital pin 11 (pin 3 of PORTB) for HIGH
		PORTB |= 0B001000;
		UDR0 = 'o';
		UDR0 = 'n';
		}
		if (strcmp(receivedChars, ledOff) == 0) {
			//Arduino digital pin 11 (pin 3 of PORTB) for LOW
			PORTB &= ~0B001000;
			UDR0 = 'o';
			UDR0 = 'f';
			_delay_ms(10);
			UDR0 = 'f';
			}
}
