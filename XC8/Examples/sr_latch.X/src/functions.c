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
 *                  - 1MHz
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
    
    /* Internal Oscillator Frequency: 1MHz  */
    OSCCONbits.IRCF =   0b1011;
    
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
 *                  - RA5: GPIO Output pin (SR Latch. SRnQ function is on RA5)
 *                  - RA4: GPIO Output pin (SR Latch. SRQ function is on RA4)
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
 * @version     29/March/2024       R4 (SRQ) and R5 (SRnQ) as SR Latch pins.
 *              27/March/2024       The ORIGIN
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
    
    /* RA5 and RA4 as digital I/O pins */
    ANSELAbits.ANSA5  =  0U;
    ANSELAbits.ANSA4  =  0U;
    
    /* RA5 and RA4 as output pins */
    TRISAbits.TRISA5  =  0U;
    TRISAbits.TRISA4  =  0U;
    
    /* SRnQ function is on RA5 */
    APFCONbits.SRNQSEL  =   0U;
}


/**
 * @brief       void conf_sr_latch ( void )
 * @details     It configures the SR latch peripheral.
 *              
 *              SR Latch
 *                  - External Q output is disabled
 *                  - Q is present on the SRQ pin
 *                  - #Q is present on the SRnQ pin
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
void conf_sr_latch ( void )
{
    /* SR Latch is disabled    */
    SRCON0bits.SRLEN    =   0U;
    
    /* External Q output is disabled    */
    SRCON0bits.SRQEN    =   0U;
    
    /* Q is present on the SRQ pin    */
    SRCON0bits.SRQEN   =   1U;
    
    /* #Q is present on the SRnQ pin    */
    SRCON0bits.SRNQEN   =   1U;
    
    /* SR Latch is ENABLED    */
    SRCON0bits.SRLEN    =   1U;
}


/**
 * @brief       void conf_Timer4 ( void )
 * @details     It configures the Timer4.
 *              
 *              TMR4_flag ( TMR4 = PR4 ) = ( 1/( f_Timer4_OSC/4 ) )·Prescaler
 * 
 *              Timer4
 *                  - FOSC = 1MHz
 *                  - TMR2 overflows every 65.28ms
 *                  - PR4 = [ TMR4_flag / ( 4·Prescaler·( 1/f_Timer4_OSC ) ] = [ 65.28ms / ( 64*4·( 1/1000000 ) ] = 255
 *                  - TMR4 Flag enabled every ~ 0.26s: 65.28ms*Postcaler = 65.28ms*4 ~ 0.26s
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
 * @date        29/March/2024
 * @version     29/March/2024    The ORIGIN
 * @pre         Error = 100*( 0.26 - 0.26112 )/0.26 ~ 0.43%
 * @warning     N/A
 */
void conf_Timer4 ( void )
{
    /* Stops Timer4 */
    T4CONbits.TMR4ON   =  0U;
        
    /* Prescaler is 64 */
    T4CONbits.T4CKPS   =  0b11;
    
    /* 1:4 Postscaler */
    T4CONbits.T4OUTPS   =  0b0011;
    
    /* Timer4 overflows every 65.28ms ( TMR4 = PR4 )  */
    PR4    =   255U;
    
    /* Clear Timer4 interrupt flag */
    PIR3bits.TMR4IF   =   0U;
    
    /* Timer4 interrupt disabled */
    PIE3bits.TMR4IE   =   0U;
}