/**
 * @brief       main.c
 * @details     [TODO] This project shows how to work with the internal peripherals GPIO and Timer0.
 *              An interrupt will be generated every 0.5s by the TIMER0, the state of all the LEDs
 *              will be changed then.
 *
 *              The microcontroller remains in low power the rest of the time.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/May/2019
 * @version     18/May/2019    The ORIGIN
 * @pre         This firmware was tested on the PIC32MM USB Curiosity Development Board with MPLAB X IDE v5.20.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include "inc/board.h"
#include "inc/variables.h"
#include "inc/functions.h"
#include "inc/interrupts.h"


/**@brief Constants.
 */



/**@brief Variables.
 */



/**@brief Function for application main entry.
 */
void main ( void ) 
{
    uint32_t    i   =   0UL;
    
    TRISDCLR    =   ( LED1 | LED3_RGB_RED );
    TRISCCLR    =   ( LED2 | LED3_RGB_GREEN | LED3_RGB_BLUE );
    
    while ( 1 )
    {
        /* Blink LED1, LED2 and LED3    */
        PORTDINV   = ( LED1 | LED3_RGB_RED );
        PORTCINV   = ( LED2 | LED3_RGB_GREEN | LED3_RGB_BLUE );
        for ( i = 0UL; i < 0x232; i++ );
    }
}

