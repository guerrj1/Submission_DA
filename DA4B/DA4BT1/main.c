//DA4BT1

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

volatile unsigned int ADCVal;			 //variable that the ADC value is stored in
void adc_init(void);

int main(void)
{
	DDRB = 0x0F;							//PB0-PB3 as output
	DDRC = 0;								//set portc as input
	PORTB = 0;								//turns off portb
	//Timer
	TCCR1B = (1 << WGM12) | (1 << CS11);	//set prescalar to 8
	
	adc_init();
	
	while(1)
	{
		ADCSRA |= (1 << ADSC);			//start adc conversion
		while((ADCSRA&(1<<ADIF))==0);	//wait for conversion to finish 
		ADCVal = ADC & 0x03FF;			//read ADCH and ADCL
		OCR1A = 10*ADCVal;				//duty cycle for PWM 

		PORTB = 0x09;
		while(!(TIFR1 & (1<<OCF1A)));  //delay
		TIFR1 |= (1 << OCF1A);         //reset flag
		PORTB = 0x03;
		while(!(TIFR1 & (1<<OCF1A)));   //delay 
		TIFR1 |= (1 << OCF1A);          //reset flag
		PORTB = 0x06;
		while(!(TIFR1 & (1<<OCF1A)));   //delay
		TIFR1 |= (1 << OCF1A);          //reset flag
		PORTB = 0x0C;
		while(!(TIFR1 & (1<<OCF1A)));   //delay
		TIFR1 |= (1 << OCF1A);          //reset flag
	}
}

void adc_init (void)
{
	DIDR0 = 0x1;							//digital input disable
	ADMUX = (1<<REFS0);						//reference selection; AVcc
	
	ADCSRA |= (1<<ADEN) |                   //enable ADC
	         (1<<ADPS2) |                   //prescalar 128
	         (1<<ADPS1) | 
			 (1<<ADPS0);				
	ADCSRB = 0x0;							//adc control and status register free running mode
}