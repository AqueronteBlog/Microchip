/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/June/2019
 * @version     01/June/2019   The ORIGIN
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
 * @date        01/June/2019
 * @version     01/June/2019      The ORIGIN
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
    
    SYSKEY  =    0x00000000;    // Force lock
}



/**
 * @brief       void conf_GPIO  ( void )
 * @details     It configures GPIO to work with the LEDs.
 * 
 *              PortD
 *                  - LED1:             RD3
 *                  - LED3_RGB_RED:     RD1
 * 
 *              PortC
 *                  - LED2:             RC13
 *                  - LED3_RGB_GREEN:   RC3
 *                  - LED3_RGB_BLUE:    RC15

 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/June/2019
 * @version     01/June/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    TRISDCLR    =   ( LED1 | LED3_RGB_RED );
    TRISCCLR    =   ( LED2 | LED3_RGB_GREEN | LED3_RGB_BLUE );
}