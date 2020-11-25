/*
 * Water Control Value.c
 *
 * Created: 11/25/2020 5:24:52 PM
 * Author : Bhanuka
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC=0x70;
	int counter=0;
    /* Replace with your application code */
    while (1) 
    {
		if(counter==50)
		{
			PORTC=PORTC | 1<<PC4;
			_delay_ms(1000);
			PORTC=PORTC & ~(1<<PC4);
		}else if(counter==100){
			PORTC=PORTC | 1<<PC5;
			_delay_ms(1000);
			PORTC=PORTC & ~(1<<PC5);
		}
		else if( counter==150)
		{
			
			PORTC=PORTC | 1<<PC6;
			_delay_ms(1000);
			PORTC=PORTC & ~(1<<PC6);
			counter=0;
		}
		counter++;
		
    }
}

