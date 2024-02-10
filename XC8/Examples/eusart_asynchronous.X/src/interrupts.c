/**
 * @brief       interrupts.c
 * @details     Interrupts sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        10/February/2024
 * @version     10/February/2024    The ORIGIN
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
    /* Rx	 */
	if ( ( PIE1bits.RCIE == 1U ) && ( PIR1bits.RCIF == 1U ) )
	{
        /* Check Overrun error  */
        if ( RCSTAbits.OERR ==  1U )
        {
            /* Clear flag. If the receive FIFO is overrun, no additional characters will be 
             * received until the overrun condition is cleared   */
            RCSTAbits.OERR =  0U;
        }
        
		/* Next action	 */
		myState	 =	 RCREG;
        
        /* Clear Rx Interrupt flag  */
        PIR1bits.RCIF = 0U; 
	}

	/* Tx	 */
	if ( ( PIE1bits.TXIE == 1U ) && ( TXSTAbits.TXEN == 1UL ) )
	{        
        /* Wait until Transmit Shift Register Status is empty  */
        while ( TXSTAbits.TRMT ==  0U );
        
		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{            
            /* Disable transmission and enable reception again    */
			TXSTAbits.TXEN  =   0UL;
            RCSTAbits.CREN  =   1U;
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