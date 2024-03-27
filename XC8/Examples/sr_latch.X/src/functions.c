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
 *                  - 2MHz
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
    
    /* Internal Oscillator Frequency: 2MHz  */
    OSCCONbits.IRCF =   0b1100;
    
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
 *                  - RA0: GPIO Analog Input pin (C12IN0-)
 *                  - RA3: GPIO Analog Input pin (C1IN+)
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
 * @version     27/March/2024       RA3 as a C1IN+ and RA0 as an C12IN0- pin
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
    
    /* RA0 and RA3 as analog inputs   */
    ANSELAbits.ANSA0    =   1U;
    ANSELAbits.ANSA3    =   1U;
    
    /* RC7 as an input pin */
    TRISC   |=  RX;
    
    /* RC6 as an output pin */
    TRISC   &=  ~( TX );
}


/**
 * @brief       void conf_comparator ( void )
 * @details     It configures the comparator peripheral.
 *              
 *              C1 comparator
 *                  - Comparator output is not inverted
 *                  - C1VP connects to C1IN+ pin
 *                  - C1VN connects to C12IN0- pin
 *                  - The C1IF interrupt flag will be set upon a positive going edge of the C1OUT bit
 *                  - The C1IF interrupt flag will be set upon a negative going edge of the C1OUT bit
 *                  - Comparator Output is internal only
 *                  - Comparator operates in low-power, low-speed mode
 *                  - Comparator hysteresis disabled
 *                  - Interrupt enabled
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
void conf_comparator ( void )
{
    /* Comparator disabled    */
    CM1CON0bits.C1ON  =   0U;
    
    /* Comparator output is not inverted    */
    CM1CON0bits.C1POL  =   0U;
    
    /* Comparator Output is internal only    */
    CM1CON0bits.C1OE  =   0U;
    
    /* Comparator operates in low-power, low-speed mode    */
    CM1CON0bits.C1SP  =   0U;
    
    /* Comparator hysteresis disabled    */
    CM1CON0bits.C1HYS  =   0U;
    
    /* C1VP connects to C1IN+ pin   */
    CM1CON1bits.C1PCH   =   0b00;
    
    /* Comparator Output Enabled   */
    CM1CON1bits.C1NCH   =   0b00;
    
    /* The C1IF interrupt flag will be set upon a positive going edge of the C1OUT bit   */
    CM1CON1bits.C1INTP   =   1U;
    
    /* The C1IF interrupt flag will be set upon a negative going edge of the C1OUT bit   */
    CM1CON1bits.C1INTN   =   1U;
    
    /* Comparator enabled    */
    CM1CON0bits.C1ON  =   1U;
        
    /* Clear C1 comparator interrupt flag */
    PIR2bits.C1IF   =   0U;
    
    /* Enable Interrupt */
    PIE2bits.C1IE   =   1U;
}