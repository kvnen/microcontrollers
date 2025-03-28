
#include <avr/io.h>
#include <avr/interrupt.h>
// has to be volatile so the compiler doesnt fuck it up
volatile uint16_t timer_counter = 0;
//interrupt service routine when timer 0 comparator A is reached
ISR(TIMER0_COMPA_vect){
	timer_counter++;
}
int main(void){
	//set the timer to CTC so that the timer is cleared when it reaches a comparison?
	TCCR0A |= 0x02;
	//set the prescaler to divide by 64
	TCCR0B |= 0x03;
	//set the comparison A to 250 so that it is met every 1ms
	OCR0A |= 0xFA;
	//set comparison A enable
	TIMSK0 |= (1 << OCIE0A);
	//set all Port B to output 
	DDRB |= 0xFF;
	//set portb4 high so that when the timer counter reaches 500 it switches between the 2
	PORTB = 0x10;
	//set enable interrupts to enable global interrupts
	sei();
	//just some basic shit ya know ya know
	while(1){
			if (timer_counter >= 500){
				timer_counter = 0;
				PORTB ^= 0x30;
					
			}
		}
}
