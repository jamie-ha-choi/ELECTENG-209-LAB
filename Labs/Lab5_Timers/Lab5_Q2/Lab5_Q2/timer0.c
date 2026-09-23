/*
 * timer0.c
 *
 * Created: 23/09/2026 4:02:30 pm
 * Author : disiz
 */ 

#include "timer0.h"
#include "led.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void timer0_init()
{
	TCCR0A = (1 << WGM01);  // CTC mode
	TCCR0B = (1 << CS02);   // prescaler = 256
	OCR0A = 77;             // compare every 9.984 ms
}

uint8_t timer0_check_clear_compare()
{
	if (TIFR0 & (1 << OCF0A))
	{
		TIFR0 = (1 << OCF0A);   // write 1 to clear flag
		return 1;
	}

	return 0;
}