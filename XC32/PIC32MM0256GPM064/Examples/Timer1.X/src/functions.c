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
#include <proc/p32mm0256gpm064.h>

#include "../inc/functions.h"


/**
 * @brief       void conf_CLK  ( void )
 * @details     It configures the clocks for the system.
 * 
 *                  - SYSCLK ( F_SYS ) = FRC/1 = 8MHz
 *                  - Device will enter Sleep mode when a WAIT instruction is executed
 *                  - Secondary oscillator is enabled
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
 * @version     03/June/2019      Device will enter Sleep mode when a WAIT instruction is executed
 *              02/June/2019      Secondary oscillator is enabled
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
    OSCCONbits.FRCDIV   =   0UL; // FRC divided by 1
    OSCCONbits.NOSC     =   0UL; // Internal Fast RC (FRC) Oscillator divided by FRCDIV[2:0] bits (FRCDIV)
    OSCCONbits.SOSCEN   =   1UL; // Enables the Secondary Oscillator
    OSCCONbits.SLPEN    =   1UL; // Device will enter Sleep mode when a WAIT instruction is executed
    
    /* Initiates an oscillator switch to a selection specified by the NOSC[2:0] bits     */
    OSCCONbits.OSWEN    =   1UL;
    
    /* Wait until oscillator switch is complete and the secondary oscillator is enabled too  */
    while ( ( OSCCONbits.OSWEN == 1UL ) && ( CLKSTATbits.SOSCRDY == 0UL ) );    // [TODO]       Too dangerous!!! The uC may get stuck here
                                                                                // [WORKAROUND] Insert a counter
    
    SYSKEY  =    0x00000000;    // Force lock
}



/**
 * @brief       void conf_PWRCON  ( void )
 * @details     It configures the power control register.
 * 
 *                  - Main regulator to be put in a low-power state during Sleep mode 
 *                  - Voltage regulator will go into Standby mode during Sleep mode
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
 * @date        03/June/2019
 * @version     03/June/2019      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_PWRCON  ( void )
{
    SYSKEY  =    0x00000000;    // Force lock
    SYSKEY  =    0xAA996655;    // Unlock registers    
    SYSKEY  =    0x556699AA;
    
    /* The main regulator to be put in a low-power state during Sleep mode  */
    PWRCONbits.RETEN    =   1UL;
    
    /* Voltage regulator will go into Standby mode during Sleep mode     */
    PWRCONbits.VREGS    =   0UL;
    
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
 *                 Timer1:
 *                   - Overflow: 250ms ( 8192 * ( 1 / 32768kHz ) = 250ms )
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
    T1CONbits.ON    =   0UL;
    
    /* Continues operation even in Idle mode    */
    T1CONbits.SIDL  =   0UL;
    
    /* External clock comes from the Secondary Oscillator (SOSC)     */
    T1CONbits.TECS  =   0b00;
    
    /*  Timer1 Input Clock Prescale: 1:1 prescale value   */
    T1CONbits.TCKPS =   0b00;
    
    /* External clock is defined by the TECS[1:0] bits   */
    T1CONbits.TCS   =   1UL;
    
    /* Clear timer register  */
    TMR1     =   0UL;
    
    /* Load period register  */
    PR1      =   8192UL;
    
    /* Timer1: Interrupt priority is 3   */
    IPC4bits.T1IP   =   0b011;
    
    /* Timer1: Interrupt subpriority is 1   */
    IPC4bits.T1IS   =   0b01;
            
    /* Clear the timer interrupt status flag ( T1IF )     */
    IFS0CLR  =   0x00020000;
    
    /* Enable timer interrupts ( T1IE )     */
    IEC0SET  =   0x00020000;
    
    /* Multi-vector mode     */
    INTCONbits.MVEC =   1UL;
    
    /* Enable Timer1    */
    T1CONbits.ON    =   1UL;
}