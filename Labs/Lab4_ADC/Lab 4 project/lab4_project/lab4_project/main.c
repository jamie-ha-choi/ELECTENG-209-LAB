/*
 * GccApplication2.c
 *
 * Created: 14/09/2026 2:06:40 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1 << PB5);
	DDRB &= ~(1 << PB7);

	while (1)
	{
		if (!(PINB & (1 << PB7)))
		{
			PORTB |= (1 << PB5);
		}
		else
		{
			PORTB &= ~(1 << PB5);
		}
	}
}


