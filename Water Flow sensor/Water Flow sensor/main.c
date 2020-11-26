#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>
#include "lcd.h"

float time_clock=0;      //Count the time
float pulses[3]={0,0,0};          //Store digital pulses from the sensor
volatile uint8_t tot_overflow;   //To count the time to overflow


void timer0_int();
int clk();
void display(float rate,int sensor);
int main(void)
{
	LCD_Init();
	timer0_int();
	
	GICR |= 1<< INT0;     //Enable the external interrupt source in general interrupt control register
	GICR |= 1<< INT1;     //Enable the external interrupt source in general interrupt control register
	GICR |= 1<< INT2;     //Enable the external interrupt source in general interrupt control register
	
	MCUCR |= 1<<ISC01;    //interrupt fire on falling edge in INT0
	MCUCR |= 1<<ISC11;    //interrupt fire on falling edge in INT1
	
	MCUCSR |= 0<<ISC2;    //interrupt fire on falling edge in INT2
	
	
	
	
	
	
	
	
	while(1){
		while(clk()!=1);  //wait 1 second
		time_clock++;  //increase the clock by 1 second
		for (int i=0;i<3;i++)
		{
			float l_minutes=(pulses[i])/7.5;  //calculation
			display(l_minutes,i);              //display the liter/hour flow rate
			pulses[i]=0;                        //reset the pulse variable
		}
		
			
		
		
	}
	
}
int clk(){
	if (tot_overflow>=24)
	{
		if(TCNT0>=106){
			TCNT0=0;
			tot_overflow=0;
			return 1;
		}
	}
		return 0;
}
void display(float rate,int sensor){
	
	char out_str[30] ;
	
	dtostrf(rate,6,4,out_str);
	LCD_String("Flow Rate of ");
	if (sensor==0)
	{
		LCD_String("1");
	}else if(sensor==1){
		LCD_String("2");
		}else{
			LCD_String("3");
		}
	LCD_String(" : ");
	LCD_Command(0xc0);
	LCD_String(out_str);
	LCD_String(" liter/Min");
	
	LCD_Clear();
	
	
	
	
}
void timer0_int(){
	TCCR0 |= 1<<CS02;            //set the prescaler to 256
	TCNT0=0;                     //reset the timer
	TIMSK |= 1<<TOIE0;           //Enable the timer overflow interrupt
	sei();                       //enable global interrupts
	tot_overflow=0;
}
ISR(TIMER0_OVF_vect){
	tot_overflow++;
}
ISR(INT0_vect){
	pulses[0]++;
}

ISR(INT1_vect){
	pulses[1]++;
}

ISR(INT2_vect){
	pulses[2]++;
}

