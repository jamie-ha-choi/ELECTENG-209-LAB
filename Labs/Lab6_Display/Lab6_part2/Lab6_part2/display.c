#include "display.h"
#include <avr/io.h>


// Segment patterns for 0-9
// bit 7 = dp, bit 6 = g, ... bit 0 = a
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


// Segment patterns currently waiting to be displayed
// [0] = ones
// [1] = tens
// [2] = hundreds
// [3] = thousands
static volatile uint8_t disp_characters[4] = {0, 0, 0, 0};


// Which digit will be displayed next
static volatile uint8_t disp_position = 0;



void init_display(void)
{
	// PC3 = SH_CP
	// PC4 = SH_DS
	// PC5 = SH_ST
	DDRC |= (1 << PC3) | (1 << PC4) | (1 << PC5);

	// PD4 = Ds1
	// PD5 = Ds2
	// PD6 = Ds3
	// PD7 = Ds4
	DDRD |= (1 << PD4) | (1 << PD5) |
	(1 << PD6) | (1 << PD7);

	// Start shift register control signals LOW
	PORTC &= ~((1 << PC3) | (1 << PC4) | (1 << PC5));

	// Disable all four digits initially
	PORTD |= (1 << PD4) | (1 << PD5) |
	(1 << PD6) | (1 << PD7);
}



void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos)
{
	// Separate the four digits
	uint8_t ones      = number % 10;
	uint8_t tens      = (number / 10) % 10;
	uint8_t hundreds  = (number / 100) % 10;
	uint8_t thousands = (number / 1000) % 10;

	// Convert each digit into its 7-segment pattern
	disp_characters[0] = seg_pattern[ones];
	disp_characters[1] = seg_pattern[tens];
	disp_characters[2] = seg_pattern[hundreds];
	disp_characters[3] = seg_pattern[thousands];

	// Decimal point isn't needed for Q2.3
	(void)decimal_pos;
}



void send_next_character_to_display(void)
{
	// Get the pattern for the digit we're currently displaying
	uint8_t character = disp_characters[disp_position];

	// Make sure clock is LOW
	PORTC &= ~(1 << PC3);

	// Send all 8 bits MSB first
	for (uint8_t mask = 0x80; mask != 0; mask >>= 1)
	{
		// Put current bit onto SH_DS
		if (character & mask)
		{
			PORTC |= (1 << PC4);      // SH_DS = 1
		}
		else
		{
			PORTC &= ~(1 << PC4);     // SH_DS = 0
		}

		// Pulse SH_CP to shift current bit in
		PORTC |= (1 << PC3);
		PORTC &= ~(1 << PC3);
	}


	// Disable ALL digits before changing displayed pattern
	PORTD |= (1 << PD4) | (1 << PD5) |
	(1 << PD6) | (1 << PD7);


	// Latch shift register data onto outputs
	PORTC |= (1 << PC5);
	PORTC &= ~(1 << PC5);


	// Enable the correct digit
	switch (disp_position)
	{
		case 0:
		PORTD &= ~(1 << PD7);     // Ds4 = ones
		break;

		case 1:
		PORTD &= ~(1 << PD6);     // Ds3 = tens
		break;

		case 2:
		PORTD &= ~(1 << PD5);     // Ds2 = hundreds
		break;

		case 3:
		PORTD &= ~(1 << PD4);     // Ds1 = thousands
		break;
	}


	// Move to next digit
	disp_position++;

	if (disp_position > 3)
	{
		disp_position = 0;
	}
}