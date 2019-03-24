//DA2CT3_1.c

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= (1<<2);                    //sets pb2 as output
	PORTB |= (1<<2);                   //sets for pb2 led
	//TCNT0 = 0x1D;
	TCNT0 = 0;  
	TCCR0A = (1<<WGM01);                //sets CTC mode 
	TCCR0B = (1<<CS02) | (1 << CS00);   //sets prescaler to 2014
	
	TIMSK0 |= (1<<OCIE0A);              //sets interrupt compare match
	sei();                              //enables interrupt
	
	while(1)
	{
		
	}
}

ISR(TIMER0_COMPA_vect)
{
	uint8_t OVFCount = 0;
	
	while(1)
	{
		while((TIFR0 & 0x01) == 0);      //while flag is 0
		
		TCNT0 = 0x1D;                //starting counter for tcnt0
		TIFR0 = 0x01;                //resets the overflow flag
		//OVFCount++;
		
		if(OVFCount == 19 )          //overflow counter counts up to this
		{
			PORTB ^= (1<<2);         //turns led off
		}
		else if(OVFCount == 49)      //overflow counter counts up to this
		{
			PORTB ^= (1<<2);       //keeps led on
			OVFCount = 0;          //resets the overflow count
		}
		OVFCount++;		            //increment overflow count
	}

}