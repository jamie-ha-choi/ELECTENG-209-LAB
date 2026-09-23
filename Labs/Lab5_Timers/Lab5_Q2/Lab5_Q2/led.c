/*
 * led.c
 *
 * Created: 23/09/2026 4:03:00 pm
 * Author : disiz
 */ 

#include "led.h"
#include <avr/io.h>

void led_toggle()
{
	PORTB ^= (1 << PB5);
}