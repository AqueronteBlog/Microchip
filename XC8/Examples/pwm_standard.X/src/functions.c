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
 * @date        13/February/2024
 * @version     13/February/2024    The ORIGIN
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
 * @version     13/February/2024    CCP5 enabled (PWM standard)
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
    
    /* RE2 as a digital I/O pin */
    ANSELE  &=  ~( CCP5 );
}


/**
 * @brief       void conf_pwm_standard ( void )
 * @details     It configures the standard PWM.
 *              
 *              PWM_period = ( PRx + 1 )·4·T_osc·TMRx_prescale
 * 
 *              Duty_cycle_ratio = ( CCPRxL:CCPxCON<5:4> )/[ 4·( PRx + 1 ) ]
 * 
 *              PEM standard
 *                  - PWM_period = 1ms (1kHz)
 *                  - Duty_cycle_ratio = 50% (Initial)
 *                  - PWM_standard: CCP5 (RE2)
 *                  - TMRx_prescale = 64
 *                  - f_Timerx_OSC = f_OSC = 16MHz
 *                  - PWM_period: PRx = [ PWM_period / ( 4·TMRx_prescale·( 1/f_Timerx_OSC ) ] - 1 = [ 0.001 / ( 64*4·( 1/16000000 ) ] - 1 ~ 62
 *                  - Duty_cycle_ratio: CCPRxL:CCPxCON<5:4> = Duty_cycle_ratio·[ 4·( PRx + 1 ) ] = 50·[ 4·( 62 + 1 ) ] / 100 = 126 (0x7E)
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
 * @pre         Error = 100*( 0.5 - 0.4997 )/0.5 = 0.06%
 * @warning     N/A
 */
void conf_pwm_standard ( void )
{
    /* Disable the CCP5 pin output driver  */
    TRISE   |=   CCP5;
        
    /* Load the PRx register with the PWM period value  */
    PR2    =   62U;
    
    /* Configure the CCP5 module for the PWM mode    */
    CCP5CONbits.CCP5M   =  0b1100;
    
    /* Configure the PWM standard duty cycle: 50% (Initial value) */
    CCPR5L              =   ( 0x7E >> 2U );
    CCP5CONbits.DC5B    =   ( 0b11 & 0x7E );
    
    /* Select the Timer2 resource to be used for PWM generation */
    CCPTMRS1bits.C5TSEL   =   0b00;
    
    /* Clear the TMR2IF interrupt flag */
    PIR1bits.TMR2IF   =   0U;
    
    /* Configure the T2CKPS bits.  Prescaler is 64    */
    T2CONbits.T2CKPS    =   0b11;
    
    /* Enable the Timer2 */
    T2CONbits.TMR2ON    =   1U;
    
    /* Wait until the Timer2 overflows   */
    while ( PIR1bits.TMR2IF == 0U );
    
    /* Enable the CCP5 pin output driver  */
    TRISE   &=   ~CCP5;
}