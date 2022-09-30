
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DELAY 20

int digits[4];

void number(int num) {
	
	digits[0] = num/1000;
	digits[1] = num % 1000 / 100;
	digits[2] = num % 100 / 10;
	digits[3] = num % 10;
}

int main(void)
{
	DDRD = 0b11111111;
	
	DDRB = 0b00001111;
	
	PORTD = 0b11111111;
	
	
	
	PORTB = 0b00001111;	
	
	int digits16[10] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
		
    while (1) 
    {
		// for schemes Dynamic indication2
/*
		PORTB = 0b00001110;
		PORTD = digits16[0];
		_delay_ms(DELAY);
		PORTB = 0b00001101;
		PORTD = digits16[1];
		_delay_ms(DELAY);
		PORTB = 0b00001011;
		PORTD = digits16[2];
		_delay_ms(DELAY);
		PORTB = 0b00000111;
		PORTD = digits16[3];
		_delay_ms(DELAY);
*/		

		//for schemes Dynamic indication3_npn
		
		number(4567);
		
		PORTB = 0b00000001;
		PORTD = digits16[digits[0]];
		_delay_ms(DELAY);
		for (int i = 1; i < 4; i++)
		{
			PORTB <<= 1;
			PORTD = digits16[digits[i]];
			_delay_ms(DELAY);
		}
		
		/*PORTB = 0b00000001;
		PORTD = digits16[digits[0]];
		_delay_ms(DELAY);
		PORTB = 0b00000010;
		PORTD = digits16[digits[1]];
		_delay_ms(DELAY);
		PORTB = 0b00000100;
		PORTD = digits16[digits[2]];
		_delay_ms(DELAY);
		PORTB = 0b00001000;
		PORTD = digits16[digits[3]];
		_delay_ms(DELAY);*/
    }
}

