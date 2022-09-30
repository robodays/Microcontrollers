#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

//set CKSEL3..0  -> 1110
int main(void)
{
	DDRD |= (1<<0);
	PORTD &= ~(1<<0);
	
	while (1) 
    {
		PORTD |= (1<<0);
		_delay_ms(500);
		PORTD &= ~(1<<0);
		_delay_ms(500);
    }
}

