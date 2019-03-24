// DA2CT1_2.c

#define F_CPU 16000000UL               //sets CPU clock speed
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<2);                    //sets pb2 as input
	PORTB |= (1<<2);                   //sets pb2 to high for LED
	DDRC &= (0<<2);                    //sets PC2 to input
	PORTC |= (0<<2);                   //sets PC2 to low 0
	
	TCCR0A = 0;                         
	TCCR0B = (1<<CS02) | (1<<CS00);     //sets prescaler to 1024
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
	return 0;
}