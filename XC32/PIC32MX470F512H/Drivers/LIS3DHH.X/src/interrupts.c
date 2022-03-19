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
 * @brief       void U1Handler ()
 * @details     UART1 interruption. 
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/February/2022
 * @version     27/February/2022   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __attribute__ ( ( vector(_UART_1_VECTOR), interrupt(IPL3SOFT) ) ) U1Handler ( void )
{
    /* Rx	 */
	if ( ( U1STAbits.URXDA == 1UL ) && ( U1STAbits.URXEN == 1UL ) )
	{
        while( U1STAbits.RIDLE == 0UL );
        
		/* Next action	 */
		myState	 =	 (uint8_t)( U1RXREG );
        
        /* Clear Interrupt (IFS1<7>)  */
        IFS1CLR |=  ( 1UL << 7UL );  
	}

	/* Tx	 */
	if ( U1STAbits.UTXEN == 1UL )
	{
        while( U1STAbits.TRMT == 0UL );
        
		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{
			U1STAbits.UTXEN = 0UL;
		}
		else
		{
			U1TXREG	 =	 *++myPtr;
		}
        
        /* Clear Interrupt (IFS1<8>)  */
        IFS1CLR |=  ( 1UL << 8UL );
	}
}