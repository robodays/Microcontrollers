/*
 * 2_Blink_led_delay.c
 *
 * Created: 10.08.2022 19:16:46
 */ 

#include <avr/io.h>

#define F_CPU 1000000UL
#include <util/delay.h>

#define LED PORTD
#define DELAY 100



int main(void)
{
	DDRD = 0b00000011;
    while (1) 
    {
		LED = 0b00000001;
		_delay_ms(DELAY);
		LED = 0b00000000;
		_delay_ms(DELAY);
		LED = 0b00000010;
		_delay_ms(DELAY);
		LED = 0b00000000;
		_delay_ms(DELAY);
    }
}

