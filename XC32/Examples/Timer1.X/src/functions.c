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
 * @version     02/June/2019      Secondary oscillator is enabled
 *              01/June/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK  ( void )
{
    SYSKEY  =    0x00000000;    // Force lock
    SYSKEY  =    0xAA996655;    // Unlock registers    
    SYSKEY  =    0x556699AA;
    
    /* Internal Fast RC (FRC) Oscillator divided by 1 and Secondary Oscillator is enabled */
    OSCCONbits.FRCDIV   =    0; // FRC divided by 1
    OSCCONbits.NOSC     =    0; // Internal Fast RC (FRC) Oscillator divided by FRCDIV[2:0] bits (FRCDIV)
    OSCCONbits.SOSCEN   =    1; // Enables the Secondary Oscillator
    
    /* Initiates an oscillator switch to a selection specified by the NOSC[2:0] bits     */
    OSCCONbits.OSWEN    =    1;
    
    /* Wait until oscillator switch is complete and the secondary oscillator is enabled too  */
    while ( ( OSCCONbits.OSWEN == 1 ) && ( CLKSTATbits.SOSCRDY == 0 ) );    // [TODO]       Too dangerous!!! The uC may get stuck here
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



/**
 * @brief       void conf_TIMER1  ( void )
 * @details     It configures Timer1.
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
 * @date        02/June/2019
 * @version     02/June/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_TIMER1  ( void )
{
    /* Disable Timer1    */
    T1CONbits.ON    =   0;
    
    /* Continues operation even in Idle mode    */
    T1CONbits.SIDL  =   0;
    
    /* External clock comes from the Secondary Oscillator (SOSC)     */
    T1CONbits.TECS  =   0b00;
    
    /*  Timer1 Input Clock Prescale: 1:1 prescale value   */
    T1CONbits.TCKPS =   0b00;
    
    /* External clock is defined by the TECS[1:0] bits   */
    T1CONbits.TCS   =   1;
    
    /* Clear timer register  */
    TMR1     =   0UL;
    
    /* Load period register  */
    PR1      =   8192UL;
    
    /* Timer1: Interrupt priority is 3   */
    IPC4bits.T1IP   =   0b011;
    
    /* Timer1: Interrupt subpriority is 1   */
    IPC4bits.T1IS   =   0b01;
            
    /* Clear the timer interrupt status flag ( T1IF )     */
    IFS0SET  =   0x00020000;
    
    /* Enable timer interrupts ( T1IE )     */
    IEC0SET  =   0x00020000;
    
    /* Enable Timer1    */
    T1CONbits.ON    =   1;
}