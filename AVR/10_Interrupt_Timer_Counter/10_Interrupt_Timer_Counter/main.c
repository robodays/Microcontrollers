#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect) {
	TCCR1B = 0b00000000; // stop timer
	PORTD |=(1<<0);
	_delay_ms(1000);
	PORTD &=~(1<<0);
	_delay_ms(1000);
	PORTD |=(1<<0);
	_delay_ms(1000);
	PORTD &=~(1<<0);
	_delay_ms(1000);
	TCCR1B = 0b00000011; // start timer
	TCNT1 = 5000; // start with 5000 
}



int main(void)
{

	DDRC = 0b0111111;
	PORTC = 0b0000000; // 6 LED
	
	DDRD |= (1<<0);
	PORTD &= ~(1<<0); //one LED
	
	TIMSK |= (1<<2); // Bit 2 – TOIE1: Timer/Counter1, Overflow Interrupt Enable
	TCCR1B = 0b00000011; // clkI/O/64 (From prescaler)
	TCNT1 = 0; // Timer/Counter
	
	SREG |= (1<<7); // Status Register -> Bit 7 – I: Global Interrupt Enable
	// or
	//sei();
	
	while (1)
	{
		for(int i = 0; i < 6; i++) {
			PORTC |= (1<<i);
			_delay_ms(300);
		}
		


		PORTC = 0b0000000;
		_delay_ms(300);
	}
}

