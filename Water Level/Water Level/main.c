/*
 * Water Level.c
 *
 * Created: 11/25/2020 5:12:51 AM
 * Author : Bhanuka
 */ 
#ifndef F_CPU
#define F_CPU 8000000UL /* Define CPU Frequency e.g. here its 8MHz */
#endif

#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */

#include <avr/io.h>
#include "adc.h"



int main(void)
{
	
	int value;
	DDRD=0xff;

	ADC_Init();
	
    int const measure=50;
    while (1) 
    {
		for(int i=3;i<6;i++){
			value=ADC_Read(i);	/* Read ADC channel 0 */
			if(value>measure){
				PORTD=PORTD |(1<<i);
			}
			else{
				PORTD=PORTD & ~(1<<i);
			}
		}
		
		
		
		
		
    }
}

