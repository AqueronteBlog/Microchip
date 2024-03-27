/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        27/March/2024
 * @version     27/March/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/functions.h"


/**
 * @brief       void conf_clk ( void )
 * @details     It configures the clocks.
 * 
 *              HFINTOSC
 *                  - 8MHz
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
 * @date        27/March/2024
 * @version     27/March/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_clk ( void )
{
    /* 4x PLL is disabled  */
    OSCCONbits.SPLLEN =   0U;
    
    /* Internal Oscillator Frequency: 8MHz  */
    OSCCONbits.IRCF =   0b1110;
    
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
 * @brief       void conf_Timer2 ( void )
 * @details     It configures the Timer2.
 *              
 *              TMR2_flag ( TMR2 = PR2 ) = ( 1/( f_Timer2_OSC/4 ) )�Prescaler
 * 
 *              Timer2
 *                  - TMR2 overflows every 8.16ms
 *                  - f_Timer2_OSC = 8MHz
 *                  - PR2 = [ TMR2_flag / ( 4�Prescaler�( 1/f_Timer2_OSC ) ] = [ 8.16ms / ( 64*4�( 1/8000000 ) ] = 255
 *                  - TMR2 flag enabled every 0.13s: 8.16ms*Postcaler = 8.16ms*16 ~ 0.13s 
 *                  - Timer2 interrupt enabled
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/March/2024
 * @version     27/March/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_Timer2 ( void )
{
    /* Stops Timer2 */
    T2CONbits.TMR2ON   =  0U;
        
    /* Prescaler is 64 */
    T2CONbits.T2CKPS   =  0b11;
    
    /* 1:16 Postscaler */
    T2CONbits.T2OUTPS   =  0b1111;
    
    /* Timer2 overflows every 8.16ms ( TMR2 = PR2 )  */
    PR2    =   255U;
    
    /* Clear Timer2 interrupt flag */
    PIR1bits.TMR2IF   =   0U;
    
    /* Timer2 interrupt enabled */
    PIE1bits.TMR2IE   =   1U;
}


/**
 * @brief       void conf_adc ( void )
 * @details     It configures the ADC peripheral.
 *              
 *              ADC
 *                  - Temperature Indicator is enabled
 *                  - VOUT = VDD - 4VT (High Range)
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
 * @date        27/March/2024
 * @version     27/March/2024    The ORIGIN
 * @pre         N/A 
 * @warning     The user must respect the TACQ before start a new ADC conversion! TACQtyp ~ 200us
 * @warning     The user must respect the TCNV before start a new ADC conversion! TCNVtyp ~ 200us
 */
void conf_adc ( void )
{
    /* ADC disabled    */
    ADCON0bits.ADON  =   0U;
    
    /* Temperature Indicator channel enabled    */
    ADCON0bits.CHS  =   0b11101;
    
    /* ADC result format: Right justified   */
    ADCON1bits.ADFM =   1U;
    
    /* ADC Conversion Clock: FRC (clock supplied from a dedicated RC oscillator)   */
    ADCON1bits.ADCS =   0b011;
    
    /* VREF- is connected to VSS   */
    ADCON1bits.ADNREF   =   0U;
    
    /* VREF+ is connected to VDD   */
    ADCON1bits.ADPREF   =   0b00;
    
    /* VOUT = VDD - 4VT (High Range)    */
    FVRCONbits.TSRNG    =   1U;
    
    /* Temperature Indicator is enabled    */
    FVRCONbits.TSEN    =   1U;
    
    /* ADC enabled    */
    ADCON0bits.ADON  =   1U;
    
    // the user must wait at least 200us after the ADC input multiplexer is connected to the temperature indicator output before the conversion is performed 
    
    /* Clear ADC interrupt flag */
    PIR1bits.ADIF   =   0U;
    
    /* Enable Interrupt */
    PIE1bits.ADIE   =   1U;
}


/**
 * @brief       void conf_eusart ( void )
 * @details     It configures the EUSART in 16-bit asynchronous mode.
 *              
 *              Desire_baudrate = F_OSC/[4�(SPBRG+1)]
 * 
 *              EUSART
 *                  - 16-bit asynchronous mode
 *                  - F_OSC = 8MHz
 *                  - SPBRG = ( F_OSC/(4�Desire_baudrate) ) - 1 = ( 8000000/(4�115200) ) - 1 ~ 16 (0x0010)
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
 * @version     27/March/2024       Rx is disabled, F_OSC = 8MHz
 *              10/February/2024    The ORIGIN
 * @pre         Error = 100*( 115200 - 117647 )/115200 = 2.12%
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
    SPBRGL  =   0x10;
    
    /* Clear receiver (Rx) and transmission (Tx) interrupt flags   */
    PIR1bits.RCIF   =   0U;
    PIR1bits.TXIF   =   0U;
    
    /* Disable transmission (Tx) interrupt    */
    PIE1bits.TXIE   =   0U;
        
    /* Serial port enabled (configures RX/DT and TX/CK pins as serial port pins)    */
    RCSTAbits.SPEN  =   1U;
}