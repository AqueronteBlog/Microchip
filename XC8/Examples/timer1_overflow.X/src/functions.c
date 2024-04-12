/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        11/April/2024
 * @version     11/April/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/functions.h"


/**
 * @brief       void conf_clk ( void )
 * @details     It configures the clocks.
 * 
 *              HFINTOSC
 *                  - 32MHz
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
 * @date        11/April/2024
 * @version     11/April/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_clk ( void )
{
    /* 4x PLL is enabled  */
    OSCCONbits.SPLLEN =   1U;
    
    /* Internal Oscillator Frequency: 4 * 8MHz = 32MHz  */
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
 *                  - RC0: GPIO Output pin (T1OSO)
 *                  - RC1: GPIO Output pin (T1OSI)
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
 * @date        11/April/2024
 * @version     11/April/2024    The ORIGIN
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
    
    /* RC0 as an output pin*/
    TRISCbits.TRISC0    =   0U;
    
    /* RC1 as an input pin*/
    TRISCbits.TRISC1    =   1U;
    
    /* RC7 as an input pin */
    TRISC   |=  RX;
    
    /* RC6 as an output pin */
    TRISC   &=  ~( TX );
}


/**
 * @brief       void conf_timer1 ( void )
 * @details     It configures the Timer1.
 * 
 *               TMR1_flag = ( ( 65536 - TMR1 )/( f_Timer1_OSC ) )·Prescaler
 * 
 *              Timer1
 *                  - TMR1 overflows every 0.5s
 *                  - 1:1 Prescale
 *                  - Crystal oscillator on T1OSI/T1OSO pins = 32.768kHz
 *                  - [TMR1H, TMR1L] = [ TMR1_flag / ( Prescaler·( 1/f_Timer2_OSC ) ] = 65536 - [ 0.5 / ( 1·( 1/32.768kHz ) ] = 49152 (0xC000) [TMR1H = 0xC0, TMR1L = 0x00]
 *                  - Timer1 overflow interrupt enable
 *                  - Stabilization for Timer1 external crystal is done
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        11/April/2024
 * @version     11/April/2024    The ORIGIN
 * @pre         N/A 
 * @warning     N/A
 */
void conf_timer1 ( void )
{
    /* Stop Timer1 */
    T1CONbits.TMR1ON    =   0U;
    
    /* Crystal oscillator on T1OSI/T1OSO pins   */
    T1CONbits.TMR1CS    =   0b10;
    
    /* Dedicated Timer1 oscillator circuit enabled   */
    T1CONbits.T1OSCEN    =   1U;
    
    /* Timer1 1:1 Prescale value   */
    T1CONbits.T1CKPS    =   0b00;
    
    /* Do not synchronize external clock input   */
    T1CONbits.nT1SYNC    =   1U;
    
    /* Delay to ensure a safe start-up and stabilization     */
    TMR1H   =   0xFC;
    TMR1L   =   0x00;
       
    /* Clear Timer1 overflow flag   */
    PIR1bits.TMR1IF =   0U;
    
    /* Interrupt Timer1 overflow enabled   */
    PIE1bits.TMR1IE =   0U;
    
    /* Start Timer1 */
    T1CONbits.TMR1ON    =   1U;
    
    /*  Wait for this delay for the clock stabilization   */
    while ( PIR1bits.TMR1IF ==   0U );
    
    /* Stop Timer1 */
    T1CONbits.TMR1ON    =   0U;
    
    /* Timer1 overflows every 0.5s  */
    TMR1H   =   0xC0;
    TMR1L   =   0x00;
    
    /* Clear Timer1 overflow flag   */
    PIR1bits.TMR1IF =   0U;
    
    /* Interrupt Timer1 overflow enabled   */
    PIE1bits.TMR1IE =   1U;
}