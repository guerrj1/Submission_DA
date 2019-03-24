//DA2CT1_1.c

#define F_CPU 16000000L
#include <avr/io.h>

int main()
{
	uint8_t OVFCount = 0;                 //overflow flag counter
	DDRB |= (1<<2);                       //set pb2 as output
	PORTB |= (1<<2);                      //led output
	TCNT0 = 0x1D;                         //starting counter
	TCCR0B = (1<<CS02) | (1 << CS00);     //sets prescaler to 1024
	
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
	return 0;
}