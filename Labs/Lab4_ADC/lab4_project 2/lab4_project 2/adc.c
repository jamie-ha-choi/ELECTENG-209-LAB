/*
 * adc.c
 *
 * Created: 16/09/2026 4:52:47 pm
 * Author : disiz
 */ 

#include "common.h"
#include "adc.h"
#include <avr/io.h>

void adc_init(void)
{
	ADMUX = (1 << REFS0) | (1 << MUX1);

	ADCSRA = (1 << ADEN) | (1 << ADPS2);

	ADCSRB = 0;
}