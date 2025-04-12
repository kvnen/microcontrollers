#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
volatile unsigned long timesec = 0;
ISR(TIMER1_COMPA_vect){
	timesec++;
}
void initTimer(){
	TCCR1A = 0b00000000;
	TCCR1B = 0b00001011;
	OCR1A = 255;
	TIMSK1 = 0x02;
}
void initPWM(){
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
void fadeLed(unsigned short fadetime,unsigned char percentage){
	unsigned char value = 2.55 * percentage; 

	if(OCR0A > value){ 
		unsigned char delaytime = fadetime/(OCR0A - value);
		for(; OCR0A > value; OCR0A--){
			delay(delaytime);
		}
	}
	else if (OCR0A < value){
		unsigned char delaytime = fadetime/(value - OCR0A);
		for(; OCR0A < value; OCR0A++){
			delay(delaytime);
		}
	}
	else return;
}
int main(void){
	initTimer();
	initPWM();
	sei();
	

	while(1){
			fadeLed(2000, 100);
			fadeLed(2000, 0);
		}
}
