/*
 * 29_SPI_MAX6675_converter_and_thermocouple.c
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SS 2
#define MOSI 3
#define MISO 4
#define SCK 5

unsigned int r1_1000 = 0, r2_100 = 0, r3_10 = 0, r4_1=0;
int cnt = 0;

unsigned char High_Byte = 0;
unsigned char Low_Byte = 0;

unsigned int Temper_bits = 0;
float Temperature = 0;


int digits [10] = {
	0b00111111, //0
	0b00000110, //1
	0b01011011, //2
	0b01001111, //3
	0b01100110, //4
	0b01101101, //5
	0b01111101, //6
	0b00000111, //7
	0b01111111, //8
	0b01101111 //9
};


ISR(TIMER0_OVF_vect)
{
	if (cnt==1)
	{
		PORTC |= (1<<3) | (1<<2) | (1<<1);
		PORTC &= ~(1<<0);
		PORTD = digits [r1_1000]; // Сотни
	}
	else if (cnt==2)
	{
		PORTC |= (1<<3) | (1<<2) | (1<<0);
		PORTC &= ~(1<<1);
		PORTD = digits [r2_100]; // Десятки
	}
	else if (cnt==3)
	{
		PORTC |= (1<<3) | (1<<1) | (1<<0);
		PORTC &= ~(1<<2);
		PORTD = digits [r3_10]; // Единици
	}
	else if (cnt==4)
	{
		PORTC |= (1<<2) | (1<<1) | (1<<0);
		PORTC &= ~(1<<3);
		PORTD = digits [r4_1]; // Единици
	}
	
	cnt++;
	
	if (cnt>4) cnt=1;
	
	
}

void number(unsigned int num)
{
	r1_1000 = num/1000; // Тысячи
	r2_100 = num%1000/100; // Сотни
	r3_10  = num%100/10; // Десятки
	r4_1   = num%10; // Единици

}

// Настройки SPI_Master
void SPI_Master_Settings ()
{
	//DDRB |= (1<<MOSI) | (1<<SCK) | (1<<SS);
	DDRB |= (1<<SCK) | (1<<SS);
	PORTB |= (1<<SS); // "Этот пин нужно установить раньше
	// настроек регистра контроля, т.е. раньше команды SPCR |= (1<<MSTR)
	DDRB &= ~(1<<MISO);
	//SPCR |= (1<<SPIE); // Разрешаем прерывания по SPI
	SPCR |= (1<<SPE); // Включаем SPI
	SPCR |= (1<<MSTR); // МК Master
	SPSR &= ~(1<<SPI2X); // Без удвоения частоты
	// Делим частоту МК на 16
	SPCR &= ~(1<<SPR1);
	SPCR |= (1<<SPR0);
	//SPCR |= (1<<CPOL); // Импульсы отрицательной полярности
	SPCR &= ~(1<<CPOL); // Импульсы положительной полярности
	SPCR |= (1<<CPHA); // Выборка данных по заднему фронту
	SPCR &= ~(1<<DORD); // Первым передается старший бит
	
}

// Функция приема данных
unsigned char Receiver_SPI_Master ()
{
	SPDR = 0xff;
	while(~SPSR&(1<<SPIF))
	;
	return SPDR;
}

int main(void)
{
    // Сегменты индикатора
    DDRD = 0xff;
    PORTD = 0x00;
    
    // Разряды индикатора
    DDRC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
    PORTC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
    
    TCCR0 = 0b00000010; // Делим частоту МК на 8
    TCNT0 = 0;
    TIMSK |= (1<<TOIE0); // Разрешаем прерывания при переполнении 0-от ТС

    SPI_Master_Settings ();
    

    sei();
	
    while (1) 
    {
		//_delay_ms(250); // Задержка на преобразование АЦП
		PORTB &= ~(1<<SS);
		High_Byte = Receiver_SPI_Master();
		Low_Byte = Receiver_SPI_Master();
		PORTB |= (1<<SS);
		Temper_bits = (High_Byte << 5) | (Low_Byte >> 3);
		Temperature = (float)Temper_bits*0.25; // Температура в Цельсиях
		//Temperature = (float)Temper_bits*9.0/5.0 + 32; // Температура в Фаренгейтах

		//number(1234);
		number(Temperature);
    }
}

