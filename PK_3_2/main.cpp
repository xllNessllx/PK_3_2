/*
 * PK_3_2.cpp
 *
 * Created: 07.11.2019 15:41:00
 * Author : Ness
 */ 

#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile int red = false;
volatile int yellow = false;

//isr aktiv
//falling edge
//gsr

void init(){
	DDRB = 0b11111111;
	DDRD = 0b00000000;
	
	PORTD = 0xFF;
}

void init_interrupt(){
	//Interrupts sperren
	cli();
	
	//Interrupt wird durch falling edge ausgelöst
	MCUCR |= (1 << ISC10);   
	//Interrupts registrieren
	GICR |= (1 << INT0) | (1 << INT1);
	
	//Interrupts freigeben
	sei();
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
    
	init();
	init_interrupt();
	
    while (1) 
    {
		
		if(!red && yellow){
			ledYellow();
		}
		
		if(red && !yellow){
			ledRed();
		}
		
    }
}

//PIND 2
ISR(INT0_vect){
	_delay_ms(200);
	red = !red;
	yellow = false;
}

//PIND 3
ISR(INT1_vect){
	_delay_ms(200);
	yellow = !yellow;
	red = false;
}
