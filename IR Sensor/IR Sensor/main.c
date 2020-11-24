#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>


int main(void)
{
	DDRC=1<<PC4;
	/* Replace with your application code */
	while (1)
	{
		if(PINC &(1<<PC3))//Check whether pc3 is high
		{
			PORTC=PORTC | 1<<PC4;//output pc4 high
		}
		else{
			PORTC=PORTC & ~(1<<PC4);////output pc4 low
		}
		
	}
}
