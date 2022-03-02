/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/February/2022
 * @version     27/February/2022   The ORIGIN
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
 * @date        27/February/2022
 * @version     27/February/2022      The ORIGIN
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
 *              UART1
 *                  - Tx: RPF0
 *                  - Rx: RPF1
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/February/2022
 * @version     02/March/2022       UART pins were added
 *              27/February/2022    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO  ( void )
{
    ANSELECLR  |=   ( LED1 | LED2 | LED3 );
    TRISECLR   |=   ( LED1 | LED2 | LED3 );
    
    /* Reset value of the LEDs = OFF */
    PORTECLR   |=   ( LED1 | LED2 | LED3 );  
    
    /* Set UART1 pins: U1TX (RPF0) and U1RX (RPF1)   */
    SYSKEY  =    0x00000000;    // Force lock
    SYSKEY  =    0xAA996655;    // Unlock registers    
    SYSKEY  =    0x556699AA;
    
    CFGCONbits.IOLOCK   =   0UL;
    
    RPF0Rbits.RPF0R =   0b0011;
    U1RXRbits.U1RXR =   0b0100;  
    
    CFGCONbits.IOLOCK   =   1UL;
    
    SYSKEY  =    0x33333333;    // Force lock
}



/**
 * @brief       void conf_UART1  ( uint32_t , uint32_t )
 * @details     It configures the UART1.
 *
 * @param[in]    f_pb:      UART clock.
 * @param[in]    baudrate:  UART baud rate.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/February/2022
 * @version     27/February/2022      The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_UART1  ( uint32_t f_pb, uint32_t baudrate )
{
    /* UART disabled */
    U1MODEbits.ON   =   0UL;
    
    /* Continue operation in Idle mode */
    U1MODEbits.SIDL =   0UL;
    
    /* IrDA is disabled */
    U1MODEbits.IREN =   0UL;
    
    /* U1TX and U1RX pins are enabled and used only */
    U1MODEbits.UEN = 0b00;
    
    /* Wake-up is enabled */
    U1MODEbits.WAKE = 1UL;
    
    /* Loopback mode is disabled */
    U1MODEbits.LPBACK = 0UL;
    
    /* Baud rate measurement disabled or completed */
    U1MODEbits.ABAUD = 0UL;
    
    /* U1RX Idle state is '1' */
    U1MODEbits.RXINV = 0UL;
    
    /* High-Speed mode ? 4x baud clock enable */
    U1MODEbits.BRGH = 1UL;
    
    /* 8-bit data, no parity */
    U1MODEbits.PDSEL = 0b00;
    
    /* 1 Stop bit */
    U1MODEbits.STSEL = 0UL;
    
    /* Automatic Address Detect mode is disabled */
    U1STAbits.ADM_EN = 0UL;
    
    /* Interrupt is generated and asserted when all characters have been transmitted */
    U1STAbits.UTXISEL = 0b01;
    
    /* U1TX Idle state is '1' */
    U1STAbits.UTXINV = 0UL;
    
    /* UART1 receiver is enabled */
    U1STAbits.URXEN = 1UL;
    
    /* Break transmission is disabled or completed */
    U1STAbits.UTXBRK = 0UL;
    
    /* UART1 transmitter is disabled */
    U1STAbits.UTXEN = 0UL;
    
    /* Interrupt flag bit is asserted while receive buffer is not empty */
    U1STAbits.URXISEL = 0b00;
    
    /* Address Detect mode is disabled */
    U1STAbits.ADDEN = 0UL;
    
    /* Calculate the desired baud rate */
    if ( U1MODEbits.BRGH == 0UL )
    {
        U1BRG = ( f_pb / ( 16UL * baudrate ) ) - 1UL;
    }
    else
    {
        U1BRG = ( f_pb / ( 4UL * baudrate ) ) - 1UL;
    } 
    
    /* UART1: Interrupt priority is 3   */
    IPC7bits.U1IP   =   0b011;
    
    /* UART1: Interrupt subpriority is 1   */
    IPC7bits.U1IS   =   0b01;
    
    /* Clear the UART1 interrupt status flag ( U1IF )     */
    IFS1CLR  =   0x00000180;
    
    /* Enable UART1 interrupts ( U1IF )     */
    IEC1bits.U1RXIE = 1UL;
    IEC1bits.U1TXIE = 1UL;
    
    /* Interrupt controller configured for multivectored vectored mode     */
    INTCONbits.MVEC =   1UL;
    
    /* UART enabled */
    U1MODEbits.ON   =   1UL;
}