#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	//Clear OC1A/OC1B on Compare Match, set OC1A/OC1B at BOTTOM, (non-inverting mode)
	//Bit 7:6 – COM1A1:0: Compare Output Mode for channel A
	//TCCR1A |= (1<<COM1A1);
	//TCCR1A &= ~(1<<COM1A0);
	
	//Set OC1A/OC1B on Compare Match, clear OC1A/OC1B at BOTTOM, (inverting mode)
	//Bit 7:6 – COM1A1:0: Compare Output Mode for channel A
	TCCR1A |= (1<<COM1A1) | (1<<COM1A0);
	
	//Fast PWM, 10-bit
	//Bit 1:0 – WGM11:0: Waveform Generation Mode
	//TCCR1A |= (1<<WGM10);
	//TCCR1A |= (1<<WGM11);
	//Bit 4:3 – WGM13:2: Waveform Generation Mode
	//See TCCR1A Register description.
	//TCCR1B |= (1<<WGM12);
	//TCCR1B &= ~(1<<WGM13);

	//PWM, Phase Correct, 10-bit
	//Bit 1:0 – WGM11:0: Waveform Generation Mode
	TCCR1A |= (1<<WGM10);
	TCCR1A |= (1<<WGM11);
	//Bit 4:3 – WGM13:2: Waveform Generation Mode
	//See TCCR1A Register description.
	TCCR1B &= ~(1<<WGM12);
	TCCR1B &= ~(1<<WGM13);

	//clkI/O/8 (From prescaler)
	//Bit 2:0 – CS12:0: Clock Select
	TCCR1B |= (1<<CS11);
	TCCR1B &= ~(1<<CS10);
	TCCR1B &= ~(1<<CS12);

	//Output Compare Register 1 A
	OCR1A = 511;
	
	DDRB |= (1<<1) | (1<<2);
	
	PORTB &= ~((1<<1) | (1<<2));
	
	//button
	DDRC = 0b0000000;
	PORTC = 0b0000011;
	
    while (1) 
    {
		if (~PINC & (1<<0)) {
			_delay_ms(200);
			OCR1A += 10;
			if (OCR1A >= 1013) {
				OCR1A = 511;
			}
		}
		if (~PINC & (1<<1)) {
			_delay_ms(200);
			OCR1A -= 10;
			if (OCR1A <= 10) {
				OCR1A = 511;
			}
		}
    }
}

