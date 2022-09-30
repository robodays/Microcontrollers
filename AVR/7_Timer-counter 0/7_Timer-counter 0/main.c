#define F_CPU 1000000UL

#include <avr/io.h>


int main(void)
{
	
	DDRD = 0b11111111;
	
	PORTD = 0b00000000;
	
	TCCR0 = 0b00000101; // initialization Timer/Counter Control Register – TCCR0 clkI/O/1024 (From prescaler) // T = 1024/1000000 = 0,001024 sec
	// or so
	//TCCR0 |= ((1<<0) | (1<<2));
	//TCCR0 &= ~(1<<1);
	// or so
	//TCCR0 |= ((1<<CS00) | (1<<CS02));
	//TCCR0 &= ~(1<<CS01);
	
	// clkI/O/256 (From prescaler)
	//TCCR0 |= (1<<2);
	//TCCR0 &= ~((1<<0) | (1<<1));
	
	
	TCNT0 = 0; // Timer/Counter Register – TCNT0 8bit (max255)  1Bt = 0,001024 * 256 = 0,262144 sec
	
	int d = 0;
    while (1) 
    {
		if (TCNT0 == 128)
		{
			//PORTD = 0b10101000;
		}
		
		if (TCNT0 == 255)
		{
			//PORTD = 0b01010100;
			d++;
			TCNT0 = 0;
		}
		
		if (d < 20)
		{
			//PORTD = 0b10101000;
			
			PORTD |= (1<<0);
		} else
		if (d > 20) {
			//PORTD = 0b01010100;

			PORTD &= ~(1<<0);
		}
		if (d >= 40) {
			d = 0;
		}

    }
}

