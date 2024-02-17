/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        17/February/2024
 * @version     17/February/2024    The ORIGIN
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
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
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
 *              PORTC
 *                  - RC4: GPIO Input pin (I2C_SDA)
 *                  - RC3: GPIO Input pin (I2C_SCL)
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
 * @version     17/February/2024    I2C pins were added
 *              15/December/2023    Turn all the LEDs off
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
    
    /* I2C. RC3 (SCL) and RC4 (SDA) as an input pin */
    TRISC   |=  ( SDA | SCL );
}


/**
 * @brief       void conf_master_i2c ( void )
 * @details     It configures the I2C peripheral.
 * 
 *              SCL_F_CLOCK = F_OSC / ( 4*( SSPxADD + 1 ) )
 *              
 *              I2C
 *                  - Master mode.
 *                  - Polling mode (interrupts disabled)
 *                  - SCL_F_CLOCK = 100kHz. SSPxADD = ( F_OSC / ( 4*SCL_F_CLOCK ) ) - 1 = ( 16MHz / ( 4*100kHz ) ) - 1 = 39
 *                  - F_OSC = 16MHz
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        17/February/2024
 * @version     17/February/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_master_i2c ( void )
{
    /* Disable the serial port and configures the SDA and SCL pins */
    SSPCON1bits.SSPEN    =   0U;
    
    /*  I2C Master mode */
    SSPCON1bits.SSPM    =   0b1000;
    
    /* Disable all I2C interrupts   */
    SSPCON3bits.PCIE    =   0U;
    SSPCON3bits.SCIE    =   0U;
    
    /*  Minimum of 100 ns hold time on SDA after the falling edge of SCL   */
    SSPCON3bits.SDAHT    =   0U;
    
    /*  SCL pin clock = 100kHz   */
    SSPADD    =   39U; 
    
    /* Enable the serial port and configures the SDA and SCL pins */
    SSPCON1bits.SSPEN    =   1U;
}