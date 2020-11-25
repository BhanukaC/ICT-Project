/*  
   LCD16x2 4 bit ATmega16 interface
   http://www.electronicwings.com
*/

#ifndef F_CPU
#define F_CPU 8000000UL			/* Define CPU Frequency e.g. here 8MHz */
#endif
#include "lcd.h"


 
int main()
{

	LCD_Init();			/* Initialization of LCD*/

	LCD_String("Group 14");	/* Write string on 1st line of LCD*/
	LCD_Command(0xC0);		/* Go to 2nd line*/
	LCD_String("Hello World");	/* Write string on 2nd line*/
	while(1);
}