//дл€ настройки плавающей точки
//menu->ptoject-Properties
//Toolchain->AVR/GNU Linker->General [v] Use vprintf library
//Toolchain->AVR/GNU Linker->Libraries ^+ printf_flt

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int m1 = 45;
int m2 = 55;
float voltage = 0;

// Baud Rate Registers
void UART_settings (unsigned int ubrr) {
	
	// Baud Rate Registers
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) (ubrr);
	
	// Bit 1 Ц U2X: Double the USART transmission speed
	UCSRA |= (1<<U2X);
	
	//Bit 4 Ц RXEN: Receiver Enable
	//Bit 3 Ц TXEN: Transmitter Enable
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	//Bit 7 Ц URSEL: Register Select
	//Bit 3 Ц USBS: Stop Bit Select -> 2bits
	//Bit 2:1 Ц UCSZ1:0: Character Size -> 8bits
	UCSRC = (1<<URSEL) | (1<<USBS) | (1<<UCSZ1) | (1<<UCSZ0);
}

void ADC_settings (void)
{
	DDRC &= ~(1<<3);
	ADCSRA |= (1<<ADEN);
	ADCSRA |= (1<<ADFR);
	
	ADCSRA &= ~(1<<ADPS2);
	ADCSRA |= (1<<ADPS1) |(1<<ADPS0);
	
	ADMUX |= (1<<REFS0);
	ADMUX &= ~(1<<REFS1);
	
	ADMUX &= ~(1<<ADLAR);
	
	ADMUX &= ~((1<<MUX3) | (1<<MUX2));
	ADMUX |= (1<<MUX1) | (1<<MUX0);
	
	ADCSRA |= (1<<ADSC);
}

// ‘ункци€, вызываема€ при обращении потока на ввод символа
static int uart_put_char(char ch, FILE *stream) {
	while (~UCSRA & (1<<UDRE)) {}
	UDR = ch;
	return 0;
}

// ‘ункци€, вызываема€ при обращении потока на ввод символа
static int uart_get_char (FILE *stream)
{
	while (~UCSRA & (1<<RXC))
	;
	return UDR;
}

//—оздаем свой поток данных с имененем mystdout,
//назначаем функцию uart_put_char дл€ вывода
//‘ункцию ввода не назначаем, поэтому пишем NULL
//ѕоскольку используем только ввод, от
//устанавливаем флаг _FDEV_SETUP_WRITE
//static FILE myStdOut = FDEV_SETUP_STREAM(uart_put_char, NULL, _FDEV_SETUP_WRITE);

static FILE myStdInOut = FDEV_SETUP_STREAM (uart_put_char, uart_get_char, _FDEV_SETUP_RW);

int main(void)
{
	UART_settings(12); // data transfer rate 9600, by Fmc = 1000000 Hz, U2X = 1

	ADC_settings();


	DDRB = 0xff;
	PORTB = 0x00;
	
	//stdout = &myStdOut;
	stdout = &myStdInOut;
	stdin = &myStdInOut;
	
	//printf("Hello, World\r\n");
	//printf("m1=%d, m2=%d, m1+m2=%d\r\n", m1, m2, m1+m2);
	
	while (1)
	{
		/*
 		if (ADCSRA & (1<<ADIF))
 		{
 			voltage = (ADC*5.0)/1024;
 			//printf("Good!\r\n");
 			printf("Voltage = %.2f\r\n", voltage);
 			ADCSRA |= (1<<4);
 		}
		*/
		
		printf("Enter digit(0-9)\r\n");
		printf("Menu: \r\n");
		printf("Exit - enter 'q'");
		printf("0: all LOW\r\n");
		printf("1: PB0 LOW/HIGH\r\n");
		printf("2: PB1 LOW/HIGH\r\n");
		printf("3: PB2 LOW/HIGH\r\n");
		printf("4: PB3 LOW/HIGH\r\n");
		printf("5: PB4 LOW/HIGH\r\n");
		printf("6: PB5 LOW/HIGH\r\n");
		printf("7: PB6 LOW/HIGH\r\n");
		printf("8: PB7 LOW/HIGH\r\n");
		printf("9: all HIGH\r\n");
		
		//printf("You entered %c\r\n", getchar());
		
		/*if (getchar() == 'q'){
			printf("Good bye!\r\n");
			break;
		}*/
		switch(getchar())
		{
			case '0': PORTB = 0x00; printf("You entered 0\r\n"); break;
			case '1': if(PINB & (1<<0)){PORTB &= ~(1<<0);}else{PORTB |= (1<<0);} printf("You entered 1\r\n"); break;
			case '2': if(PINB & (1<<1)){PORTB &= ~(1<<1);}else{PORTB |= (1<<1);} break;
			case '3': if(PINB & (1<<2)){PORTB &= ~(1<<2);}else{PORTB |= (1<<2);} break;
			case '4': if(PINB & (1<<3)){PORTB &= ~(1<<3);}else{PORTB |= (1<<3);} break;
			case '5': if(PINB & (1<<4)){PORTB &= ~(1<<4);}else{PORTB |= (1<<4);} break;
			case '6': if(PINB & (1<<5)){PORTB &= ~(1<<5);}else{PORTB |= (1<<5);} break;
			case '7': if(PINB & (1<<6)){PORTB &= ~(1<<6);}else{PORTB |= (1<<6);} break;
			case '8': if(PINB & (1<<7)){PORTB &= ~(1<<7);}else{PORTB |= (1<<7);} break;
			case '9': PORTB = 0xff; printf("You entered 9\r\n"); break;
			default: printf("ERROR! Please, enter digit in the range 0...9\r\n");
		}
		
	}
}




