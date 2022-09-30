/*
 * 1_Led.c
 *
 * Created: 10.08.2022 15:57:32
 */ 

#include <avr/io.h>


int main(void)
{
    /* Replace with your application code */
	DDRC = 0b000011; // 2 system
	//DDRC = 0x1; // 16 system 
	PORTC = 0b0000000; // 0V
    while (1) 
    {
		PORTC = 0b000011; // 5V
    }
}