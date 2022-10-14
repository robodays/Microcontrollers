/*
 * 27_Shift_register_74HC595.c
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void HC595 (uint8_t byte) {
	for (int i = 0; i < 8; i++) {
		if (byte&(1<<i)) { // >0
			PORTD |= (1<<0);
			} else {
			PORTD &= ~(1<<0);
		}
		PORTD |= (1<<1); // линия тактирования 
		_delay_us(10);
		PORTD &= ~(1<<1);
		_delay_us(10);
	}
	PORTD |= (1<<2); // линия защелки
	_delay_us(10);
	PORTD &= ~(1<<2);
	_delay_us(10);

}

int main(void)
{
	DDRD = 0xff;
	PORTD &= ~((1<<2) | (1<<1) | (1<<0));
	PORTD |= (1<<3); //reset
    //HC595 (0b10000001);
	//_delay_ms(1000);
    //HC595 (0b11000011);
	//_delay_ms(1000);
    //HC595 (0b11100111);
	//_delay_ms(1000);
	//HC595 (0b11111111);

    while (1) 
    {
		
		
		
//		uint8_t byte = 0;
//		for (int i = 0; i < 8; i++) {
//			byte |= (1<<i);
//			//HC595 (1<<i);
//			HC595 (byte);
//			_delay_ms(300);
//		}

		for (uint8_t i = 0; i < 8; i++)
		{
			HC595(1<<i);
			_delay_ms(300);
			
			PORTD &= ~(1<<3);
			//_delay_us(10);
			PORTD |= (1<<3);
			
		}
		
		
		for (uint8_t i = 0; i < 8; i++)
		{
			HC595(1<<i);
			HC595(0);
			_delay_ms(300);
			
			PORTD &= ~(1<<3);
			//_delay_us(10);
			PORTD |= (1<<3);
			
		}
		
		
		for (uint8_t i = 0;  i < 8; i++)
		{
			HC595(1<<i);
			HC595(0b00000000);
			HC595(0b00000000);
			_delay_ms(300);
			
			PORTD &= ~(1<<3);
			//_delay_us(10);
			PORTD |= (1<<3);
			
		}

    }
}

