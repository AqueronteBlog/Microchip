/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        31/January/2024
 * @version     31/January/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/functions.h"


/**
 * @brief       void conf_CLK ( void )
 * @details     It configures the clocks.
 * 
 *              MFINTOSC
 *                  - 125kHz
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
 * @date        31/January/2024
 * @version     31/January/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_CLK ( void )
{
    /* 4x PLL is disabled  */
    OSCCONbits.SPLLEN =   0U;
    
    /* Internal Oscillator Frequency: 125kHz  */
    OSCCONbits.IRCF =   0b0101;
    
    /* Internal oscillator block */
    OSCCONbits.SCS  =   0b11;
    
    while ( OSCSTATbits.MFIOFR == 0U ); // Wait until MFINTOSC is ready
}


/**
 * @brief       void conf_GPIO ( void )
 * @details     It configures GPIOs.
 * 
 *              PORTB
 *                  - RB0: GPIO Input pin, no pull-up
 *                  - RB1: GPIO Output pin, no pull-up
 *                  - RB2: GPIO Output pin, no pull-up
 *                  - RB3: GPIO Output pin, no pull-up
 *              
 *              PORTA
 *                  - RA4: GPIO Input pin
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
 * @version     15/December/2023    Turn all the LEDs off
 *                                  RA4 as an input pin
 *              08/December/2023    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_GPIO ( void )
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
}


/**
 * @brief       void conf_Timer0 ( void )
 * @details     It configures the Timer0.
 *              
 *              Timer0_overflow = 4·( 1/f_Timer0_OSC )·( 256 - TMR0)·Prescaler
 * 
 *              Timer0
 *                  - Overflow every 0.5s
 *                  - TMR0 = 256 - [ Timer0_overflow / ( Prescaler*4·( 1/f_Timer0_OSC ) ] = 256 - [ 0.5 / ( 256*4·( 1/125000 ) ] ~ 195
 *                  - Timer0 interrupt overflows enabled
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        31/January/2024
 * @version     31/January/2024    The ORIGIN
 * @pre         Error = 100*( 0.5079 0.5 )/0.5 = 1.58%
 * @warning     N/A
 */
void conf_Timer0 ( void )
{
    /* Prescaler is assigned to the Timer0 module */
    OPTION_REGbits.PSA   =  0U;
    
    /* Prescaler Rate Select bits: 256 */
    OPTION_REGbits.PS   =  0b111;
    
    /* Internal instruction cycle clock (FOSC/4) */
    OPTION_REGbits.TMR0CS   =  0U;
    
    /* Timer0 overflows every 0.5s  */
    TMR0    =   195U;
    
    /* Clear Timer0 interrupt flag */
    INTCONbits.TMR0IF   =   0U;
    
    /* Timer0 interrupt enabled */
    INTCONbits.TMR0IE   =   1U;
}