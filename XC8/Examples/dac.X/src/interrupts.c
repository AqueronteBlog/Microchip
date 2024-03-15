/**
 * @brief       interrupts.c
 * @details     Interrupts sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        15/March/2024
 * @version     15/March/2024    The ORIGIN
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
 * @date        15/March/2024
 * @version     15/March/2024   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __interrupt() ISR ( void )
{
    /* Check if Timer2 Overflow interrupt is enabled and Timer2 Overflow occurred */
    if ( ( PIE1bits.TMR2IE == 1U  ) && ( PIR1bits.TMR2IF == 1U ) )
    {        
        /* Update the variable  */
        myState =   1U;
        
        
        /* Clear the interrupt flag   */
        PIR1bits.TMR2IF = 0U;
    }
}