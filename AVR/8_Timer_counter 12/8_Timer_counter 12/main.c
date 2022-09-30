#define F_CPU 1000000UL

#include <avr/io.h>


int main(void)
{
	DDRD = 0b11111111;
	PORTD = 0b00000000;
	
	TCCR1B = 0b00000011;
	
	// TCCR2
	//TCCR2 = 0b00000111;
	//TCNT2 = 0;
	
//	TCNT1 = 0;
	TCNT1H = 0;
	TCNT1L = 0;
	while (1)
	{
		/*
		if (TCNT1 == 0) {
			PORTD = 0b00000111;
		}
		if (TCNT1 == 32768) {		// 65536/2
			PORTD = 0b11111111;
		}
		*/
		 
		// or so
		
		if (TCNT1L == 0 && TCNT1H == 0) {
			PORTD = 0b00000111;
		}
		//if (TCNT1L == 0 && TCNT1H == 128) {
		//	PORTD = 0b11111111;
		//}
		// or so
		if (TCNT1L == 0x00 && TCNT1H == 0b10000000) {
			PORTD = 0b11111111;
		}
		
		// TCCR2
		/*
		if (TCNT2 == 0) {
			PORTD = 0b00000111;
		}
		if (TCNT2 == 128) {		
			PORTD = 0b11111111;
		}
		*/
	}
}