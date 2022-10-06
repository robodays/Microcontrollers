#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define RS_DATA PORTD |= (1<<2); // sending data
#define RS_COMMAND PORTD &= ~(1<<2); // sending commands

// raising and lowering the potential for fixing commands
#define E_1 PORTD |= (1<<3); 
#define E_0 PORTD &= ~(1<<3); 

void LCD_commands(unsigned char command) {
	PORTD = command;
	RS_COMMAND;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
	
	PORTD = (command<<4);
	RS_COMMAND;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
}

void LCD_data(unsigned char data) {
	PORTD = data;
	RS_DATA;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
	
	PORTD = (data<<4);
	RS_DATA;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
}

void line1(unsigned char adress) {
	LCD_commands(adress | (1<<7));
}

void line2(unsigned char adress) {
	LCD_commands((adress + 0x40) | (1<<7));
}

void LCD_string(char str[]) {
	for (uint8_t i = 0; i < strlen(str); i++) {
		LCD_data(str[i]);
	}
}


int main(void)
{
	DDRD = 0b11111100;
	PORTD = 0b00000000;
	
	//from datasheet LCD
	_delay_ms(15);
	LCD_commands(0b00110000);
	
	_delay_ms(5);
	LCD_commands(0b00110000);

	_delay_us(100);
	LCD_commands(0b00110000);
	
	_delay_ms(1);
	LCD_commands(0b00000010);
	
	_delay_ms(2);
	LCD_commands(0b00101000); // 4 bits, 2 string, font 5*8

	_delay_ms(1);
	LCD_commands(0b00001100); // turn on the display, do not show and do not blink the cursor
	//LCD_commands(0b00001111); // turn on the display, show and blink the cursor

	_delay_ms(1);
	LCD_commands(0b00000001); // Clear display
	
	_delay_ms(2);
	LCD_commands(0b00000110); // increment and shift the cursor to the right
	
	_delay_ms(1);
	
	line1(8);
	LCD_data('!');
	
	line2(2);
	LCD_string("Print string");

    while (1) 
    {
    }
}

