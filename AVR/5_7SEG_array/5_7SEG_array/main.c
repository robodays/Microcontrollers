
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#define DELAY 500

int digits[10] = {
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111	//9
};

int digits16[10] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
	
int digitNow = 0;

int main(void)
{
	DDRD = 0b11111111;
	DDRB = 0b00000000;
	PORTB = 0b00000011;
	while (1)
	{
		if (PINB == 0b00000010) {
			digitNow++;
			_delay_ms(300);
			if (digitNow > 9) {
				digitNow = 0;
			}
		}
		
		if (PINB == 0b00000001) {
			digitNow--;
			_delay_ms(300);
			if (digitNow < 0) {
				digitNow = 9;
			}
		}
		
		PORTD = digits16[digitNow];

	}
}