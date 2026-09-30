/*
 * Lab6_Prelab.c
 *
 * Created: 30/09/2026 12:25:28 pm
 * Author : disiz
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
    
uint8_t seg_pattern[10] = {
	0x3F,   // 0
	0x06,   // 1
	0x5B,   // 2
	0x4F,   // 3
	0x66,   // 4
	0x6D,   // 5
	0x7D,   // 6
	0x07,   // 7
	0x7F,   // 8
	0x6F    // 9
};

// Function due to g being in a different port 
void display_digit(uint8_t digit)
{
	uint8_t pattern = seg_pattern[digit];

	PORTC = (PORTC & ~0x3F) | (pattern & 0x3F);

	if (pattern & (1 << 6))
	{
		PORTB |= (1 << PB4);
	}
	else
	{
		PORTB &= ~(1 << PB4);
	}
}



int main(void)
{
	DDRC |= 0b00111111;
	
	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB4);
	DDRB &= ~(1 << PB7);
	
	PORTB |= (1 << PB0);
	PORTB &= ~(1 << PB1);
	
	
	uint8_t counter = 0;
	
    while (1) 
    {
		display_digit(counter);
    }
}

