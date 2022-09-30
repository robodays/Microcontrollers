
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DELAY 500



int main(void)
{
	DDRD = 0b11111111;
	DDRB = 0b00000000;
	
	PORTD = 0b00000001;
	//PORTB = 0b00000011; 
	PORTB = 0b00000010; // резистор к нулевому порту прит€нут отдельно на схеме 10кќм
	while (1) {

		_delay_ms(DELAY);

		// offset
/*		for (int i = 0; i < 7; i++)
		{
			PORTD =  PORTD << 1;
			_delay_ms(DELAY);		
		}
		_delay_ms(DELAY);
*/
/*
		// setting 1 with a offset to left
		PORTD |= (1<<3);
		_delay_ms(DELAY);
		PORTD |= (1<<5) | (1<<6) | (1<<7);
		_delay_ms(DELAY);
		
		// setting 0 with a offset to left
		PORTD &= ~(1<<3);
		_delay_ms(DELAY);
		PORTD &= ~((1<<5) | (1<<6) | (1<<7));
		_delay_ms(DELAY);
		
		// exclusive or
		PORTD ^= (1<<1);
		_delay_ms(DELAY);
		PORTD ^= ((1<<0) | (1<<2));
		_delay_ms(DELAY);
*/
/*		
		// check zero
		if ((PINB & (1<<0)) == 0) {
			PORTD = 0b11111111;
		}
		// or so
		if (~PINB & (1<<1)) {
			PORTD = 0b00000000;
		}
		// or
		//!(PINB & (1<<1))
		
		//check 1 
		//((PINB & (1<<0)) != 0)
		//or
		//(PINB & (1<<0))

		_delay_ms(DELAY);
*/
		
		//while
		//(PINB & (1<<0)) == 1
		//(~PINB & (1<<0)) == 0
		//(!(PINB & (1<<0))) == 0
		while (~PINB & (1<<0))
		{
			PORTD = 0b11111111;
		}
		PORTD = 0b00000000;
		//_delay_ms(DELAY);
	}
}
