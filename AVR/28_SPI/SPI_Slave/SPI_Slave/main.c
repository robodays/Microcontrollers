/*
 * SPI_Slave.c
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

int r1_1000 = 0;
int r2_100 = 0;
int r3_10 = 0;
int r4_1 = 0;

int cnt=0;


int digits [10] = {
	0b00111111,  // 0
	0b00000110,  // 1
	0b01011011,  // 2
	0b01001111,  // 3
	0b01100110,  // 4
	0b01101101,  // 5
	0b01111101,  // 6
	0b00000111,  // 7
	0b01111111,  // 8
	0b01101111   // 9
};



void number (unsigned int num)
{
	r1_1000 = num/1000;		// ������
	r2_100 = num%1000/100;	// �����
	r3_10 = num%100/10;		// �������
	r4_1 = num%10;			// �������
}

ISR(TIMER0_OVF_vect)
{	
	if (cnt==1)
	{
		PORTC |= (1<<3) | (1<<2) | (1<<1);
		PORTC &= ~(1<<0);
		PORTD = digits [r1_1000]; // �����
		
	}
	else if (cnt==2)
	{
		PORTC |= (1<<3) | (1<<2) | (1<<0);
		PORTC &= ~(1<<1);
		PORTD = digits [r2_100]; // �������
	}
	else if (cnt==3)
	{
		PORTC |= (1<<3) | (1<<1) | (1<<0);
		PORTC &= ~(1<<2);
		PORTD = digits [r3_10]; // �������
	}
	else if (cnt==4)
	{
		PORTC |= (1<<2) | (1<<1) | (1<<0);
		PORTC &= ~(1<<3);
		PORTD = digits [r4_1]; // �������
	}
	
	cnt++;
	if(cnt>8) cnt=1;
	
}


// ��������� SPI_Slave
void SPI_Slave_Settings (void)
{
	DDRB &= ~((1<<MOSI) | (1<<SCK));
	DDRB |= (1<<MISO);
	
	SPCR |= (1<<SPIE); // ��������� ���������� �� SPI
	SPCR |= (1<<SPE); // �������� SPI
	SPCR &= ~(1<<MSTR); // �� Slave
	
	// ������� �� ���������, �.�. ������� �� �������
	
	SPCR |= (1<<CPOL); // �������� ������������� ����������
	SPCR |= (1<<CPHA); // ������� ������ �� ������� ������
	SPCR &= ~(1<<DORD); // ������ ���������� ������� ���
	
	DDRB &= ~(1<<SS);
	PORTB |= (1<<SS);
	
}

ISR(SPI_STC_vect)
{
	while(~SPSR&(1<<SPIF))
	;
	counter = SPDR;
}


int main(void)
{
	// �������� ����������
	DDRD = 0xff;
	PORTD = 0x00;
	
	// ������� ����������
	DDRC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
	PORTC |= (1<<3) | (1<<2) | (1<<1) | (1<<0);
	
	TCCR0 = 0b00000010; // ����� ������� �� �� 8
	TCNT0 = 0;
	TIMSK |= (1<<TOIE0); // ��������� ���������� ��� ������������ 0-�� ��
	
	SPI_Slave_Settings();
	
	sei();

	while (1)
	{
		number(counter);
	}
}

