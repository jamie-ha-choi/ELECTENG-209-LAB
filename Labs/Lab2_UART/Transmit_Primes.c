/*
 * GccApplication2.c
 *
 * Created: 10/08/2026 2:13:15 pm
 * Author : disiz
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#define F_CPU 2000000UL

void usart_init(uint16_t ubrr)
{
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << TXEN0);
}

void usart_transmit(uint8_t data)
{
    while (!(UCSR0A & (1 << UDRE0)))
    {
    }

    UDR0 = data;
}

int main(void)
{
    uint16_t primes[62];
    uint8_t primeCount = 0;
    uint16_t number;
    uint16_t divisor;
    uint8_t isPrime;

    uint8_t i;
    uint16_t currentPrime;
    uint8_t hundreds;
    uint8_t tens;
    uint8_t ones;

    usart_init(12);

    for (number = 2; number <= 300; number++)
	{
		isPrime = 1;
		for (divisor = 2; divisor < number; divisor++)
		{
			if (number % divisor == 0)
			{
				isPrime = 0;
				break;
			}
		}
		if (isPrime)
		{
			primes[primeCount] = number;
			primeCount++;
		}
	}

    while (1)
    {
        for (i = 0; i < primeCount; i++)
        {
            currentPrime = primes[i];

            hundreds = currentPrime / 100;
            tens = (currentPrime / 10) % 10;
            ones = currentPrime % 10;

            usart_transmit(hundreds + 48);
            usart_transmit(tens + 48);
            usart_transmit(ones + 48);

            usart_transmit(',');
            usart_transmit(' ');
			_delay_ms(500);
        }
    }
}