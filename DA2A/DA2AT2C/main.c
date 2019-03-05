//DA2AT2C.c


#define F_CPU 16000000UL        //sets CPU clock speed 
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= (1<<2);                    //sets pb2 as input
	PORTB |= (1<<2);                   //sets pb2 to high for LED
	DDRC &= (0<<2);                    //sets PC2 to input
	PORTC |= (0<<2);                   //sets PC2 to low 0 

	while (1)                          //while loop continously checking
	{
		if (!(PINC & (1 << PINC2)))    //if pinc2 was pressed then released
		{
	 		PORTB &= ~(1<<2);          //then portb2 led is on
			_delay_ms(1250);           //delays for 1.250 secs while on
		}
		else
		{
			PORTB |= (1<<2);           //toggles pb2 led 
		}
	}
	return 0;
}