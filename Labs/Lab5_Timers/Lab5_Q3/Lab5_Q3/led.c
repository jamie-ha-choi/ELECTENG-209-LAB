#include "led.h"
#include <avr/io.h>

void led_toggle()
{
	PORTB ^= (1 << PB5);
}