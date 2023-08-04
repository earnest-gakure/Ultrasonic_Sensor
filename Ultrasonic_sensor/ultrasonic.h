/**@file ultrasonic.h
 * @brief interface file for ultrasonic sensor initialization and operation
 */
#ifndef ULTRASONIC_H__
#define ULTRASONIC_H__
#include <stdint.h>

/**@brief Function for initialization  of Timer0 which is used for
detecting rising and falling edge 
*/
void Timer0_init (void);

/**@brief Function for initializing the Trigger pin of the the\n
 * ultrasonic sensor and calculating distance*/
uint32_t measureD(void) ;

/**@brief function for initializing GPIO PIN of port F */
void port_init (void) ;

static const double _16MHZ_1clock = 62.5e-9;   /*value of 1clock cycle in nanoseconds*/
static const uint32_t MULTIPLIER = 5882;       /*Constant derived from the speed of sound*/


#define ECHO (1U<<6)   //PB6
#define TRIGGER (1U<<4)  //PA4 (OUTPUT)
#define BLUE_LED (1U<<2) //PF2 onboard BLUE LED


static uint32_t highEdge;           /** Variable to hold time-stamp of high-edge detection*/
static uint32_t lowEdge;            /** Variable to hold time-stamp of low-edge detection */
static uint32_t distance;          /** Variable to hold calculated distance*/
static uint32_t distance_in_cm ;

#endif


