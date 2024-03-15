/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        15/March/2024
 * @version     15/March/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/functions.h"


/**
 * @brief       void conf_clk ( void )
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
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_clk ( void )
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
 *                  - RA2: GPIO Output pin
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
 * @version     15/March/2024       RA2 as a digital output
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
    
    /* RA2 (DACOUT) as a digital output pin */
    //TRISAbits.TRISA2    =   0U;
    
    /* RA4 as an input pin */
    TRISA   |=  S2;
}


/**
 * @brief       void conf_timer2 ( void )
 * @details     It configures the Timer2.
 *              
 *              TMR2_flag ( TMR2 = PR2 ) = ( 1/( f_Timer2_OSC/4 ) )·Prescaler
 * 
 *              Timer2
 *                  - TMR2 overflows every 0.25s
 *                  - PR2 = [ TMR2_flag / ( 4·Prescaler·( 1/f_Timer2_OSC ) ] = [ 0.25 / ( 64*4·( 1/125000 ) ] ~ 122
 *                  - TMR2 flag enabled every 0.25s: 0.25s*Postcaler = 0.25*1 = 0.25s 
 *                  - Timer2 interrupt disabled
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/March/2024
 * @version     15/March/2024    The ORIGIN
 * @pre         Error = 100*( 0.25 - 0.249856 )/0.25 ~ 0.06%
 * @warning     N/A
 */
void conf_timer2 ( void )
{
    /* Stops Timer2 */
    T2CONbits.TMR2ON   =  0U;
        
    /* Prescaler is 64 */
    T2CONbits.T2CKPS   =  0b11;
    
    /* 1:1 Postscaler */
    T2CONbits.T2OUTPS   =  0b0000;
    
    /* Timer2 overflows every 0.25s ( TMR2 = PR2 )  */
    PR2    =   122U;
    
    /* Clear Timer2 interrupt flag */
    PIR1bits.TMR2IF   =   0U;
    
    /* Timer2 interrupt disabled */
    PIE1bits.TMR2IE   =   0U;
}


/**
 * @brief       void conf_dac ( void )
 * @details     It configures the DAC with DACOUT pin enabled.
 *              
 *              V_DAC_OUT = [ ( V_SOURCE+ - V_SOURCE- ) * ( DACR<4:0> / 32 ) } + V_SOURCE-
 * 
 *              DAC
 *                  - DAC Positive Source = VDD
 *                  - DAC Negative Source = VSS
 *                  - DAC voltage level is also an output on the DACOUT pin
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        15/March/2024
 * @version     15/March/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_dac ( void )
{
    /* DAC disabled */
    DACCON0bits.DACEN   =   0U;
      
    /* DAC Positive Source = VDD */
    DACCON0bits.DACPSS   =   0b00;
    
    /* DAC Negative Source = VSS */
    DACCON0bits.DACNSS   =   0U;
    
    /* DAC out starts as 0 value */
    DACCON1bits.DACR    =   0b00000;
    
    /* DAC voltage level is also an output on the DACOUT pin    */
    DACCON0bits.DACOE   =   1U;
    
    /* DAC enabled */
    DACCON0bits.DACEN   =   1U;
}