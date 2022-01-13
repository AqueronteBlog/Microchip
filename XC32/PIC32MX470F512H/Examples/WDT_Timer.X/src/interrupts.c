/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/January/2022
 * @version     12/January/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/interrupts.h"


/**
 * @brief       void _nmi_handler ()
 * @details     Non-maskable Interrupt (NMI) handler. 
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        13/January/2022
 * @version     13/January/2022   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __attribute__((nomips16)) _nmi_handler(void)
{
    /* Check the Watchdog Timer Time-out Flag bit and the device was in Sleep mode */
    if ( ( RCONbits.WDTO == 1UL ) && ( RCONbits.SLEEP == 1UL ) )
    {
        changeLEDstate = 1UL;
        
        /* Return from interrupt    */
        asm volatile ( "ERET" );
    }    
}