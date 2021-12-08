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
    
    /* Device will enter Idle mode when a WAIT instruction is executed */
    OSCCONbits.SLPEN    =   0UL;    
    
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
 *              Timer1:
 *                  - Prescaler: 256 (f_timer = 8MHz/256 = 31250Hz)
 *                  - Overflow: 1s ( 31250 * ( 1 / 31250Hz ) = 1s )
 *                  - Interrupt enabled
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
 * @version     08/December/2021      The Timer1 was set to overflow at 1s
 *              02/December/2021      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_Timers  ( void )
{
    /* Disable Timer 1  */
    T1CONbits.ON     =   0UL;
    
    /* Continue operation even in Idle mode */
    T1CONbits.SIDL   =   0UL;
    
    /* Back-to-back writes are enabled  */
    T1CONbits.TWDIS  =   0UL;
    
    /* Asynchronous write to TMR1 register complete (in asynchronous Timer mode)    */
    T1CONbits.TWIP   =   0UL;
    
    /* Gate time accumulation is disabled   */
    T1CONbits.TGATE  =   0UL;
    
    /* 1:256 Prescale value   */
    T1CONbits.TCKPS  =   0b11;
    
    /* Internal peripheral clock    */
    T1CONbits.TCS    =   0UL;
    
    /* Clear time register  */
    TMR1     =   0UL;
    
    /* Load period register */
    PR1  =   31250UL;
    
    /* Timer1: Interrupt priority is 3   */
    IPC1bits.T1IP   =   0b011;
    
    /* Timer1: Interrupt subpriority is 1   */
    IPC1bits.T1IS   =   0b01;
    
    /* Clear the Timer1 interrupt status flag ( T1IF )     */
    IFS0CLR  =   0x00000010;
    
    /* Enable Timer1 interrupts ( T1IE )     */
    IEC0SET  =   0x00000010;
    
    /* Interrupt controller configured for multivectored vectored mode     */
    INTCONbits.MVEC =   1UL;
    
    /* Enable Timer 1  */
    T1CONbits.ON     =   1UL;
}