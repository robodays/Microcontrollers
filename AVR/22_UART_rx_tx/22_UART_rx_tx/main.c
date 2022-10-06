

#include <avr/io.h>
#include <string.h>

// Baud Rate Registers
void UART_settings (unsigned int ubrr) {
	
	// Baud Rate Registers
	UBRRH = (unsigned char) (ubrr >> 8);
	UBRRL = (unsigned char) (ubrr);
	
	// Bit 1 – U2X: Double the USART transmission speed
	UCSRA |= (1<<U2X);
	
	//Bit 4 – RXEN: Receiver Enable
	//Bit 3 – TXEN: Transmitter Enable
	UCSRB = (1<<RXEN) | (1<<TXEN);
	
	//Bit 7 – URSEL: Register Select
	//Bit 3 – USBS: Stop Bit Select -> 2bits
	//Bit 2:1 – UCSZ1:0: Character Size -> 8bits
	UCSRC = (1<<URSEL) | (1<<USBS) | (1<<UCSZ1) | (1<<UCSZ0);
}

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	// Bit 5 – UDRE: USART Data Register Empty
	// If UDRE is one, the buffer is empty, and therefore ready to be written.
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}

void send_str(unsigned char *str) {
	while (*str != '\0')
	{
		/* Wait for empty transmit buffer */
		// Bit 5 – UDRE: USART Data Register Empty
		// If UDRE is one, the buffer is empty, and therefore ready to be written.
		while ( !( UCSRA & (1<<UDRE)) )
		;
		/* Put data into buffer, sends the data */
		UDR = *str;
		
		str++;
	}
}

int main(void)
{
	UART_settings(12); // data transfer rate 9600, by Fmc = 1000000 Hz, U2X = 1

	USART_Transmit('T');
	USART_Transmit('e');
	USART_Transmit('s');
	USART_Transmit('t');
	USART_Transmit('\r');
	USART_Transmit('Ò');
	USART_Transmit('å');
	USART_Transmit('ñ');
	USART_Transmit('ò');
	
	USART_Transmit('\r');
	
	//char str[] = "Hello World";
	uint8_t str[] = "Hello World";
	uint8_t iStr = 0;
	
	DDRB = 0xff;
	
	while (1)
	{
		if (UCSRA & (1<<UDRE) && (iStr < sizeof(str)-1/*strlen(str)*/))
		{
			UDR = str[iStr];
			iStr++;
		}
		
		if (UCSRA & (1<<RXC))
		{
			uint8_t udr_id = UDR;
			//PORTB = udr_id - 48;
			PORTB = udr_id;
			
			//USART_Transmit(udr_id);
			
			//unsigned char str[] = "Hello\r\n";
			unsigned char str[] = "Day#X\r\n";
			str[4] = udr_id;
			//send_str(&str[0]);
			send_str(str);
		}

	}
}


