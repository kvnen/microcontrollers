
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t timer_counter = 0;

ISR(TIMER0_COMPA_vect){
	TCNT0 = 0x00;
	timer_counter++;
}
int main(void){
	TCCR0A |= 0x02;
	TCCR0B |= 0x03;
	OCR0A |= 0xFA;
	TIMSK0 |= (1 << OCIE0A);
	DDRB |= 0x20;
	sei();
	while(1){
			if (timer_counter >= 500){
				timer_counter = 0;
				PORTB ^= 0x20;
					
			}
		}
}
