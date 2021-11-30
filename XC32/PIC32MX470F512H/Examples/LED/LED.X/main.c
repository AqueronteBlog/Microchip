/**
 * @brief       main.c
 * @details     This project shows how to work with the internal peripherals GPIO. All the LEDs ( LED1, LED2 and
 *              LED3 ) blink for a period of time.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        18/May/2019
 * @version     18/May/2019    The ORIGIN
 * @pre         This firmware was tested on the PIC32MM USB Curiosity Development Board with MPLAB X IDE v5.20.
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
    
    conf_CLK  ();
    conf_GPIO ();
        
    
    while ( 1 )
    {
        /* Blink LED1, LED2 and LED3    */
        PORTDINV   = ( LED1 | LED3_RGB_RED );
        PORTCINV   = ( LED2 | LED3_RGB_GREEN | LED3_RGB_BLUE );
        for ( i = 0UL; i < 0x23232; i++ );
    }
}
