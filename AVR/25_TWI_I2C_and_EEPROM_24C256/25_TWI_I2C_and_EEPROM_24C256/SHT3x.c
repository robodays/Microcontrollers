/////// Датчик SHT3x 
/////// Часть кода

unsigned char TWI_status = 0;
unsigned char TWI_data = 0;

unsigned char Tst = 0;
unsigned char Tml = 0;
unsigned int  T_16 = 0;
float		  Tf = 0;
int			  Temperature = 0;

unsigned char Hst = 0;
unsigned char Hml = 0;
unsigned int  H_16 = 0;
float		  Hf = 0;
int			  Humidity = 0;

/*
.........
*/

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


// Запись команд
void TWI_write (unsigned char twi_com)
{
	TWDR = twi_com;
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
}



int main(void)
{
   DDRB |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5); // Выводы управления разрядами семисегментного индикатора
   PORTB |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5); // Изначально все разряды погасшие
	
	  
   DDRD |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7); // Выводы управления сегментами семисегментного индикатора
   PORTD &= ~((1<<0) | (1<<1) |(1<<2) | (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7)); // Изначально все сегменты погасшие
     

	sei ();
	
	timer0_settings ();
	
	
	TWI_settings ();
	
	
	TWI_start();
	
	TWI_write(0b10001000); // Адрес + W
	
	TWI_write(0x21); // Запись старшего байта в регистр команд
		
	TWI_write(0x26); // Запись младшего байта в регистр команд	
	
	_delay_ms(50); // Проверить!!! Можно и не ставить задержку
	
	TWI_start(); 
	
	//TWI_status = TWSR;
	
	TWI_write(0b10001001); // Адрес + R
	
	////////////// Прием данных от датчика!!!!
	
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
	
	Tst = TWDR; // Принимаем старший байт температуры
	
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
	
	Tml = TWDR; // Принимаем младший байт температуры
	
	T_16 = (Tst<<8) | Tml;
	Tf = (float)T_16/65535*175.0;
	Temperature = Tf - 45; // Температура по Цельсию
	
	// Принимаем контрольную сумму по температуре
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
	
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
	
	Hst = TWDR; // Принимаем старший байт влажности
	
	TWCR = (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
	
	Hml = TWDR; // Принимаем младший байт влажности
	
	H_16 = (Hst << 8) | Hml;
	Hf = (float)H_16/65535*100.0;
	Humidity = Hf;
	
	
	// Принимаем контрольную сумму по влажности
	TWCR = (1<<TWINT) | (1<<TWEN);
	while (!(TWCR&(1<<TWINT)))
	;
	
	_delay_ms(5); //Проверить!!! Можно и не ставить задержку
	
	TWI_stop();
	
    while (1) 
    {
		
		
		number1(Temperature);
		
		number2(Humidity);
		
		
    }
}