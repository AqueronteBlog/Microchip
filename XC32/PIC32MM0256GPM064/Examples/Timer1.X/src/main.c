/**
 * @brief       main.c
 * @details     This project shows how to work with the internal peripherals Timer1. Both LED1 and LED2
 *              will change their state every ~250ms by overflow of the Timer1.
 * 
 *              The rest of the time, the microcontroller will be in the lowest power-mode: Retention Sleep Mode.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/June/2019
 * @version     01/June/2019    The ORIGIN
 * @pre         This firmware was tested on the PIC32MM USB Curiosity Development Board with MPLAB X IDE v5.20.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include "../inc/board.h"
#include "../inc/variables.h"
#include "../inc/functions.h"
#include "../inc/interrupts.h"


/**@brief Constants.
 */



/**@brief Variables.
 */
volatile uint32_t changeLEDstate     =   0UL;       /*!< Flag to change the state of the LEDs     */


/**@brief Function for application main entry.
 */
void main ( void ) 
{
    conf_CLK    ();
    conf_PWRCON ();
    conf_GPIO   ();
    conf_TIMER1 ();
     
    /* All interrupts are enabled     */
     __builtin_enable_interrupts();
     
    while ( 1 )
    {
        /* uC in low power mode: Retention Sleep Mode     */
        asm volatile ( "wait" );
        
        /* Check the next action     */
        if ( changeLEDstate == 1UL )
        {
            /* Blink LED1 and LED2    */
            PORTDINV   = ( LED1 );
            PORTCINV   = ( LED2 );
            
            /* Reset variable    */
            changeLEDstate   =   0UL;
        }        
    }
}
