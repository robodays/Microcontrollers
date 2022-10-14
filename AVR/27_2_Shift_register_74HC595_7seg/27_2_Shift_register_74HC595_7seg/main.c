/*
 * 27_2_Shift_register_74HC595_7seg.c
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


void number (unsigned int num);
void HC595 (uint8_t byte);


int didits [10] =
{
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111 //9
};


void number (unsigned int num)
{
	HC595(didits[num%10]);//еденици	
	HC595(didits[num%100/10] | (1<<7));//десятки	
	HC595(didits[num/100]);//сотни


	
	
}




void HC595 (uint8_t byte)
{
	for(int i=0; i<=7; i++)
	{
		if (byte&(1<<i)) PORTD |= (1<<0);
		else PORTD &= ~(1<<0);
		
		PORTD |= (1<<1); // Линия тактирования
		_delay_us(10);
		PORTD &= ~(1<<1);
		_delay_us(10);
	}
	
	
	PORTD |= (1<<2); // Линия защелки
	_delay_us(10);
	PORTD &= ~(1<<2);
	_delay_us(10);
	
	
}


int main(void)
{
	DDRD = 0xff;
	PORTD &= ~((1<<2) | (1<<1) | (1<<0));
	PORTD |= (1<<3); // Reset
	
	number(456);
	
	while (1)
	{
		
	}
}


