#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


#define DELAY 300

int digits16[10] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};

int digits[4];

char discharge = 1; // digit of a number

float num;
float num2;

void number(int num2) {
	
	digits[0] = num2/100;
	digits[1] = num2 % 100 / 10;
	digits[2] = num2 % 10;

}

ISR (TIMER0_OVF_vect) {
	if (discharge == 1) {
		PORTB = 0b00000001; 
		PORTD = digits16[digits[0]];
		if (num < 10) {
			PORTD |= (1<<7);
		} else {
			PORTD &= ~(1<<7);
		}
	}
	
	if (discharge == 2) {
		PORTB = 0b00000010; 
		PORTD = digits16[digits[1]];
		if (num > 10) {
			PORTD |= (1<<7);
		} else {
			PORTD &= ~(1<<7);
		}
	}
	
	if (discharge == 3) {PORTB = 0b00000100; PORTD = digits16[digits[2]]; discharge = 0;}
	//if (discharge == 4) {PORTB = 0b00001000; PORTD = digits16[digits[3]]; discharge = 0;}
	discharge++;

}

int main(void)
{
	DDRD = 0b11111111;
	DDRB = 0b00000111;
	
	// potentiometer
	DDRC &= ~(1<<1);

	// LED
	DDRC |= (1<<5);

	
	PORTD = 0b00000000;
	PORTB = 0b0000111;

	
	

	// 1000000/8
	TCCR0 |= (1<<1);
	TCCR0 &= ~((1<<0) | (1<<2));	
	// 1000000/64
	//TCCR0 |= (1<<0) | (1<<1);
	//TCCR0 &= ~(1<<2);
	// 1000000/256
	//TCCR0 |= (1<<2);
	//TCCR0 &= ~((1<<0) | (1<<1));
	
	// 1000000/1024
	//TCCR0 |= (1<<0) | (1<<2);
	//TCCR0 &= ~(1<<1);
	


	TIMSK |= (1<<0); //Timer/Counter0 Overflow Interrupt Enable
	TCNT0 = 0; // Timer/Counter Register
	sei();  // Status Register / Bit 7 – I: Global Interrupt Enable
	
	//ACD
	ADCSRA |= (1<<ADEN); // Bit 7 – ADEN: ADC Enable
	ADCSRA |= (1<<ADFR); // Bit 5 – ADFR: ADC Free Running Select
	
	//Bits 2:0 – ADPS2:0: ADC Prescaler Select Bits
	//These bits determine the division factor between the XTAL frequency and the input clock to the ADC.
	//125kHz  1000000/8
	//ADCSRA &= ~(1<<ADPS2);
	//ADCSRA |= (1<<ADPS1) | (1<<ADPS0);
	// 1000000/128
	//ADCSRA |= (1<<ADPS1) | (1<<ADPS0) | (1<<ADPS2);
	// 1000000/2
	//ADCSRA &= ~((1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2));
	// 1000000/16
	ADCSRA |= (1<<ADPS2);
	ADCSRA &= ~((1<<ADPS0) | (1<<ADPS1));
	
	//Bit 7:6 – REFS1:0: Reference Selection Bits
	//These bits select the voltage reference for the ADC
	//AVCC with external capacitor at AREF pin 5V
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
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
		if (ADCSRA & (1<<ADIF)) {
			num = ADC*5.0/1024;
			
			if (num > 1.5) {
				PORTC |= (1<<5);
			} else {
				PORTC &= ~(1<<5);
			}
		
			//coefficient for point displacement 
			if (num < 10)
			{
				num2 = num * 100;
			} else {
				num2 = num * 10;
			}
			number(num2);
			
			
			ADCSRA |= (1<<ADIF);
		}

	}
}


