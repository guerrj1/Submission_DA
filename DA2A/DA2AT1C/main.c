//DA2AT1C.c

#include <avr/io.h>
#include <stdio.h>

int main(void)
{
	DDRB = (1<<2);   //sets pb2 as an input
	DDRB = (0<<5);   //sets pb5 as an input
	TCCR1B = 5;      //sets the prescaler of 1024
	
	while(1)
	{
		TCNT1 = 0;   //t count
		while (TCNT1 != 4530) //while tcount is not equal to the calculated tcnt1
		{}                    //creates the delay
		PORTB ^= (1<<2);     //sets pb2 led to on
		TCNT1 = 0;           //resets count to 0
		while (TCNT1 != 6796)  //while tcount is not euqal to the calculated tcnt1 value
		{}                     //set delay
		PORTB ^= (1<<2);       //exclusive OR the previous value to toggle
	}
	return 0;
}
