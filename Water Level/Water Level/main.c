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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <avr/io.h>
#include "adc.h"
#include "lcd.h"



int main(void)
{
	
	int value;
	

	ADC_Init();
	LCD_Init();
	char buffer [10];
	
   
    while (1) 
    {
		for(int i=3;i<6;i++){
			ADC_Init();
			
			value=ADC_Read(i);	/* Read ADC channel 0 */
			
			
			LCD_Clear();
			LCD_String("Sensor ");
			if(i==3){
				LCD_String("1");
			}else if(i==4){
				LCD_String("2");
			}
			else{
				LCD_String("3");
			}
			LCD_Command(0xC0);
			dtostrf(value,8,5,buffer);
			LCD_String(buffer);
			_delay_ms(200);
			
			
		}
		
		
		
		
		
    }
}

