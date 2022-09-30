
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DELAY 500


int main(void)
{
	DDRD = 0b11111111;
    while (1) 
    {
		//with a common cathode
		PORTD = 0b00111111; //0
		_delay_ms(DELAY);
		PORTD = 0b00000110; //1
		_delay_ms(DELAY);
		PORTD = 0b01011011; //2
		_delay_ms(DELAY);
		PORTD = 0b01001111; //3
		_delay_ms(DELAY);
		PORTD = 0b01100110; //4
		_delay_ms(DELAY);
		PORTD = 0b01101101; //5
		_delay_ms(DELAY);
		PORTD = 0b01111101; //6
		_delay_ms(DELAY);
		PORTD = 0b00000111; //7
		_delay_ms(DELAY);
		PORTD = 0b01111111; //8
		_delay_ms(DELAY);
		PORTD = 0b01101111; //9
		_delay_ms(DELAY);
		PORTD = 0b10000000; //.
		_delay_ms(DELAY);
		
		//with a common anode
		//PORTD = ~0b00111111; //0

    }
}

