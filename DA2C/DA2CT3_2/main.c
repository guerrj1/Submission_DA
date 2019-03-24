//DA2CT3_2.c 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRB |= (1<<2);                     //sets pb2 as output
	PORTB |= (1<<2);                    //sets pb2 led
	//TCNT0 = 0x1D;
	TCNT0 = 0;
	TCCR0A = (1<<WGM01);                //sets ctc mode
	TCCR0B = (1<<CS02) | (1 << CS00);   //sets prescaler to 1024
	
	TIMSK0 |= (1<<OCIE0A);              //sets interrupt on compare match
	sei();                              //enables interrupt 
	
	while(1)
	{
		
	}
}

ISR(TIMER0_COMPA_vect)
{
	int OVFCount = 0;
	while (1)
	{
		if (!(PINC & (1<<PINC2)))    //checks if the pushbutton is pressed
		{
			OVFCount = 0;
			TCNT0 = 0;
		}
		
		while ((TIFR0 & 0x01) == 0);
		
		TCNT0 = 0x05;			//starts at this value to count from
		TIFR0 = 0x01;			//rests the overflow flag
		OVFCount++;			   //overflow flag counter increment
		
		if (OVFCount <= 78)		   //when overflow counter is less than or equal to 78
		{
			PORTB = (0<<2);          //then portb2 led is on
		}
		else
		{
			PORTB = (1<<2);          //then portb2 led is off
		}
	}
}