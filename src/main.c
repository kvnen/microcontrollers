#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
volatile unsigned long timesec = 0;
ISR(TIMER1_COMPA_vect){
	timesec++;
}
void inittimer(){
	TCCR1A = 0b00000000;
	TCCR1B = 0b00001011;
	OCR1A = 249;
	TIMSK1 = 0x02;
}
void initpwm(){
	TCCR0A = 0b10000011;
	TCCR0B = 0b00000100;
	OCR0A = 0;
	TIMSK0 = 0x00;
	DDRD |= (1 << PB6);
}
void delay(unsigned short x){
	unsigned long newtime = timesec + x;
	while(1){
			if(timesec < newtime){
				continue;
			}else{
				return;
			}
		}
}
int main(void){
	inittimer();
	initpwm();
	sei();
	bool leddir = true;
	while(1){
		delay(10);
		if(OCR0A <= 2)
		{
			leddir = true; 
		}
		else if(OCR0A >= 254)
		{
			leddir = false;
		}
		if(leddir == true)
		{
			OCR0A++;
		}else{
			OCR0A--;
		}
		}
}
