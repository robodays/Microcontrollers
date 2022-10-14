/*
 * 26_TWI_I2C_PCF8574_LCD.c
*/

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

///LCD
#define RS_DATA PORTD |= (1<<2); // sending data
#define RS_COMMAND PORTD &= ~(1<<2); // sending commands

// raising and lowering the potential for fixing commands
#define E_1 PORTD |= (1<<3);
#define E_0 PORTD &= ~(1<<3);
///end


///LCD PCF8574
//#define RS_DATA TWI_write_byte_addr(pcf_port |= (1<<2)) // sending data
//#define RS_COMMAND TWI_write_byte_addr(pcf_port &= ~(1<<2)) // sending commands

// raising and lowering the potential for fixing commands
//#define E_1 TWI_write_byte_addr(pcf_port |= (1<<3))
//#define E_0 TWI_write_byte_addr(pcf_port &= ~(1<<3))

unsigned char pcf_port = 0;
///end


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


// Запись данных
void TWI_write_byte (unsigned char twi_data)
{
	TWDR = twi_data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
}

// Запись данных + адрес для PCF8574
void TWI_write_byte_addr(unsigned char twi_data)
{
	TWI_start();
	//TWI_write_byte(0b01000000); // Адрес + W
	TWI_write_byte(0b01000110); // Адрес + W для переходник + ЖК
	
	TWI_write_byte(twi_data);
	TWI_stop();
	
}


// Чтение данных
unsigned char TWI_read_byte ()
{
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	return TWDR;
}


// Настройки ЖК дисплея
void LCD_commands(unsigned char command) {
	/// для LCD
	PORTD = command;
	///end
	
	/// PCF8574
	//pcf_port = command;
	//TWI_write_byte_addr(pcf_port);
	///end

	
	RS_COMMAND;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
	
	/// для LCD
	PORTD = (command<<4);
	///end
	
	/// PCF8574
	//pcf_port = (command<<4);
	//TWI_write_byte_addr(pcf_port);
	///end

	
	RS_COMMAND;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
}

void LCD_data(unsigned char data) {
	/// для LCD
	PORTD = data;
	///end
		
	/// PCF8574
	//pcf_port = data;
	//TWI_write_byte_addr(pcf_port);
	///end

	
	RS_DATA;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
	
	/// для LCD
	PORTD = (data<<4);
	///end
		
	/// PCF8574
	//pcf_port = (data<<4);
	//TWI_write_byte_addr(pcf_port);
	///end

	
	RS_DATA;
	E_1;
	_delay_us(50);
	E_0;
	_delay_us(50);
}

// Для порта D
void LCD_setting_PORTD() {
		/// для LCD
		DDRD = 0b11111100;
		PORTD = 0b00000000;
		/// end
		
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

///////////////////PSF8574




int main(void)
{
	 DDRB = 0xff;
	 
	TWI_settings ();
	
	// Запись данных
	TWI_start();
	TWI_write_byte(0b01000000); // Адрес000 + W
	TWI_write_byte(0b10011011); // Данные
	TWI_stop();
	
	// Чтение данных
	TWI_start();
	TWI_write_byte(0b01000011); // Адрес001 + R
	PORTB = TWI_read_byte();
	TWI_stop();
	
	// for button and led in while
	TWI_start();
	TWI_write_byte(0b01000011);
	
	//LCD PIND
	LCD_setting_PORTD();
	line1(6);
	LCD_string("!!!!!");
	line2(2);
	LCD_string("Print string");
	
	
    while (1) 
    {
		// for button and led in while
		// Чтение данных
		_delay_ms(100); //чтобы не загружать процессор микроконтроллера
		PORTB = TWI_read_byte();
    }
}

