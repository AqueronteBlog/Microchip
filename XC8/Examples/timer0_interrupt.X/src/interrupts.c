/**
 * @brief       interrupts.c
 * @details     Interrupts sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        31/January/2024
 * @version     31/January/2024    The ORIGIN
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
    /* Check if Timer0 Overflow interrupt is enabled and Timer0 Overflow occurred */
    if ( ( INTCONbits.TMR0IE == 1U  ) && ( INTCONbits.TMR0IF == 1U ) )
    {        
        /* Update the variable  */
        myState =   1U;
        
        /* Reload Timer0, it overflows every 0.5s  */
        TMR0    =   195U;
        
        /* Clear the interrupt flag   */
        INTCONbits.TMR0IF = 0U;
    }
}