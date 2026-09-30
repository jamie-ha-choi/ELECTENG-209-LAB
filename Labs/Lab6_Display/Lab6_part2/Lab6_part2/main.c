/*
 * Lab6_part2.c
 *
 * Created: 30/09/2026 2:53:23 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "display.h"


void timer0_init(void)
{
	// ctc
	TCCR0A = (1 << WGM01);

	// 256 prescaler
	TCCR0B = (1 << CS02);

	// about 10 ms
	OCR0A = 77;

	// enable timer0 interrupt
	TIMSK0 |= (1 << OCIE0A);

	// enable global interrupts
	sei();
}


// called approximately every 10 ms
ISR(TIMER0_COMPA_vect)
{
	send_next_character_to_display();
}


int main(void)
{
	uint16_t counter = 0;

	// set up display
	init_display();

	// set up 10 ms Timer0 interrupt
	timer0_init();


	while (1)
	{
		// convert current counter into 4 display characters
		seperate_and_load_characters(counter, 255);

		// hold value for 400 ms
		_delay_ms(400);

		counter++;

		// 9999 -> 0
		if (counter > 9999)
		{
			counter = 0;
		}
	}
}

