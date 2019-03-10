//DA2BT1C.c

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h> 
#include <util/delay.h>

int main(void)
{

  DDRB |= (1<<2);    //sets pb2 as an output
  DDRB |= (1<<5);    //sets pb5 as an output
  PORTB |= (1<<2);   //sets pb2 led
  PORTB |= (1<<5);   //sets pb5 led off
  DDRC &= (0<<2);    //for push button output
  PORTC |= (0<<2);   //for push button 
  PORTD |= (1<<2);   // enable PORTD.2 pin pull up resistor
  EIMSK = (1<<INT0); //enable external interrupt 0
  EICRA = 0x02;      //interrupt on falling edge
  sei();
	
  while(1)           //while running
  {}
  
}

ISR(INT0_vect)
{
 PORTB ^= (1<<2); //toggle pb2 led
 _delay_ms(1250);   //keep led on for 1250ms
}


