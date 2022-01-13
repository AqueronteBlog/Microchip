/**
 * @brief       main.c
 * @details     This project shows how to work with the internal peripherals WDT as a timer. All the LEDs ( LED1, LED2 and
 *              LED3 ) blink every 1.024 second.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        12/January/2022
 * @version     12/January/2022    The ORIGIN
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
volatile uint32_t changeLEDstate     =   0UL;       /*!< Flag to change the state of the LEDs     */


/**@brief Function for application main entry.
 */
void main ( void ) 
{
    /* Configure the peripherals*/
    conf_CLK        ();
    conf_GPIO       ();
    conf_WDT_Timer  ();    
    

    while ( 1 )
    {
        /* WDT enabled  */
        WDTCONbits.ON   =   1UL;
        
        /* Perform a dummy instruction before WAIT instruction*/
        asm volatile ( "NOP" );
        
        /* uC in low power mode: Sleep Mode     */
        asm volatile ( "WAIT" );
        
        /* Check the next action     */
        if ( changeLEDstate == 1UL )
        {
            /* Blink LED1, LED2 and LED3    */
            PORTEINV   = ( LED1 | LED2 | LED3 );
            
            /* Reset variable    */
            changeLEDstate   =   0UL;
        }        
    }
}
