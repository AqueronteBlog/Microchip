/**
 * @brief       interrupts.c
 * @details     Interrupts sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        27/March/2024
 * @version     27/March/2024    The ORIGIN
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
 * @date        09/February/2024
 * @version     09/February/2024   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __interrupt() ISR ( void )
{
    /* Check if Timer1 Overflow interrupt is enabled and Timer1 Overflow occurred */
    if ( ( PIE1bits.TMR1IE == 1U  ) && ( PIR1bits.TMR1IF == 1U ) )
    {        
        /* Update the variable  */
        myFlag  =   1U;
        
        /* Clear the interrupt flag   */
        PIR1bits.TMR1IF = 0U;
    }
}