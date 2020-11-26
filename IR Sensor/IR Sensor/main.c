#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>




int main(void)
{
	DDRC=1<<PC4;
	
	while (1)
	{
		
		
		
		if(PIND &(1<<PD6))//Check whether PD6 is high
		{
			
			PORTC=PORTC | (1<<PC4);//output pc4 high
			
		}
		else{
			PORTC=PORTC & ~(1<<PC4);////output pc4 low
		}
		
		
	}
}
