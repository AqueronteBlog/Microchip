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
 * @date        13/February/2024
 * @version     13/February/2024    The ORIGIN
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
 * @brief       void conf_Timer2 ( void )
 * @details     It configures the Timer2.
 *              
 *              TMR2_flag ( TMR2 = PR2 ) = ( 1/( f_Timer2_OSC/4 ) )·Prescaler
 * 
 *              Timer2
 *                  - TMR2 overflows every 0.5s
 *                  - PR2 = [ TMR2_flag / ( 4·Prescaler·( 1/f_Timer2_OSC ) ] = [ 0.5 / ( 64*4·( 1/125000 ) ] ~ 244
 *                  - TMR2 flag enabled every 0.5s: 0.5s*Postcaler = 0.5*1 = 0.5s 
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
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
 * @pre         Error = 100*( 0.5 - 0.4997 )/0.5 = 0.06%
 * @warning     N/A
 */
void conf_Timer2 ( void )
{
    /* Stops Timer2 */
    T2CONbits.TMR2ON   =  0U;
        
    /* Prescaler is 64 */
    T2CONbits.T2CKPS   =  0b11;
    
    /* 1:1 Postscaler */
    T2CONbits.T2OUTPS   =  0b0000;
    
    /* Timer2 overflows every 0.5s ( TMR2 = PR2 )  */
    PR2    =   244U;
    
    /* Clear Timer2 interrupt flag */
    PIR1bits.TMR2IF   =   0U;
    
    /* Timer2 interrupt enabled */
    PIE1bits.TMR2IE   =   1U;
}


/**
 * @brief       void conf_Timer4 ( void )
 * @details     It configures the Timer4.
 *              
 *              TMR4_flag ( TMR4 = PR4 ) = ( 1/( f_Timer4_OSC/4 ) )·Prescaler
 * 
 *              Timer4
 *                  - TMR2 overflows every 0.5s
 *                  - PR4 = [ TMR4_flag / ( 4·Prescaler·( 1/f_Timer4_OSC ) ] = [ 0.5 / ( 64*4·( 1/125000 ) ] ~ 244
 *                  - TMR4 Flag enabled every 1s: 0.5s*Postcaler = 0.5*2 = 1s 
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
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
 * @pre         Error = 100*( 0.5 - 0.4997 )/0.5 = 0.06%
 * @warning     N/A
 */
void conf_Timer4 ( void )
{
    /* Stops Timer4 */
    T4CONbits.TMR4ON   =  0U;
        
    /* Prescaler is 64 */
    T4CONbits.T4CKPS   =  0b11;
    
    /* 1:2 Postscaler */
    T4CONbits.T4OUTPS   =  0b0001;
    
    /* Timer4 overflows every 0.5s ( TMR4 = PR4 )  */
    PR4    =   244U;
    
    /* Clear Timer4 interrupt flag */
    PIR3bits.TMR4IF   =   0U;
    
    /* Timer4 interrupt disabled */
    PIE3bits.TMR4IE   =   0U;
}


/**
 * @brief       void conf_Timer6 ( void )
 * @details     It configures the Timer6.
 *              
 *              TMR6_flag ( TMR6 = PR6 ) = ( 1/( f_Timer6_OSC/4 ) )·Prescaler
 * 
 *              Timer6
 *                  - TMR6 overflows every 0.5s
 *                  - PR6 = [ TMR6_flag / ( 4·Prescaler·( 1/f_Timer6_OSC ) ] = [ 0.5 / ( 64*4·( 1/125000 ) ] ~ 244
 *                  - TMR6 flag enabled every 1.5s: 0.5s*Postcaler = 0.5*3 = 1.5s 
 *                  - Timer6 interrupt enabled
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
 * @pre         Error = 100*( 0.5 - 0.4997 )/0.5 = 0.06%
 * @warning     N/A
 */
void conf_Timer6 ( void )
{
    /* Stops Timer2 */
    T6CONbits.TMR6ON   =  0U;
        
    /* Prescaler is 64 */
    T6CONbits.T6CKPS   =  0b11;
    
    /* 1:3 Postscaler */
    T6CONbits.T6OUTPS   =  0b0010;
    
    /* Timer6 overflows every 0.5s ( TMR6 = PR6 )  */
    PR6    =   244U;
    
    /* Clear Timer6 interrupt flag */
    PIR3bits.TMR6IF   =   0U;
    
    /* Timer6 interrupt enabled */
    PIE3bits.TMR6IE   =   1U;
}