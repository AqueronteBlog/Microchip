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
    /* Tx	 */
	if ( ( PIE1bits.TXIE == 1U ) && ( TXSTAbits.TXEN == 1UL ) )
	{        
        /* Wait until Transmit Shift Register Status is empty  */
        while ( TXSTAbits.TRMT ==  0U );
        
		/* Stop transmitting data when that character is found */
		if ( *myPtr  == '\n' )
		{            
            /* Disable transmission   */
			TXSTAbits.TXEN  =   0UL;
            
            /* Indicates that the transmission is completed */
            myFlag  =   0b01;
		}
		else
		{
			TXREG	 =	 *myPtr;
            myPtr++;
		}
        
        /* Clear Tx Interrupt flag  */
        PIR1bits.TXIF = 0U; 
	}
    
    /* ADC	 */
	if ( ( PIE1bits.ADIE == 1U ) && ( PIR1bits.ADIF == 1UL ) )
	{        
        /* Get the ADC measurement (right alignment)  */
        myADCresult =   ADRESH;
        myADCresult <<= 8U;
        myADCresult |=  ADRESL;
		
        /* Indicates that the ADC data is completed */
        myFlag  =   0b10;
            
        /* Clear ADC Interrupt flag  */
        PIR1bits.ADIF = 0U; 
	}
}