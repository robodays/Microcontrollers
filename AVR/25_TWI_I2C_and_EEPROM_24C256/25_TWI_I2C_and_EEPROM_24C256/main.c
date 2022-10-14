/*
 * 25_TWI_I2C_and_EEPROM_24C256.c
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

int digits16[10] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};
int digits[4];
char discharge = 1; // digit of a number
int num = 0;


unsigned char TWI_status = 0;
unsigned char TWI_data = 0;

//bool negative_temperature = false;

void number(int num) {
	digits[0] = num/1000;
	digits[1] = num % 1000 / 100;
	digits[2] = num % 100 / 10;
	digits[3] = num % 10;
}

ISR (TIMER0_OVF_vect) {
	if (discharge == 1) {
		PORTC &= ~(1<<0);
		PORTC |= (1<<3);
		PORTD = digits16[digits[0]];
/*		if (negative_temperature) {
			PORTD = 0b01000000;
			} else {
			//PORTD &= ~(1<<6);
			PORTD = digits16[digits[0]];
		}
		*/
	}
	if (discharge == 2) {
		PORTC &= ~(1<<1);
		PORTC |= (1<<0);
		PORTD = digits16[digits[1]];
	}
	if (discharge == 3) {
		PORTC &= ~(1<<2);
		PORTC |= (1<<1);
		PORTD = digits16[digits[2]];
		//PORTD |= (1<<7);
	}
	if (discharge == 4) {
		PORTC &= ~(1<<3);
		PORTC |= (1<<2);
		PORTD = digits16[digits[3]];
		discharge = 0;
	}
	discharge++;
}

// Настройки TWI
void TWI_settings (void)
{
	TWBR = 2; // Частота 50 кГц линии тактирования при fмк = 1 МГц
	TWSR &= ~((1<<TWPS1) | (1<<TWPS0)); // Коэф. деления = 1
}

// Старт TWI
void TWI_start (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
}

// Стоп TWI
void TWI_stop (void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
}


int main(void)
{
	//7seg
	DDRC |= (1<<0) | (1<<1) | (1<<2) | (1<<3);
	DDRD = 0b11111111;
	
	PORTC |= (1<<0) | (1<<1) | (1<<2) | (1<<3);

	PORTD = 0b00000000;	

	// 1000000/8
	//TCCR0 |= (1<<1);
	//TCCR0 &= ~((1<<0) | (1<<2));
	// 1000000/64
	TCCR0 |= (1<<1) | (1<<0);
	TCCR0 &= ~(1<<2);
	
	TIMSK |= (1<<0); //Timer/Counter0 Overflow Interrupt Enable
	TCNT0 = 0; // Timer/Counter Register
	sei();
	
	TWI_settings();
	
	
	////////////////// Запись
	TWI_start();
	
//TWI_status = TWSR;
	
	TWDR = 0b10100000; //Адрес устройства + запись W
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
//TWI_status = TWSR;
	
	TWDR = 0; // Старший байт адреса внешней EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	TWDR = 8; // Младший байт адреса внешней EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
//TWI_status = TWSR;
	
	TWDR = 156; // Запись данных во внешнюю EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
//TWI_status = TWSR;
	
	TWI_stop();
	_delay_ms(10);	// задержка, т.к. не успевает обработать
//TWI_status = TWSR;
	
	/////////////////////////// Чтение
	
	TWI_start();
		
//TWI_status = TWSR;
		
	TWDR = 0b10100000; //Адрес устройства + запись W
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
		
//TWI_status = TWSR;
		
	TWDR = 0; // Старший байт адреса внешней EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
		
	TWDR = 8; // Младший байт адреса внешней EEPROM 24C256
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
		
//TWI_status = TWSR;
	
	TWI_start(); // повторный старт для чтения
	
//TWI_status = TWSR;
	
	TWDR = 0b10100001; //Адрес устройства + чтение R
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
//TWI_status = TWSR;

	// Принимаем данные из EEPROM
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	TWI_data = TWDR;
	TWI_status = TWSR;
	
	TWI_stop();
	
	while (1)
	{
		//number(1234);
		//number(TWI_status);
		number(TWI_data);
		
	}
}

