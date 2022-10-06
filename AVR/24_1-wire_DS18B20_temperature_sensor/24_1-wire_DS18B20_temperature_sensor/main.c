/*
 * 24_1-wire_DS18B20_temperature_sensor.c
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


bool negative_temperature = false;

void number(int num) {
	digits[0] = num/1000;
	digits[1] = num % 1000 / 100;
	digits[2] = num % 100 / 10;
	digits[3] = num % 10;
}

ISR (TIMER0_OVF_vect) {
	if (discharge == 1) {
		PORTC &= ~(1<<2);
		PORTC |= (1<<5);
		if (negative_temperature) {
			PORTD = 0b01000000;
		} else {
			//PORTD &= ~(1<<6);
			PORTD = digits16[digits[0]];
		}
	}
	if (discharge == 2) {
		PORTC &= ~(1<<3); 
		PORTC |= (1<<2);
		PORTD = digits16[digits[1]];
	}
	if (discharge == 3) {
		PORTC &= ~(1<<4); 
		PORTC |= (1<<3);
		PORTD = digits16[digits[2]];
		PORTD |= (1<<7);
	}
	if (discharge == 4) {
		PORTC &= ~(1<<5); 
		PORTC |= (1<<4);
		PORTD = digits16[digits[3]];
		discharge = 0;
	}
	discharge++;
	//TCNT0 = 50;
}


//checking the sensor on the line
bool check_ds18b20() {
	cli(); // запрещаем прерывания, если есть
	bool check;
	DDRC |= (1<<1);
	PORTC &= ~(1<<1); // Занимаем линию данных
	_delay_us(500);
	DDRC &= ~(1<<1); // Отпускаем линию данных
	_delay_us(120); // 60
	if (~PINC & (1<<1))
	{
		check = true;
	} else {
		check = false;
	}
	sei(); // разрешаем прерывания, если есть
	_delay_us(380); // Ожидаем завершение слота времени
	return check;
}

// Запись байта данных в датчик температуры ds18b20

void write_byte (char one_byte) {
	for (char i = 0; i<8; i++) {
		if (one_byte & (1<<i)) {
			cli();
			DDRC |= (1<<1);
			//PORTC &= ~(1<<1);
			_delay_us(2); // Формируем "1"
			DDRC &= ~(1<<1);
			_delay_us(58); // Ожидаем окончание слота времени
			sei();
		} else {
			cli();
			DDRC |= (1<<1);
			//PORTC &= ~(1<<1);
			_delay_us(65); // Формируем "0"
			DDRC &= ~(1<<1);
			sei();	
		}
	}
}

// Функция чтения байта данных из датчика температуры ds18b20

int read_byte () {
	char byte_ds18b20 = 0;
	for(char i = 0; i < 8; i++) {
		cli();
		char bit_ds18b20 = 0;
		DDRC |= (1<<1);
		_delay_us(2);
		DDRC &= ~(1<<1);
		_delay_us(13);
		
		if (PINC & (1<<1)) {
			bit_ds18b20 = 1;
		} else {
			bit_ds18b20 = 0;
		}
		_delay_us(45);
		sei();
		
		//or
		//if (PINC & (1<<1)) {
		//	byte_ds18b20 |= (1<<i);
		//} else {
		//	byte_ds18b20 &= ~(1<<i);
		//}
		//or
		//bit_ds18b20 = PINC & (1<<1) >> 1;
		//or
		//byte_ds18b20 |= (PINC & (1<<1) >> 1) << i;
		
		byte_ds18b20 |= bit_ds18b20 << i;
		
	}
	
	return byte_ds18b20;
}

// Принимаем два байта от датчика температуры ds18b20
int two_bytes_ds18_b20 (void) {
	unsigned int byte_from_ds18b20 = 0;
	unsigned int bytes_from_ds18b20 = 0;
	
	if (check_ds18b20()) {
		write_byte(0xCC); // Пропуск ROM
		write_byte(0x44); // Команда датчику "Конвертировать температуру"
		_delay_ms(750); // 750 мс - время на конвертацию температуры при 12 бит
		check_ds18b20();
		write_byte(0xCC); // Пропуск ROM
		write_byte(0xBE); // команда датчику на чтение данных
		
		byte_from_ds18b20 = read_byte(); // Принимаем младший байт данных
		bytes_from_ds18b20 = read_byte(); // Принимаем старший байт данных
		
		bytes_from_ds18b20 = (bytes_from_ds18b20 << 8) | byte_from_ds18b20;
		// Получаем 16 бит (2 байта) данных температуры
	}
	
	return bytes_from_ds18b20;
}

// Преобразование двух байт температуры в температуру в градусах
int bytes_to_temperature (unsigned int two_bytes) {
	double temperature = 0;
	
	if (two_bytes >= 2048) {
		// Значит отрицательная температура
		temperature = ((~two_bytes) + 1) * 0.0625 * 10;
		negative_temperature = true;
		return temperature;
	} else {
		// Значит положительная температура
		temperature = two_bytes * 0.0625 * 10;
		negative_temperature = false;
		return temperature;
	}
}


int main(void)
{
	
	//7seg
	DDRC |= (1<<2) | (1<<3) | (1<<4) | (1<<5); 
	DDRD = 0b11111111;
	
	PORTC |= (1<<2) | (1<<3) | (1<<4) | (1<<5);
	//PORTD = 0b11111111;
	PORTD = 0b00000000;

	DDRB |= (1<<0); //LED;
		
	// 1000000/8
	//TCCR0 |= (1<<1);
	//TCCR0 &= ~((1<<0) | (1<<2));
	// 1000000/64
	TCCR0 |= (1<<1) | (1<<0);
	TCCR0 &= ~(1<<2);
	// 1000000/1024
	//TCCR0 |= (1<<2) | (1<<0);
	//TCCR0 &= ~(1<<1);	
	TIMSK |= (1<<0); //Timer/Counter0 Overflow Interrupt Enable
	TCNT0 = 0; // Timer/Counter Register
	sei();  // Status Register / Bit 7 – I: Global Interrupt Enable
	

    while (1) 
    {
/*		if (check_ds18b20()) {
			PORTB |= (1<<0);
		} else {
			PORTB &= ~(1<<0);
		}
		*/		

		//number(1234);		
		number(bytes_to_temperature(two_bytes_ds18_b20()));
		
		if (bytes_to_temperature(two_bytes_ds18_b20()) > 30*10)
		{
			PORTB &= ~(1<<0);
		} else if (bytes_to_temperature(two_bytes_ds18_b20()) < 26*10)
		{
			PORTB |= (1<<0);
		}


    }
}

