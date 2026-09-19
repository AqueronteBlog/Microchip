/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        13/February/2024
 * @version     13/February/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/functions.h"


/**
 * @brief       void conf_clk ( void )
 * @details     It configures the clocks.
 * 
 *              XT
 *                  - 4MHz
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
 * @date        19/September/2026
 * @version     19/September/2026    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_clk ( void )
{
    /* 4x PLL is disabled  */
    OSCCONbits.SPLLEN =   0U;
    
    /* Clock determined by FOSC<2:0> in Configuration Word 1    */
    OSCCONbits.SCS  =   0b00;
    
    while (OSCSTATbits.OSTS ==  0U);    // Wait until running from the clock defined by FOSC is stable
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
 *                  - RA4: GPIO Input pin
 *              
 *              PORTE
 *                  - RE2: GPIO output pin (CCP5)
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
    
    /* RE2 as digital I/0 pin   */
    ANSELE  &=  ~(CCP5);
}


/**
 * @brief       void conf_timer4 ( void )
 * @details     It configures the Timer4.
 *              
 *              TMR4_flag ( TMR4 = PR4 ) = ( 1/( f_Timer4_OSC/4 ) )·Prescaler
 * 
 *              Timer4
 *                  - TMR2 overflows every 16ms
 *                  - f_Timer4_OSC = 4MHz
 *                  - PR4 = [ TMR4_flag / ( 4·Prescaler·( 1/f_Timer4_OSC ) ] = [ 16ms / ( 64*4·( 1/4MHz ) ] = 250
 *                  - TMR4 Flag enabled every 256ms: 16ms*Postscaler = 16ms*16 = 256ms 
 *                  - Timer4 interrupt disabled
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/September/2026
 * @version     19/September/2026    The ORIGIN
 * @pre         Error = 100*( 256ms - 256ms )/256ms = 0%
 * @warning     N/A
 */
void conf_timer4 ( void )
{
    /* Stops Timer4 */
    T4CONbits.TMR4ON   =  0U;
        
    /* Prescaler is 64 */
    T4CONbits.T4CKPS   =  0b11;
    
    /* 1:16 Postscaler */
    T4CONbits.T4OUTPS   =  0b1111;
    
    /* Timer4 overflows every 16ms ( TMR4 = PR4 - before Postscaler!, every 256ms afterwards - )  */
    PR4    =   250U;
    
    /* Clear Timer4 interrupt flag */
    PIR3bits.TMR4IF   =   0U;
    
    /* Timer4 interrupt disabled */
    PIE3bits.TMR4IE   =   0U;
}
