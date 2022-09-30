
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DELAY 300
#define LED PORTD
#define BUTTON PORTB


int main(void)
{
	DDRB = 0b00000000; // in button
	DDRD = 0b11111111; // out led
	
	LED = 0b00000000; // Low potential
	BUTTON = 0b11111111; //high potential
	

    while (1) 
    {
		if (PINB == 0b11111110) {
			LED = 0b11111111;
			_delay_ms(DELAY);
			LED = 0b00000000;
			_delay_ms(DELAY);
		} else {
			LED = 0b00000000;
		}
		if (PINB == 0b11111101) {
			LED = 0b00000001;
			_delay_ms(DELAY);
			LED = 0b00000011;
			_delay_ms(DELAY);
			LED = 0b00000111;
			_delay_ms(DELAY);
			LED = 0b00001111;
			_delay_ms(DELAY);
			LED = 0b00011111;
			_delay_ms(DELAY);
			LED = 0b00111111;
			_delay_ms(DELAY);
			LED = 0b01111111;
			_delay_ms(DELAY);
			LED = 0b11111111;
			_delay_ms(DELAY);
			LED = 0b00000000;
			_delay_ms(DELAY);
		} else {
			LED = 0b00000000;
		}
    } 
}

