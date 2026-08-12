    <img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Lab 3 Notes

Keep a digital log of your work using the readme file where appropriate.

# Digital log:

# Q1.1: What is the purpose of each of the following parameters and bits?
i) The start bit: initiates the reciever to alert that a new data frame is beginning
ii) The parity bit: Error detection 
iii) The stop bits: alerts the end of a data frame 
iv) The baud rate: rate of bits transmission per second

# Q2.1 USART Settings
| 1. Setting Name | 2. Register and Bits | 3. Purpose | 4. Do we need it? | 5. Initialisation / Runtime |
|---|---|---|---|---|
| 1. Receive Complete | 2. UCSR0A, RXC0 (Bit 7) | 3. Flag indicating that a complete packet has been received and is ready to be read | 4. No | 5. - |
    | 1. Tx Data Register Empty | 2. UCSR0A, UDRE0 (Bit 5) | 3. Flag indicating that the transmit register is ready for new data | 4. Yes | 5. Runtime |
    | 1. Transmit Complete | 2. UCSR0A, TXC0 (Bit 6) | 3. Flag indicating that the entire transmission has finished | 4. No | 5. - |
| 1. Mode Selection | 2. UCSR0C, UMSEL0[1:0] (Bits 7:6) | 3. Selects asynchronous, synchronous, or SPI mode | 4. Yes | 5. Initialisation |
| 1. Character Size | 2. UCSR0B, UCSZ02 (Bit 2) and UCSR0C, UCSZ01:0 (Bits 2:1) | 3. Selects the number of data bits in each UART frame | 4. Yes | 5. Initialisation |
| 1. Clock Polarity | 2. UCSR0C, UCPOL0 (Bit 0) | 3. Sets the clock polarity when using synchronous USART | 4. No | 5. - |
| 1. Baud Rate | 2. UBRR0H and UBRR0L, UBRR0[11:0] | 3. Sets the UART transmission rate using the system clock | 4. Yes | 5. Initialisation |
| 1. Receiver Enable | 2. UCSR0B, RXEN0 (Bit 4) | 3. Enables the USART receiver | 4. No | 5. - |
| 1. Transmitter Enable | 2. UCSR0B, TXEN0 (Bit 3) | 3. Enables the USART transmitter | 4. Yes | 5. Initialisation |
| 1. Parity Mode | 2. UCSR0C, UPM0[1:0] (Bits 5:4) | 3. Selects whether parity is disabled, even, or odd | 4. Yes | 5. Initialisation |
| 1. Parity Error | 2. UCSR0A, UPE0 (Bit 2) | 3. Indicates that received data has a parity error | 4. No | 5. - |


# Meeting: Mon, 10th Aug, 2026, 1:00 pm 
# Objective: Complete lab work before our 12/08 lab
# Start time: 1:10 pm
# Notes: 

# Q2.2: Using the datasheet, what is the appropriate UBRR value? Note that our system clock is 2MHz.
UBRR = (fosc / 16 * Baud rate) - 1 
     = (2000000 / 16 x 9600) - 1 = 12.02 ≈ 12


# Q2.3: On the ATmega328P, the UBRR is divided up between two registers,
# UBRR0H and UBRR0L. Why do you think this is the case?
Because the ATmega328P has 8-bit registers, but the UBRR value can be larger than 8 bits. 
Therefore, it is split between UBRR0H (high bits) and UBRR0L (low bits).

# Q2.4
See Q2.4 Table.jpg

# Q2.5: For each of these instructions, finish the C macro expression:
i) Test if the UDRE0 bit is 1:          if( UCSR0A & (1 << UDRE0 )) {
ii) Write a 1 (set) to the TXEN0 bit:       UCSR0B |= (1 << TXEN0);
iii) Write a 0 (clear) to the UCPOL0 bit:   UCSR0C &= ~(1 << UCPOL0);}

# Q3.1: On the ATmega328P, how many bits of data can be stored in a variable of
# each of these types:
char: 8 bits    uint8_t: 8 bits
int: 16 bits    uint16_t: 16 bits
int8_t: 8 bits  float: 32 bits

# Q3.2: What is the size of the UDR0 register? 
8 bits

# Q3.3: What is the largest number we can transmit? 
2^8 - 1 = 255

# Q3.4: What decimal numbers correspond to the word “HELLO”?
HELLO = 72, 69, 76, 76, 79

# Q3.5: Fill in the blanks below to describe how to send a number to a terminal:
We can extract the individual digits of a number by using the modulo
operator. Then we encode an individual digit into its ASCII equivalent by simply
adding the decimal number 48. Then we iterate through each digit of the
number using a loop, writing each character to the UDR0 register.

# Pseudo Code for Pre-Lab

- You can use a simple algorithm that iterates through all the numbers up to 300, and checks if they can be exactly divided by numbers smaller than it using the modulo operator
- Here is an example algorithm you could use
> - Create an array that could store 62 numbers (note the variable type should allow storing integers up to 300)
> - Create a variable *i* to hold the position in the array where you will store next prime number and initialize this to 0
> - Create a variable *N* to hold the number we are going to check and see if it is a prime number (note the variable type should allow storing integers up to 300)
> - Create a counter variable *j* to iterate through numbers up to the number we want to check if it is a prime number (note the variable type should allow storing integers up to 300)
> - Create a variable *isPrime* that can be used as a flag to indicate its a prime number
> - In a 1st *for loop* increment *N* from 2 to 300 and within this loop
>   - Set the flag *isPrime*
>   - In a 2nd *for loop* increment *j* from 2 to N-1 and within this loop
>   - If *N % j* is 0 then *N* is not a prime number so clear *isPrime* and *break* the *for loop*
>   - If *isPrime* is set at the end of 2nd *for loop* then store *N* in the *i* position of the array and increment *i*
> - Continue with the 1st *for loop* until N reach 300 
