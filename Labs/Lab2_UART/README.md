    <img src="https://github.com/ee209-2020class/ee209-2020class.github.io/blob/master/ExtraInfo/logo.png">

# Lab 3 Notes

Keep a digital log of your work using the readme file where appropriate.

# Digital log:

# Q 1.1: What is the purpose of each of the following parameters and bits?
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
