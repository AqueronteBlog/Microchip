/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/functions.h"


/**
 * @brief       void conf_clk ( void )
 * @details     It configures the clocks.
 * 
 *              HFINTOSC
 *                  - 16MHz
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
 * @date        10/February/2024
 * @version     10/February/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_clk ( void )
{
    /* 4x PLL is disabled  */
    OSCCONbits.SPLLEN =   0U;
    
    /* Internal Oscillator Frequency: 16MHz  */
    OSCCONbits.IRCF =   0b1111;
    
    /* Internal oscillator block */
    OSCCONbits.SCS  =   0b11;
    
    while ( OSCSTATbits.HFIOFR == 0U ); // Wait until HFINTOSC is ready
}


/**
 * @brief       void conf_gpio ( void )
 * @details     It configures GPIOs.
 * 
 *              PORTB
 *                  - RB0: GPIO Input pin, no pull-up
 *                  - RB1: GPIO Output pin, no pull-up
 *                  - RB2: GPIO Output pin, no pull-up
 *                  - RB3: GPIO Output pin, no pull-up
 *              
 *              PORTA
 *                  - RA0: GPIO Analog Input pin (AN0)
 *                  - RA4: GPIO Input pin
 * 
 *              PORTC
 *                  - RC7: GPIO Input pin (EUSART Rx)
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
 * @date        08/December/2023
 * @version     14/March/2024       RA0 as an AN0 pin
 *              10/February/2024    EUSART pins are configured
 *              15/December/2023    Turn all the LEDs off
 *                                  RA4 as an input pin
 *              08/December/2023    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_gpio ( void )
{
    /* RB0, RB1, RB2 and RB3 as digital I/O pins */
    ANSELB  &=  ~( D3 | D4 | D5 | S3 );
    
    /* RB1, RB2 and RB3 as output pins */
    TRISB   &=  ~( D3 | D4 | D5 );
    
    /* RB0 as an input pin */
    TRISB   |=  S3;
    
    /* RB0, RB1, RB2 and RB3 no pull-ups */
    WPUB    &=  ~( S3 | D3 | D4 | D5 );
    
    /* Turn all the LEDs off    */
    LATB    &=  ~( D3 | D4 | D5 );
    
    /* RA4 as a digital I/O pin */
    ANSELA  &=  ~( S2 );
    
    /* RA4 as an input pin */
    TRISA   |=  S2;
    
    /* RA0 as an analog input   */
    ANSELAbits.ANSA0    =   1U;
    
    /* RC7 as an input pin */
    TRISC   |=  RX;
    
    /* RC6 as an output pin */
    TRISC   &=  ~( TX );
}


/**
 * @brief       void conf_adc ( void )
 * @details     It configures the ADC peripheral.
 *              
 *              ADC
 *                  - AN0 channel enabled
 *                  - Right justified result format
 *                  - ADC clock: FRC (clock supplied from a dedicated RC oscillator)
 *                  - VREF- is connected to VSS
 *                  - VREF+ is connected to VDD
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        14/March/2024
 * @version     14/March/2024    The ORIGIN
 * @pre         TADMmax@FRC ~ 6us 
 * @pre         New ADC conversion timing =  TACQ + TCNV = TACQ + 11.5*TAD = 5us + 11.5*6us = 74us 
 * @warning     The user must respect the TACQ before start a new ADC conversion! TACQtyp ~ 5us
 * @warning     The user must respect the TCNV before start a new ADC conversion! TCNVtyp ~ 11.5*TAD
 */
void conf_adc ( void )
{
    /* ADC disabled    */
    ADCON0bits.ADON  =   0U;
    
    /* AN0 channel enabled    */
    ADCON0bits.CHS  =   0b00000;
    
    /* ADC result format: Right justified   */
    ADCON1bits.ADFM =   1U;
    
    /* ADC Conversion Clock: FRC (clock supplied from a dedicated RC oscillator)   */
    ADCON1bits.ADCS =   0b111;
    
    /* VREF- is connected to VSS   */
    ADCON1bits.ADNREF   =   0U;
    
    /* VREF+ is connected to VDD   */
    ADCON1bits.ADPREF   =   0b00;
    
    /* ADC enabled    */
    ADCON0bits.ADON  =   1U;
    
    // The user must respect the TACQ before start a new ADC conversion! TACQtyp ~ 5us 
    
    /* Clear ADC interrupt flag */
    PIR1bits.ADIF   =   0U;
    
    /* Enable Interrupt */
    PIE1bits.ADIE   =   1U;
}


/**
 * @brief       void conf_eusart ( void )
 * @details     It configures the EUSART in 16-bit asynchronous mode.
 *              
 *              Desire_baudrate = F_OSC/[4·(SPBRG+1)]
 * 
 *              EUSART
 *                  - 16-bit asynchronous mode
 *                  - SPBRG = ( F_OSC/(4·Desire_baudrate) ) - 1 = ( 16000000/(4·115200) ) - 1 ~ 34 (0x0022)
 *                  - 8-bit reception/transmission
 *                  - Auto-Baud detect disabled
 *                  - Receiver interrupt disabled
 *                  - Transmission interrupt disabled
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        10/February/2024
 * @version     14/March/2024       Rx is disabled
 *              10/February/2024    The ORIGIN
 * @pre         Error = 100*( 115200 - 114285.714 )/115200 = 0.79%
 * @warning     N/A
 */
void conf_eusart ( void )
{
    /* Serial port disabled (held in Reset)    */
    RCSTAbits.SPEN  =   0U;
    
    /* Selects 8-bit reception    */
    RCSTAbits.RX9  =   0U;
    
    /* Disables receiver (Asynchronous mode)    */
    RCSTAbits.CREN  =   0U;
    
    /* Selects 8-bit transmission    */
    TXSTAbits.TX9   =   0U;
    
    /* Transmit disabled    */
    TXSTAbits.TXEN   =   0U;
    
    /* EUSART: Asynchronous mode    */
    TXSTAbits.SYNC   =   0U;
    
    /* EUSART: High speed    */
    TXSTAbits.BRGH   =   1U;
    
    /* Transmit non-inverted data to the TX/CK pin  */
    BAUDCONbits.SCKP    =   0U;
    
    /* 16-bit Baud Rate Generator is used    */
    BAUDCONbits.BRG16   =   1U;
    
    /* Auto-Baud Detect mode is disabled    */
    BAUDCONbits.ABDEN   =   0U;
    
    /* Baudrate value   */
    SPBRGH  =   0x00;
    SPBRGL  =   0x22;
    
    /* Clear receiver (Rx) and transmission (Tx) interrupt flags   */
    PIR1bits.RCIF   =   0U;
    PIR1bits.TXIF   =   0U;
    
    /* Disable transmission (Tx) interrupt    */
    PIE1bits.TXIE   =   0U;
        
    /* Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)    */
    RCSTAbits.SPEN  =   1U;
}