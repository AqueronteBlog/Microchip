/**
 * @brief       interrupts.c
 * @details     Interrupts sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        30/January/2024
 * @version     30/January/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/interrupts.h"


/**
 * @brief       void ISR ()
 * @details     Interrupt subroutine. 
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/January/2024
 * @version     31/January/2024   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __interrupt() ISR ( void )
{
    /* Check if INT External is enabled and INT external interrupt occurred */
    if ( ( INTCONbits.INTE == 1U  ) && ( INTCONbits.INTF == 1U ) )
    {
        /* Update the variable  */
        myState =   1U;
        
        /* Clear the interrupt flag   */
        INTCONbits.INTF = 0U;
    }
}