/*
 * GccApplication1.c
 *
 * Created: 7/08/2026 5:15:52 pm
 * Author : disiz
 */ 

#include <avr/io.h>

int main(void)
{	
	volatile uint16_t primes[62];
	volatile uint16_t primeCount = 0;

	uint16_t number;
	uint16_t divisor;
	uint8_t isPrime;
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
	}
}

