
#include <avr/io.h>


int main(void)
{
	//LED
	DDRB |= (1<<2) | (1<<1) | (1<<0);
	PORTB &= ~((1<<2) | (1<<1) | (1<<0));
	
	// potentiometer
	DDRC &= ~(1<<1);
	
	ADCSRA |= (1<<ADEN); // Bit 7 – ADEN: ADC Enable
	ADCSRA |= (1<<ADFR); // Bit 5 – ADFR: ADC Free Running Select
	
	//Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
	//These bits determine the division factor between the XTAL frequency and the input clock to the ADC.
	//125kHz
	ADCSRA &= ~(1<<ADPS2);
	ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
	
	//Bit 7:6 – REFS1:0: Reference Selection Bits
	//These bits select the voltage reference for the ADC 
	//Internal 2.56V Voltage Reference with external capacitor at AREF pin
	ADMUX |= (1<<REFS1) | (1<<REFS0);
	
	// Bit 5 – ADLAR: ADC Left/Right Adjust Result
	ADMUX &= ~(1<<ADLAR); // 0 -> Right
	
	//Bits 3:0 – MUX3:0: Analog Channel Selection Bits
	//ADC1(POTR PC1)
	ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1));
	ADMUX |= (1<<MUX0);
	
	//Bit 6 – ADSC: ADC Start Conversion
	ADCSRA |= (1<<ADSC);
	
	
    while (1) 
    {
		//Bit 4 – ADIF: ADC Interrupt Flag
		if (ADCSRA & (1<<ADIF)) {
			if (ADC >= 600) { // >= 1.5V
				PORTB |= (1<<0); // Green on
				PORTB &= ~((1<<1) | (1<<2)); // Yellow and Red off
			}
			if (ADC >= 560 && ADC < 600) { // >= 1.4V and < 1.5V
				PORTB |= (1<<1); // Yellow on
				PORTB &= ~((1<<0) | (1<<2)); // Green and Red off
			}
			
			if (ADC < 560) { // < 1.4V
				PORTB |= (1<<2); // Red on
				PORTB &= ~((1<<0) | (1<<1)); // Green and Yellow off
			}
			
			ADCSRA |= (1<<ADIF);
		}
    }
}

