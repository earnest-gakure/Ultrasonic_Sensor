#include "TM4C123.h"                    // Device header
#include "ultrasonic.h"

int main () {
	
	port_init();
	Timer0_init();
	
	while (1)
	{
		distance_in_cm = measureD() ;
		if (distance_in_cm <15 ){
			GPIOF->DATA |= BLUE_LED ;
		}
		else
			GPIOF->DATA &= ~ BLUE_LED ; 
	}
	
}
