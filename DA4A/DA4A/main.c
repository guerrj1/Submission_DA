//DA4A

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile unsigned int ADCvalue;		//variable that the ADC value is stored in
char toggle = 0;
void adc_init(void);   //adc function

int main(void)
{
	DDRB = (1<<1);	  //set portb1 as outout for PWM
	DDRC = 0;		  //setting portc as an input for pushbutton
	PORTB = 0;
	
	//timer1 intialization
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11);	//enable PWM, fast PWM and non inverted mode
	TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS11);		//setting prescalar to 8
	ICR1 = 9999;						//timer1 top value
	
	PORTC |= (1<<1);        //set pc1 as pushbutton
	PCICR = (1<<PCIE1);
	PCMSK1 = (1<<PCINT9);
	
	sei();                   //enable global interrupt
	
	while (1)
	{
	}
}

void adc_init(void)
{
	// ADC initialization
	DIDR0 = 0x1;		     //digital input disable
	ADMUX = (1<<REFS0);	     //reference selection; AVcc
	ADCSRA |= (1<<ADEN) |    //enable ADC
	(1<<ADPS2) |   //prescalar 128
	(1<<ADPS1) |
	(1<<ADPS0);
	ADCSRB = 0x0;		     //adc control and status register free running mode
}

//interrupt
ISR(PCINT1_vect)
{
	if(!(PINC & (1 << PINC1)))  //if pushbutton is pressed
	{
		_delay_ms(100);	//delay for debouncing

		while(!(PINC & (1 << PINC1)));  //while button is pressed
		
		if(toggle == 1)
		{
			PORTB |= (1<<1);
			ADCSRA |= (1 << ADSC);			    // start adc conversion
			
			while((ADCSRA&(1<<ADIF))==0);	         // wait for conversion to finish
			
			ADCvalue = ADC & 0x03FF;		      	//read ADCH and ADCL
			OCR1A = 10*ADCvalue;				    //duty cycle for PWM
		}
		
		else if(toggle == 0)
		{
			OCR1A = 0;
			PORTB &= ~(1<<1);
		}
		toggle ^= 1;   //xor toggling
		
	}
}
