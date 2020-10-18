#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"


void uart_init(unsigned int ubrr){
    
    /*Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    //Enable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    
    // Set frame format to 8 data bits, no parity, 1 stop bit
    UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);

}

void uart_putchar(unsigned char data){
    //wait while previous byte is completed /* Wait for empty transmit buffer       */
    while((UCSR0A & (1<<UDRE0)) == 0);
    // Transmit data /* Put data into buffer, sends the data */
    
    if(data == '\n'){
            UDR0 = '\r';
    }
    else
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

void uart_echo(void){}

