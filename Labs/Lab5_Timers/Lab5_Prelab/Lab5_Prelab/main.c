/*
 * Lab5_Prelab.c
 *
 * Created: 22/09/2026 2:02:05 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	DDRC = 0x00;
	DDRD = 0x00;

	while (1)
	{
		PORTB |= (1 << PB2);
		_delay_ms(375);

		PORTB &= ~(1 << PB2);
		_delay_ms(125);
	}
}
