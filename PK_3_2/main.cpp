/*
 * PK_3_2.cpp
 *
 * Created: 07.11.2019 15:41:00
 * Author : Ness
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 1000000UL
bool red = false;
bool yellow = false;

//PIND 2
ISR(INT0_vect){
	red = true;
	yellow false;
}

//PIND 3
ISR(INT1_vect){
	red = false;
	yellow = true;
}

void init(){
	DDRB = 0b11111111;
	DDRC = 0b00000000;
	
	PORTC = 0xFF;
}

void ledRed(){
	PORTB = (1 << PB0);
	_delay_ms(200);
	PORTB = (0 << PB0);
	_delay_ms(200);
}

void ledYellow(){
	PORTB = (1 << PB1);
	_delay_ms(200);
	PORTB = (0 << PB1);
	_delay_ms(200);
}

int main(void)
{
    
	init()
	
    while (1) 
    {
		if(red && !yellow){
			ledRed();
		}
		else if(!red && yellow){
			ledYellow();
		}
		else if(!red && !yellow){
			//Kein Switch aktiviert
		}
    }
}

