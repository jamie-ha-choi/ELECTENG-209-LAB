/*
 * Lab5_Q4.c
 *
 * Created: 23/09/2026 4:39:37 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

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
	uint8_t ticks;

	uint16_t frequency;
	uint8_t hundreds;
	uint8_t tens;
	uint8_t ones;

	usart_init(12);

	DDRD &= ~(1 << DDD2);     // PD2 / INT0 input

	while (1)
	{
		// wait until int0 is low
		while (PIND & (1 << PD2));

		// wait for rising edge
		while (!(PIND & (1 << PD2)));

		// reset and start timer0
		TCNT0 = 0;
		TCCR0A = 0;
		TCCR0B = (1 << CS02);     // 256 prescaler

		// wait for falling edge
		while (PIND & (1 << PD2));

		// stop timer0
		TCCR0B = 0;

		ticks = TCNT0;

		// calc frequency
		frequency = 2000000UL / (2UL * 256UL * ticks);

		// split f into digits
		hundreds = frequency / 100;
		tens = (frequency / 10) % 10;
		ones = frequency % 10;

		// print
		usart_transmit(hundreds + 48);
		usart_transmit(tens + 48);
		usart_transmit(ones + 48);

		usart_transmit('\r');
		usart_transmit('\n');

		_delay_ms(500);
	}
}