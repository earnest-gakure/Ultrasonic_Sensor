
/**@file ultrasonic.h
 
 * @brief This file contains functions to intializes Timer0 in Edge-Capture\n
 * mode in order to be able detect the precise time the echoed signaled is detected.
 */

#include "TM4C123GH6PM.h"                  
#include <stdint.h>
#include "ultrasonic.h"
#include "ultrasonic.h"
#include "delay.h"

void Timer0_init (void){
	
	SYSCTL->RCGCTIMER |= ( 1U<<0) ; //Clock for TIMER0
	//Our TIMER) is going to work with ECHO pin.In order to detect signal changes we need to use PB6 since its connected to TIMER0
	//we will start the timer when PB6 goes HIGH and stop when it goes LOW
	SYSCTL->RCGCGPIO |= (1U<<1) ;              //enablig CLOCK for portB
	GPIOB->DIR       &= ~ECHO ;                //Setting PB6 as input
	GPIOB->DEN       |= ECHO ; 
	GPIOB->AFSEL     |= ECHO ;                //using the alternate function for PB6
	GPIOB->PCTL      &=~ 0x0F000000 ;
	GPIOB->PCTL      |=  0x07000000 ;
	
	//LETS NOW PROGRAM THE TIMER
	TIMER0->CTL  &= ~1 ;      //DISSABLING TIMER
	TIMER0->CFG = 0x04 ;      // 16-bit mode
	TIMER0->TAMR = 0x17 ;     //edge -time mode ,capture mode , up counter : OB 0001 0111
	TIMER0->CTL |= 0x0C ;     //Set TAEVENT bit to both edges :OB 0000 1100 GPTMCTL
	TIMER0->CTL |= 1 ;
	
}

//Initialization for the ports and pins to be used 
void port_init (void)
{
	    SYSCTL->RCGCGPIO |= (1U<<0) ;    //Enable clock for PORTA
     	SYSCTL->RCGCGPIO |= (1U<<5) ;    //Enable clock for PORTF so as to use the LED
	    GPIOA->DIR |=TRIGGER ;
	    GPIOF->DIR |=BLUE_LED ;
	    GPIOA->DEN |=TRIGGER ;
	    GPIOF->DEN |=BLUE_LED ;	
}
//This function will calculate  and 0utput the distance of the object
uint32_t measureD(void) 
{
	//sending the bursts
	GPIOA->DATA &= ~TRIGGER ;           //WE START BY DISSABLING THE TRIGGER pin
	delay_microsecond(12);
	GPIOA->DATA |= TRIGGER ;            //we enable triger
	delay_microsecond(12) ;
	GPIOA->DATA &= ~TRIGGER ;           //DISABLE trigger
	
	//Lets capture the return of the signal on the ECHO pin i.e capture firtsEdge i.e rising Edge
	
	TIMER0->ICR = 4 ;                         //Clear timer capture flag by writting 1 to CAECINT bit (bit2)
	   while ((TIMER0->RIS & 4 ) == 0) {};    // wait till captured ,by checkingif CARIS bit (bit2) is high
		highEdge = TIMER0->TAR ;                //highEdge = the time at which last edge event took place  i.e TAR
	
			 //capture the second Edge i.e Falling edge
			 
		TIMER0->ICR = 4 ;
			 while ((TIMER0->RIS & 4 ) == 0 ) {} ;
				 lowEdge = TIMER0->TAR ;
				 
			 distance = lowEdge - highEdge ;
			 distance = _16MHZ_1clock * (double) MULTIPLIER * (double) distance ;
			
return distance ;				 
}
