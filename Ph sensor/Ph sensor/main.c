
#ifndef F_CPU
#define F_CPU 8000000UL /* Define CPU Frequency e.g. here its 8MHz */
#endif
 					
#include <avr/io.h>						/* Include AVR std. library file */
#include <util/delay.h>					/* Include inbuilt defined Delay header file */
#include "lcd.h"
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "adc.h"

 


 
int main()
{	
	char String[20];
	
	unsigned long int avgValue;  //Store the average value of the sensor feedback
	int buf[10],temp;
	//char*  names[][10]={"apple","Orange","lime"};

	ADC_Init();
	LCD_Init();							/* Initialize LCD */
	while (1)
	{
		for (int l=0;l<3;l++)      //go through sensor 1,2,3
		{
			for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
			{
				buf[i]=ADC_Read(l);
				
			}
			for(int i=0;i<9;i++)        //sort the analog from small to large
			{
				for(int j=i+1;j<10;j++)
				{
					if(buf[i]>buf[j])
					{
						temp=buf[i];
						buf[i]=buf[j];
						buf[j]=temp;
					}
				}
			}
			avgValue=0;
			for(int i=2;i<8;i++)                      //take the average value of 6 center sample
			avgValue+=buf[i];
			float phValue=(float)avgValue*5.0/1024/6;
			 //convert the analog into millivolt
			phValue=3.5*phValue; //convert the millivolt into pH value
			//double value=(double)phValue;                     
			 LCD_Clear();
			LCD_String("Apple");		/* write string on 1st line of LCD*/
			LCD_Command(0xc0);					/* Go to 2nd line*/
			dtostrf(phValue,8,5,String);	/* Integer to string conversion */
			LCD_String(String);
			
			
		}
		_delay_ms(30);
		
		
	}
	
	return 0;
}
 
