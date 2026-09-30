/*
 * Lab6_real.c
 *
 * Created: 30/09/2026 1:50:02 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// global counter
volatile uint8_t counter = 0;

//display functions
void init_display(void);
void timer0_init(void);

int main(void)
{
	// setup display
	init_display();
    
	// interrupt every 10ms
	timer0_init();
	
	while (1)
	{
		_delay_ms(1000);

		counter++;

		// after 99 go back to 0
		if (counter > 99)
		{
			counter = 0;
		}
	}
}
