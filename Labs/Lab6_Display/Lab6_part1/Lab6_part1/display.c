#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>


// ccounter is in main.c but extern to use it here
extern volatile uint8_t counter;


const uint8_t seg_pattern[10] =
{
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


// which digit is displayed next
static volatile uint8_t digit_select = 0;

void init_display(void)
{
	DDRC |= 0b00111111;

	DDRB |= (1 << PB0) | (1 << PB1) | (1 << PB4);

	PORTB |= (1 << PB0) | (1 << PB1);
}

void timer0_init(void)
{
	// ctc
	TCCR0A |= (1 << WGM01);

	// 256 prescaler
	TCCR0B |= (1 << CS02);

	// 78 counts for 10 ms
	OCR0A = 77;

	// enables timer0 compare interrupt
	TIMSK0 |= (1 << OCIE0A);
	
	// enables global interrupts
	sei();
}

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

ISR(TIMER0_COMPA_vect)
{
	uint8_t tens;
	uint8_t ones;

	// separate the number
	tens = counter / 10;
	ones = counter % 10;


	// disable both digits before changing segments
	PORTB |= (1 << PB0) | (1 << PB1);


	if (digit_select == 0)
	{
		// display tens digit on Ds1
		display_digit(tens);

		// Ds1 = 0 means on 
		PORTB &= ~(1 << PB0);

		// display Ds2 next time
		digit_select = 1;
	}
	else
	{
		// display ones digit on Ds2
		display_digit(ones);

		// Ds2 = 0
		PORTB &= ~(1 << PB1);

		// display Ds1 next time
		digit_select = 0;
	}
}