#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

unsigned char click0 = 0, click1 = 0;

void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address and data registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}


int main(void)
{
	//LED
	DDRB = 0b00001111;
	DDRC = 0b0001111;
	
	//Button
	DDRD &= ~((1<<0) | (1<<1));
	
	PORTB = 0b00000000;
	PORTC = 0b0000000;
	
	PORTD |= (1<<0) | (1<<1);
	
	click0 = PORTB = EEPROM_read(0x00);
	click1 = PORTC = EEPROM_read(0X01);
	
	
    while (1) 
    {
		if (~PIND & (1<<0)) {
			if (click0 < 16) {
				click0++;
			} else {
				click0 = 0;
			}
			PORTB = click0;
			EEPROM_write(0x00, click0);
			while (~PIND & (1<<0)) {
				_delay_ms(200);
			}
		}
		if (~PIND & (1<<1)) {
			if (click1 < 16) {
				click1++;
			} else {
				click1 = 0;
			}
			PORTC = click1;
			EEPROM_write(0x01, click1);
			while (~PIND & (1<<1)) {
				_delay_ms(200);
			}
		}
		
    }
}

