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
    
    /* EUSART. Tx	 */
	if ( ( PIE1bits.TXIE == 1U ) && ( TXSTAbits.TXEN == 1UL ) )
	{        
        /* Wait until Transmit Shift Register Status is empty  */
        while ( TXSTAbits.TRMT ==  0U );
        
		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{            
            /* Disable transmission    */
			TXSTAbits.TXEN  =   0UL;
            
            /* Enable interrupts    */
            INTCONbits.IOCIE    =   1U; // Enable the interrupt-on-change
            INTCONbits.PEIE     =   0U; // Disable all active peripheral interrupts
		}
		else
		{
			TXREG	 =	 *myPtr;
            myPtr++;
		}
        
        /* Clear Tx Interrupt flag  */
        PIR1bits.TXIF = 0U; 
	}
}