#include <avr/io.h>
#include <avr/delay.h>
#include <util/delay.h>

int main(){
	DDRB = 0xFF;
	while(1){
		_delay_ms(1000);
		PORTB ^= 0b00100000;
	}
	return 0;

}
