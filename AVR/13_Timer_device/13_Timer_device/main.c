#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define DELAY 300

int digits16[10] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f};

int digits[4];

char discharge = 1; // digit of a number

int num = 0;

void start() {
	TCCR1B &= ~(1<<CS12);
	TCCR1B |= (1<<CS11) | (1<<CS10); // 1000000 / 64 = 15625 tickû
	
	TIMSK |= (1<<OCIE1A); // Bit 4 – OCIE1A: Timer/Counter1, Output Compare A Match Interrupt Enable
	
	// comparison register 15625
	OCR1AH = 0b00111101;
	OCR1AL = 0b00001001;
	
	TCNT1 = 0;
	
	TCCR1B |= (1<<WGM12); // automatic reset when comparing
	
	
	
}

void number(int num) {
	
	digits[0] = num/1000;
	digits[1] = num % 1000 / 100;
	digits[2] = num % 100 / 10;
	digits[3] = num % 10;
}

ISR (TIMER0_OVF_vect) {
	if (discharge == 1) {PORTB = 0b00000001; PORTD = digits16[digits[0]];}
	if (discharge == 2) {PORTB = 0b00000010; PORTD = digits16[digits[1]];}
	if (discharge == 3) {PORTB = 0b00000100; PORTD = digits16[digits[2]];}
	if (discharge == 4) {PORTB = 0b00001000; PORTD = digits16[digits[3]]; discharge = 0;}
	discharge++;

}

ISR (TIMER1_COMPA_vect) {
	num--;
	if (num < 0) {
		num = 0;
	}
	if (num == 0) {
		PORTC |= (1<<2);
	} else {
		PORTC &= ~(1<<2);
	}
}

int main(void)
{
	DDRD = 0b11111111;
	DDRB = 0b00001111;

	DDRC &= ~((1<<3) |(1<<4) | (1<<5)); // button
	DDRC |= (1<<2); // speaker
	
	PORTD = 0b00000000;
	PORTB = 0b00001111;

	PORTC |= (1<<3) | (1<<4) | (1<<5); // button
	PORTC &= ~(1<<2); // speaker
	

	
	// 1000000/64
	TCCR0 |= (1<<0) | (1<<1);
	TCCR0 &= ~(1<<2);

	TIMSK |= (1<<0); //Timer/Counter0 Overflow Interrupt Enable
	TCNT0 = 0; // Timer/Counter Register
	sei();  // Status Register / Bit 7 – I: Global Interrupt Enable
	
	while (1)
	{
		number(num);
		if (~PINC & (1<<4))
		{
			num++;
			_delay_ms(DELAY);
			if (num > 9999) num = 0;
		}
		if (~PINC & (1<<5))
		{
			num--;
			_delay_ms(DELAY);
			if (num < 0) num = 9999;
		}
		
		if (~PINC & (1<<3))
		{
			start();
			_delay_ms(DELAY);
		}
		
		//PC6 automatic reset by default

	}
}


