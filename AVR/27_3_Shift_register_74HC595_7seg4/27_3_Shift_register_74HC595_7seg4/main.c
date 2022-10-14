/*
 * 27_3_Shift_register_74HC595_7seg4.c
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int r1_1000 = 0;
int r2_100 = 0;
int r3_10 = 0;
int r4_1 = 0;

int cnt=0;


int digits [10] = {
	0b00111111,  // 0
	0b00000110,  // 1
	0b01011011,  // 2
	0b01001111,  // 3
	0b01100110,  // 4
	0b01101101,  // 5
	0b01111101,  // 6
	0b00000111,  // 7
	0b01111111,  // 8
	0b01101111   // 9
};


void HC595 (uint8_t byte)
{
	for(int i=0; i<8; i++)
	{
		if (byte&(1<<i)) PORTD |= (1<<0);
		else PORTD &= ~(1<<0);
		
		PORTD |= (1<<1); // Линия тактирования
		_delay_us(10);
		PORTD &= ~(1<<1);
		_delay_us(10);
	}
	
	
	// 	PORTD |= (1<<2); // Линия защелки
	// 	_delay_us(10);
	// 	PORTD &= ~(1<<2);
	// 	_delay_us(10);
	
	
}


void number (unsigned int num)
{
	r1_1000 = num/1000;		// Тысячи
	r2_100 = num%1000/100;	// Сотни
	r3_10 = num%100/10;		// Десятки
	r4_1 = num%10;			// Единицы
}

ISR(TIMER0_OVF_vect)
{
	//reset
	PORTD &= ~(1<<3); 
	_delay_us(10);
	PORTD |= (1<<3);
	_delay_us(10);
	
	
	cnt++;
	if(cnt>8) cnt=1;
	if (cnt==2)
	{
		HC595(0b11111110); // Включаем первый разряд
		HC595(digits [r1_1000]); // Отображаем тысячи
		
	}
	else if (cnt==4)
	{
		HC595(0b11111101); // Включаем второй разряд
		HC595(digits [r2_100]); // Отображаем сотни
	}
	else if (cnt==6)
	{
		HC595(0b11111011); // Включаем третий разряд
		HC595(digits [r3_10]); // Отображаем десятки
	}
	else if (cnt==8)
	{
		HC595(0b11110111); // Включаем четвертый разряд
		HC595(digits [r4_1]); // Отображаем единицы
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
	
	TCCR0 = 0b00000010;
	TIMSK |= (1<<TOIE0);
	sei();

	while (1)
	{
		number(3857);
	}
}



