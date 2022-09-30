
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

ISR(INT0_vect) {
	PORTD |=(1<<0);
	_delay_ms(1000);
	PORTD &=~(1<<0);
	
}

ISR(INT1_vect) {
	PORTD |=(1<<0);
	_delay_ms(1000);
	PORTD &=~(1<<0);
	
}

int main(void)
{
	GICR = 0b11000000; // External Interrupt Request 0 AND External Interrupt Request 1
	MCUCR = 0b00001110; // The falling edge of INT0 generates an interrupt request AND The rising edge of INT1 generates an interrupt request
	SREG |= (1<<7); // Status Register -> Bit 7 – I: Global Interrupt Enable
	// or
	//sei();
	
	DDRC = 0b0111111;
	PORTC = 0b0000000; // 6 LED
	
	DDRD = 0b00000001;
	PORTD = 0b10000100; // One LED and Button
    while (1) 
    {
		for(int i = 0; i < 6; i++) {
			PORTC |= (1<<i);
			_delay_ms(300);
		}
		
		// if Button push -> on LED
		if (~PIND & (1<<7)) {
			PORTD |=(1<<0);
			_delay_ms(1000);
		}
		// if on LED -> off
		if (PIND & (1<<0)) {
			PORTD &=~(1<<0);
		}

		PORTC = 0b0000000;
		_delay_ms(300);		    
	}
}

