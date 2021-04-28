/*
 * Final Code.c
 *
 * Created: 4/14/2021 1:38:36 AM
 * Author : Bhanuka
 */ 
#ifndef F_CPU
#define F_CPU 16000000UL
#endif



#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <math.h>
#include "lcd.h"
#include "adc.h"

float time_clock=0;      //Count the time
float pulses[3]={0,0,0};          //Store digital pulses from the sensor
volatile uint8_t tot_overflow;   //To count the time to overflow


void timer0_int();
int clk();

int main(void)
{
	TCNT1 = 0;		/* Set timer1 count zero */
	ICR1 = 2499;		/* Set TOP count for timer1 in ICR1 register */
	
	TCCR1A = (1<<WGM11)|(1<<COM1A1);
	TCCR1B = (1<<WGM12)|(1<<WGM13)|(1<<CS10)|(1<<CS11);
    
   while (1)
   {
	   DDRC = 0x70;
	   DDRD=0x20;
	   DDRA=0x00;
	   DDRB=0xF3;
	   PORTC=0x0F;
	   PORTD=PORTD | (1<<PD7);
	   int stepOne= PIND & (1<<PD7);
	   timer0_int();
	   
	   
	   MCUCR |= 1<<ISC01;    //interrupt fire on falling edge in INT0
	   MCUCR |= 1<<ISC11;    //interrupt fire on falling edge in INT1
	   MCUCSR |= 0<<ISC2;    //interrupt fire on falling edge in INT2
	   
	   
	   GICR |= 1<< INT0;     //Enable the external interrupt source in general interrupt control register
	   GICR |= 1<< INT1;     //Enable the external interrupt source in general interrupt control register
	   GICR |= 1<< INT2;     //Enable the external interrupt source in general interrupt control register
	   
	   
	   sei();               //enable global interrupts
	 
	   if(!stepOne)
	   {
		   
		   //Juice machine Starting
		  LCD_Init();			/* Initialization of LCD*/

		  LCD_String("Welcome to");	/* Write string on 1st line of LCD*/
		  LCD_Command(0xC0);		/* Go to 2nd line*/
		  LCD_String("Juice Buddy");	/* Write string on 2nd line*/
		  _delay_ms(100);
		  LCD_Clear();
		    LCD_String("Please Choose");	/* Write string on 1st line of LCD*/
		    LCD_Command(0xC0);		/* Go to 2nd line*/
		    LCD_String("Your Juice");	/* Write string on 2nd line*/
		    _delay_ms(100);
			LCD_Clear();
	   
	   }
	   //checking user opinion
	   int apple= PINC & (1<<PC0);
	   int lime= PINC & (1<<PC1);
	   int orange= PINC & (1<<PC2);
	   int ice= PINC & (1<<PC3);
	   int app,lim,ora,iceWa;
	   int count=0;
	   if(!apple){
		   LCD_String("apple");	
		   _delay_ms(100);
		   LCD_Clear();
		   app=1;
		   count++;
	   }else{
		   app=0;
	   }
	   
	   if(!lime){
		   LCD_String("lime");	
		   _delay_ms(100);
		   LCD_Clear();
		   lim=1;
		   count++;
	   }
	   else{
		   lim=0;
	   }
	   if(!orange){
		   LCD_String("orange");	
		   _delay_ms(100);
		   LCD_Clear();
		   ora=1;
		   count++;
	   }else{
		   ora=0;
	   }
	   if(!ice){
		   LCD_String("ice");	
		   _delay_ms(100);
		   iceWa=1;
		   LCD_Clear();
		   
	   }else{
		   iceWa=0;
	   }
	   
	   //volume of each juice
	   double amount=500/count;
	   
	   float calibration_value = 21.34;
	   
	   unsigned long int avgval;
	   int buffer_arr[10],temp;
	   char Ph[20];
	   int con=0;
	   
	   ADC_Init();
	   
	   //check apple ph
	   if(app==1){
		   for(int i=0;i<10;i++)
		   {
			   buffer_arr[i]=ADC_Read(0);
			   _delay_ms(30);
		   }
		   for(int i=0;i<9;i++)
		   {
			   for(int j=i+1;j<10;j++)
			   {
				   if(buffer_arr[i]>buffer_arr[j])
				   {
					   temp=buffer_arr[i];
					   buffer_arr[i]=buffer_arr[j];
					   buffer_arr[j]=temp;
				   }
			   }
		   }
		   avgval=0;
		   for(int i=2;i<8;i++)
		   avgval+=buffer_arr[i];
		   float volt=(float)avgval*5.0/1024/6;
		   float ph_act = -5.70 * volt + calibration_value;
		   if(ph_act>3.35 && ph_act<4.00){
			   con=1;
			    LCD_String("Apple PH is ");
			   LCD_Command(0xc0);
			   dtostrf(ph_act,8,5,Ph);
			   LCD_String(Ph);
			    _delay_ms(100);
			    LCD_Clear();
			   
		   }else{
			   con=0;
			     LCD_String("Apple PH is ");
			     LCD_Command(0xc0);
			     LCD_String("not good");
			     _delay_ms(100);
			     LCD_Clear();
			   
		   }
		   
	   }
	   
	   
	   
	//check lime ph   
	   	   if(lim==1){
		   	   for(int i=0;i<10;i++)
		   	   {
			   	   buffer_arr[i]=ADC_Read(1);
			   	   _delay_ms(30);
		   	   }
		   	   for(int i=0;i<9;i++)
		   	   {
			   	   for(int j=i+1;j<10;j++)
			   	   {
				   	   if(buffer_arr[i]>buffer_arr[j])
				   	   {
					   	   temp=buffer_arr[i];
					   	   buffer_arr[i]=buffer_arr[j];
					   	   buffer_arr[j]=temp;
				   	   }
			   	   }
		   	   }
		   	   avgval=0;
		   	   for(int i=2;i<8;i++)
		   	   avgval+=buffer_arr[i];
		   	   float volt=(float)avgval*5.0/1024/6;
		   	   float ph_act = -5.70 * volt + calibration_value;
		   	   if(ph_act>2.00 && ph_act<2.35){
					  con=1;
			   	   LCD_String("Lime PH is ");
			   	   LCD_Command(0xc0);
			   	   dtostrf(ph_act,8,5,Ph);
			   	   LCD_String(Ph);
			   	   _delay_ms(100);
			   	   LCD_Clear();
			   	   
			   	   }else{
						  LCD_String("Lime PH is ");
						  LCD_Command(0xc0);
						  LCD_String("not good");
						  _delay_ms(100);
						  LCD_Clear();
			   	   con=0;
			   	   
		   	   }
		   	   
	   	   }
			  
			  //check ph of orange
			  
			  	   if(ora==1){
				  	   for(int i=0;i<10;i++)
				  	   {
					  	   buffer_arr[i]=ADC_Read(2);
					  	   _delay_ms(30);
				  	   }
				  	   for(int i=0;i<9;i++)
				  	   {
					  	   for(int j=i+1;j<10;j++)
					  	   {
						  	   if(buffer_arr[i]>buffer_arr[j])
						  	   {
							  	   temp=buffer_arr[i];
							  	   buffer_arr[i]=buffer_arr[j];
							  	   buffer_arr[j]=temp;
						  	   }
					  	   }
				  	   }
				  	   avgval=0;
				  	   for(int i=2;i<8;i++)
				  	   avgval+=buffer_arr[i];
				  	   float volt=(float)avgval*5.0/1024/6;
				  	   float ph_act = -5.70 * volt + calibration_value;
				  	   if(ph_act>3.30 && ph_act<4.19){
							 con=1;
					  	   LCD_String("Orange PH is ");
					  	   LCD_Command(0xc0);
					  	   dtostrf(ph_act,8,5,Ph);
					  	   LCD_String(Ph);
					  	   _delay_ms(100);
					  	   LCD_Clear();
					  	   
					  	   }else{
								 LCD_String("Orange PH is ");
								 LCD_Command(0xc0);
								 LCD_String("not good");
								 _delay_ms(100);
								 LCD_Clear();
					  	   con=0;
					  	   
				  	   }
				  	   
			  	   }
					 
					  int const measure=50;
					  int con2=0;
					  double value;
					 //check water level of apple
			  if(app==1){
				  value=ADC_Read(3);
				  if(value>measure){
					   con2=1;
				  }
				  else{
					LCD_String("Apple water level ");
					LCD_Command(0xc0);
					LCD_String("is low");
					_delay_ms(100);
					LCD_Clear();
					con2=0;
				  }
			  
			  }
			  
			  //check water level of lime
			    if(app==1){
				    value=ADC_Read(3);
				    if(value>measure){
					    con2=1;
				    }
				    else{
					    LCD_String("Lime water level ");
					    LCD_Command(0xc0);
					    LCD_String("is low");
					    _delay_ms(100);
					    LCD_Clear();
					    con2=0;
				    }
				    
			    }
			    
				
				//check water level of orange
				  if(app==1){
					  value=ADC_Read(3);
					  if(value>measure){
						  con2=1;
					  }
					  else{
						  LCD_String("Orange water level ");
						  LCD_Command(0xc0);
						  LCD_String("is low");
						  _delay_ms(100);
						  LCD_Clear();
						  con2=0;
					  }
					  
				  }
				  
				   int irCheck= PIND & (1<<PD6);
				   double vol=0;
				  
				  if(con==1){
					  if(con2==1){
						  if(irCheck){
							  if(app==1){
								  vol=0;
								  PORTC=PORTC | (1<<PC4);
								  while(vol<=amount){
									  while(clk()!=1);  //wait 1 second
									  time_clock++;  //increase the clock by 1 second
									  
										  float l_minutes=(pulses[0])/7.5;  //calculation
										  float ml_second=l_minutes*50/3;
										  vol+=ml_second;
										  pulses[0]=0;                        //reset the pulse variable
									 
									  
								  }
								   PORTC=PORTC | (0<<PC4);
								  
								  
								  
							  }
							  if(lim==1){
								  vol=0;
								  PORTC=PORTC | (1<<PC5);
								  while(vol<=amount){
									  while(clk()!=1);  //wait 1 second
									  time_clock++;  //increase the clock by 1 second
									  
									  float l_minutes=(pulses[1])/7.5;  //calculation
									  float ml_second=l_minutes*50/3;
									  vol+=ml_second;
									  pulses[1]=0;                        //reset the pulse variable
									  
									  
								  }
								  PORTC=PORTC | (0<<PC5);
								  
								  
								  
							  }
							  
							  if(ora==1){
								  vol=0;
								  PORTC=PORTC | (1<<PC6);
								  while(vol<=amount){
									  while(clk()!=1);  //wait 1 second
									  time_clock++;  //increase the clock by 1 second
									  
									  float l_minutes=(pulses[2])/7.5;  //calculation
									  float ml_second=l_minutes*50/3;
									  vol+=ml_second;
									  pulses[2]=0;                        //reset the pulse variable
									  
									  
								  }
								  PORTC=PORTC | (0<<PC6);
								  
								  
								  
							  }
							  if(iceWa==1){
								  for(int i=0;i<2;i++)/* ice cube gana*/
								  {
									  OCR1A = 65;	/* Set servo shaft at -90° position */
									  _delay_ms(3000);
									  OCR1A = 175;	/* Set servo shaft at 0° position */
									  _delay_ms(1500);
								  }
							  }
							  
							  
							  
							  }else{
			 LCD_String("Please put a cup");
			 LCD_Command(0xc0);
			 LCD_String("on the position");
			 _delay_ms(100);
			 LCD_Clear();
			
						  }
						  
					  }else{
						   LCD_String("Some Juice Level ");
						   LCD_Command(0xc0);
						   LCD_String("are low");
						   _delay_ms(100);
						   LCD_Clear();
						   LCD_String("Sorry ");
						   LCD_Command(0xc0);
						   LCD_String("wait some time");
						   _delay_ms(100);
						   LCD_Clear();
					  }
					  
				  }else{
					   LCD_String("Some Ph Level ");
					   LCD_Command(0xc0);
					   LCD_String("are not good");
					   _delay_ms(100);
					   LCD_Clear();
					   LCD_String("Sorry ");
					   LCD_Command(0xc0);
					   LCD_String("wait some time");
					   _delay_ms(100);
					    LCD_Clear();
				  }
				  
			  
			   
	   
	   
   }
		
}


void timer0_int(){
	TCCR0 |= 1<<CS02;            //set the prescaler to 1024
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



