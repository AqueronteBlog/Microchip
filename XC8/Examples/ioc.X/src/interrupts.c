/**
 * @brief       interrupts.c
 * @details     Interrupts sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        17/February/2024
 * @version     17/February/2024    The ORIGIN
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
 * @date        17/February/2024
 * @version     17/February/2024   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __interrupt() ISR ( void )
{
    /* Check if IOC interrupt is enabled and IOC negative edge happened */
    if ( ( INTCONbits.IOCIE == 1U  ) && ( IOCBFbits.IOCBF0 == 1U ) )
    {        
        /* Update the variable  */
        myState =   1U;
        
        
        /* Clear the interrupt flag   */
        IOCBFbits.IOCBF0 = 0U;
    }
}