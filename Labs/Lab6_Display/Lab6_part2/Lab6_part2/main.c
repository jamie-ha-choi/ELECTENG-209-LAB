/*
 * Lab6_part2.c
 *
 * Created: 30/09/2026 2:53:23 pm
 * Author : disiz
 */ 

#include <avr/io.h>
#include <stdint.h>

void init_display(void)
{
	// SH_CP, SH_DS, SH_ST outputs
	DDRC |= (1 << PC3) | (1 << PC4) | (1 << PC5);

	// Ds1-Ds4 outputs
	DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD6) | (1 << PD7);

	// SH_CP and SH_ST initially LOW
	PORTC &= ~((1 << PC3) | (1 << PC5));

	// Ds1-Ds3 OFF
	PORTD |= (1 << PD4) | (1 << PD5) | (1 << PD6);

	// Ds4 ON
	PORTD &= ~(1 << PD7);
}


void send_next_character_to_display(void)
{
	uint8_t character = 0x07;

	PORTC &= ~(1 << PC3);   // SH_CP LOW
	PORTC &= ~(1 << PC5);   // SH_ST LOW

	for (int8_t i = 7; i >= 0; i--)
	{
		if (character & (1 << i))
		{
			PORTC |= (1 << PC4);
		}
		else
		{
			PORTC &= ~(1 << PC4);
		}

		// Shift current bit in
		PORTC |= (1 << PC3);
		PORTC &= ~(1 << PC3);
	}

	// Latch outputs
	PORTC |= (1 << PC5);
	PORTC &= ~(1 << PC5);
}


int main(void)
{
	init_display();

	send_next_character_to_display();

	while (1)
	{
	}
}

