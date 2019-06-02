/**
 * @brief       main.c
 * @details     [TODO]This project shows how to work with the internal peripherals GPIO. All the LEDs ( LED1, LED2 and
 *              LED3 ) blink for a period of time.
 *
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



/**@brief Function for application main entry.
 */
void main ( void ) 
{
    uint32_t    i   =   0UL;
    
    conf_CLK    ();
    conf_GPIO   ();
    conf_TIMER1 ();
        
    
    while ( 1 )
    {
        /* Blink LED1, LED2 and LED3    */
        PORTDINV   = ( LED1 | LED3_RGB_RED );
        PORTCINV   = ( LED2 | LED3_RGB_GREEN | LED3_RGB_BLUE );
        for ( i = 0UL; i < 0x23232; i++ );
    }
}
