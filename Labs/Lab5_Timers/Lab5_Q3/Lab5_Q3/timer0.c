#include "timer0.h"
#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

ISR(TIMER0_COMPA_vect)
{
	static uint8_t count = 0;

	count++;

	if (count >= 10) // legit just doing the same thing 10 times so its 100 
	{
		led_toggle();
		count = 0;
	}
}

void timer0_init()
{
	TCCR0A = (1 << WGM01);   // CTC mode
	TCCR0B = (1 << CS02);    // prescaler = 256
	OCR0A = 77;              // compare every 9.984 ms

	TIMSK0 |= (1 << OCIE0A); // enable Timer0 Compare A interrupt
}