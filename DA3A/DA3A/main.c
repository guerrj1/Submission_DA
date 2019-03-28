//DA3A

#define F_CPU 16000000UL
#define BAUD 9600
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/interrupt.h>

//Function Declarations
void USART_send(char data);
void USART_putstring(char* StringPtr);
void USART_init(void);

char String[] = "Hello World!";  //holds the array of characters
char outs[20];  //number of character spaces
//char integer[] = "8";
volatile float float_val = 3.14159265;  //floating point value 

int main(void)
{
	TCCR1B = 5;           //sets the prescaler to 1024
	TIMSK1 = (1<<TOIE1);  //enables overflow interrupt
	TCNT1 = 49911;        //TCNT1 value the counter counts up to 
	
	USART_init();
	sei();                //enables the interrupt 
	
	while(1)
	{
	}
}

//interrupt 
ISR (TIMER1_OVF_vect)
{
	USART_putstring(String);         //sends the string to the terminal
	USART_putstring("\n");           //line feed 
	USART_send('5');                 //sends the value to the terminal 
	snprintf(outs, sizeof(outs), "%f\r\n", float_val);  //prints the floating point value 
	USART_putstring("\n");           //line feed
	USART_putstring(outs);           //sends the number of spaces 
	TCNT1 = 49911;                   //resets the counter to the starting value 
}

void USART_init(void) 
{
	UBRR0H = 0;
	UBRR0L = (F_CPU/16/BAUD - 1);       //BAUD prescaler 
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); //8 bit data
	UCSR0B = _BV(RXEN0) | _BV(TXEN0);   //enable rx and tx 
}

//sends the data to the serial port 
void USART_send(char data)
{
	while (!(UCSR0A & (1 << UDRE0)));
		UDR0 = data;	
}

//sends the data to the serial port 
void USART_putstring(char *StringPtr)
{
	while ((*StringPtr != '\0'))
	{
		while (!(UCSR0A & (1 << UDRE0)));
			UDR0 = *StringPtr;
				StringPtr++;
	}
}
