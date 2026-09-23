/*
 * Lab5_Q2.c
 *
 * Created: 23/09/2026 4:02:15 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL

#include "timer0.h"
#include "led.h"
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= (1 << DDB5);   // PB5 output for LED

	timer0_init();

	while (1)
	{
		if (timer0_check_clear_compare())
		{
			led_toggle();
		}
	}
}
