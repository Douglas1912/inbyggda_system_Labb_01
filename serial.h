#ifndef SERIAL_H_
#define SERIAL_H_

void uart_init(unsigned int ubrr);

void uart_putchar(unsigned char chr);
void uart_putstr(const char *str);

char uart_getchar(void);

void uart_echo(void);

#endif

