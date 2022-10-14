/*
 * SPI_Master.c
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SS 2
#define MOSI 3
#define MISO 4
#define SCK 5

int counter = 0;

// Настройки SPI_Master
void SPI_Master_Settings (void)
{
	DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SS);
	PORTB |= (1<<SS); // "Этот пин нужно установить раньше
	// настроек регистра контроля, т.е. раньше команды SPCR |= (1<<MSTR)
	DDRB &= ~(1<<MISO);
	SPCR |= (1<<SPIE); // Разрешаем прерывания по SPI
	SPCR |= (1<<SPE); // Включаем SPI
	SPCR |= (1<<MSTR); // МК Master
	SPSR &= ~(1<<SPI2X); // Без удвоения частоты
	
	// Делим частоту МК на 16
	SPCR &= ~(1<<SPR1);
	SPCR |= (1<<SPR0);
	
	SPCR |= (1<<CPOL); // Импульсы отрицательной полярности
	SPCR |= (1<<CPHA); // Выборка данных по заднему фронту
	SPCR &= ~(1<<DORD); // Первым передается старший бит
	
}

ISR (SPI_STC_vect)
{
	while(~SPSR&(1<<SPIF))
	;
	PORTB |= (1<<SS);
}



int main(void)
{
    // Кнопки
    DDRC &= ~((1<<1) | (1<<0));
    PORTC |= (1<<1) | (1<<0);
    
    SPI_Master_Settings();
    sei();
	
	
    while (1) 
    {
		if (~PINC&(1<<0))
		{
			counter++;
			if(counter>=100) counter = 100;
			PORTB &= ~(1<<SS);
			SPDR = counter;
			_delay_ms(300);
		}
		
		if (~PINC&(1<<1))
		{
			counter--;
			if(counter<=0) counter = 0;
			PORTB &= ~(1<<SS);
			SPDR = counter;
			_delay_ms(300);
		}
		
    }
}

