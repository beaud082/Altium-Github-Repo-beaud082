#ifndef DMX_CONFIGS_H
#define DMX_CONFIGS_H

#include <avr/io.h>

// Configurations for USART 1
#define DMX_RX_VECT USART1_RX_vect
#define DMX_TX_VECT USART1_TX_vect
#define DMX_UDR UDR1
#define DMX_UBRRH UBRR1H
#define DMX_UBRRL UBRR1L
#define DMX_UCSRA UCSR1A
#define DMX_UCSRB UCSR1B
#define DMX_TXEN TXEN1
#define DMX_TXCIE TXCIE1
#define DMX_RXEN RXEN1
#define DMX_RXCIE RXCIE1
#define DMX_FE FE1
#define DMX_RX_PIN 19
#define DMX_TX_PIN 18
#define DMX_OE_PIN 17

#ifndef F_CPU
#define F_CPU 16000000
#endif
#define DMX_BREAK_BAUD 49950 // For value of 176 uS
#define DMX_BAUD_RATE 250000

#define SET_BAUD(baud) \
do { \
        DMX_UBRRH = (unsigned char)(((F_CPU + baud * 8L) / (baud * 16L) - 1)>>8); \
        DMX_UBRRL = (unsigned char) ((F_CPU + baud * 8L) / (baud * 16L) - 1); \
} while (0);

#endif // DMX_CONFIGS_H
