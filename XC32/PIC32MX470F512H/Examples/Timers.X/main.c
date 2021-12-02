/**
 * @brief       main.c
 * @details     This project shows how to work with the internal peripherals GPIO. All the LEDs ( LED1, LED2 and
 *              LED3 ) blink for a period of time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        30/November/2021
 * @version     30/November/2021    The ORIGIN
 * @pre         This firmware was tested on the PIC32MX470 Curiosity Development Board with MPLAB X IDE v5.50.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - Twitter: https://twitter.com/aqueronteblog
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
    
    /* Configure the peripherals*/
    conf_CLK  ();
    conf_GPIO ();
        
    
    while ( 1 )
    {
        /* Blink LED1, LED2 and LED3    */
        PORTEINV   = ( LED1 | LED2 | LED3 );
        for ( i = 0UL; i < 0x23232; i++ );
    }
}
