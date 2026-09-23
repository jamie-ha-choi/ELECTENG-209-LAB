/*
 * Lab5_Q3.c
 *
 * Created: 23/09/2026 4:24:02 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL

#include "timer0.h"
#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= (1 << DDB5);   // PB5 output for LED

	timer0_init();

	sei();                 // enable global interrupts

	while (1)
	{
	}
}

