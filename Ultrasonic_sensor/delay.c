
#include "TM4C123.h"                    // Device header
#include "delay.h"
void delay_microsecond (uint32_t time )
{
	int i;
	   //WE USE TIMER1
	  SYSCTL->RCGCTIMER |= ( 1U<<1 );
    TIMER1->CTL = 0 ;         //disable timer
	  TIMER1->CFG  = 0x04 ;     //16-bits mode
	  TIMER1->TAMR = 0x02 ;     //periodic time mode
    TIMER1->TAILR = 16-1 ;    //COZ we are using microseconds
	  TIMER1->ICR = 0x1;        //interrupt clear register
	  TIMER1->CTL |= 0x01 ;     //ENABLE TIMER
	
	for (i = 0 ; i < time ; i++ ){ 
		
		while ((TIMER1->RIS & 0x1) == 0) ;      //POLLING
		TIMER1->ICR = 0x1;
	}
}

