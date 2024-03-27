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
 * @date        27/March/2024
 * @version     27/March/2024   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __interrupt() ISR ( void )
{
    /* C1 comparator	 */
	if ( ( PIE2bits.C1IE == 1U ) && ( PIR2bits.C1IF == 1UL ) )
	{              
        /* Indicates a change in the comparator output (from Low to High or from High to Low) */
        myFlag  =   1U;
            
        /* Clear C1 comparator Interrupt flag  */
        PIR2bits.C1IF = 0U; 
	}
}