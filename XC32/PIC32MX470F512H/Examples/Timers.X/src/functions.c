/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        02/December/2021
 * @version     02/December/2021   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/functions.h"


/**
 * @brief       void conf_CLK  ( void )
 * @details     It configures the clocks for the system.
 * 
 *                  - SYSCLK ( F_SYS ) = FRC/1 = 8MHz
 * 
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/November/2021
 * @version     30/November/2021      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK  ( void )
{
    SYSKEY  =    0x00000000;    // Force lock
    SYSKEY  =    0xAA996655;    // Unlock registers    
    SYSKEY  =    0x556699AA;
    
    /* Internal Fast RC (FRC) Oscillator divided by 1 */
    OSCCONbits.FRCDIV   =    0; // FRC divided by 1
    OSCCONbits.NOSC     =    0; // Internal Fast RC (FRC) Oscillator divided by FRCDIV[2:0] bits (FRCDIV)
    
    /* Initiates an oscillator switch to a selection specified by the NOSC[2:0] bits     */
    OSCCONbits.OSWEN    =    1;
    
    /* Wait until oscillator switch is complete  */
    while ( OSCCONbits.OSWEN == 1 );    // [TODO]       Too dangerous!!! The uC may get stuck here
                                        // [WORKAROUND] Insert a counter
    
    /* Wait until Peripheral Bus Clock (PBCLK) Divisor can be written   */
    while ( OSCCONbits.PBDIVRDY == 0 ); // [TODO]       Too dangerous!!! The uC may get stuck here
                                        // [WORKAROUND] Insert a counter
    
    /* PBCLK is SYSCLK divided by 1 */
    OSCCONbits.PBDIV    =   0b00;
        
    
    SYSKEY  =    0x33333333;    // Force lock
}



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 * 
 *              PortE
 *                  - LED1: RE4 (Digital output)
 *                  - LED2: RE6 (Digital output)
 *                  - LED3: RE7 (Digital output)
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        30/November/2021
 * @version     30/November/2021      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    ANSELECLR  |=   ( LED1 | LED2 | LED3 );
    TRISECLR   |=   ( LED1 | LED2 | LED3 );
    
    /* Reset value of the LEDs = OFF */
    PORTESET   |=   ( LED1 | LED2 | LED3 );  
}



/**
 * @brief       void conf_Timers  ( void )
 * @details     It configures the Timers.
 * 
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        02/December/2021
 * @version     02/December/2021      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_Timers  ( void )
{
    
}