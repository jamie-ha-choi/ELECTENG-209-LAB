/*
 * GccApplication2.c
 *
 * Created: 10/08/2026 2:13:15 pm
 * Author : disiz
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 2000000UL

void usart_init(uint16_t ubrr)
{
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    UCSR0B = (1 << TXEN0);
}

void usart_transmit(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = data;
}

int main(void)
{
    uint16_t number = 345;
    uint8_t hundreds;
    uint8_t tens;
    uint8_t ones;

    usart_init(12);

    while(1)
    {
        hundreds = number / 100;
        tens = (number / 10) % 10;
        ones = number % 10;

        usart_transmit(hundreds + 48);
        usart_transmit(tens + 48);
        usart_transmit(ones + 48);

        _delay_ms(500);
    }
}