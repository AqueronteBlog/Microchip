/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: DAC with DACOUT pin enabled.
 * 
 *              A Triangle wave is generated on DACOUT (RA2) pin. The DAC output is updated every 0.26s by
 *              the Timer 2 (polling mode).
 *              
 *              D5 LED indicates when the triangle wave goes up (D5 on) or down (D5 off).
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        15/March/2024
 * @version     15/March/2024    The ORIGIN
 * @pre         This project was tested on a PIC16F1937 using a PICDEM 2 Plus.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - X:       https://twitter.com/aqueronteblog
 */

// PIC16F1937 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
//#pragma config DEBUG = ON       // In-Circuit Debugger Mode (In-Circuit Debugger enabled, ICSPCLK and ICSPDAT are dedicated to the debugger)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "../inc/board.h"
#include "../inc/functions.h"
#include "../inc/interrupts.h"

/**@brief Constants.
 */
#define DAC_RESOLUTION  ( 32U - 1U )    /*!< DAC resolution: 5-bit */

/**@brief Variables.
 */ 

/**@brief Function prototypes.
 */
/** Timer2 delay function.
  */
static void timer2_delay ( void );

/**@brief Function for application main entry.
 */
void main(void) {
    uint8_t dac_out =   0U;
    
    conf_clk    ();
    conf_gpio   ();
    conf_dac    ();
    conf_timer2 ();
    
    /* Disable interrupts    */
    INTCONbits.PEIE =   0U; // Disable all active peripheral interrupts
    INTCONbits.GIE  =   0U; // Disable all active interrupts
    
    /* Start timers */
    T2CONbits.TMR2ON   =  1U;
    
    /* Reset the variables  */
    dac_out =   0U;
    
    while ( 1U )
    {
        /* DAC output value goes up, turn D5 LED on */
        LATB    |=  D5;
        for ( dac_out = 0U; dac_out < DAC_RESOLUTION; dac_out++ )
        {
            /* Update DAC out value */
            DACCON1bits.DACR    =   dac_out;
            
            /* Delay for the next DAC output value  */
            timer2_delay ();
        }
        
        /* DAC output value goes down, turn D5 LED off */
         LATB    &=  ~D5;
        for ( dac_out = DAC_RESOLUTION; dac_out > 0U; dac_out-- )
        {
            /* Update DAC out value */
            DACCON1bits.DACR    =   dac_out;
            
            /* Delay for the next DAC output value  */
            timer2_delay ();
        }
    }
}


/**
 * @brief       void timer2_delay ( void )
 * @details     Timer2 delay function, it waits until Timer2 overflows.
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
 * @date        15/March/2024
 * @version     15/March/2024   The ORIGIN
 * @pre         N/A
 * @warning     It is recommended to add a timeout to unblock this function in case of an unexpected issue.
 *              This is a blocking function.
 */
static void timer2_delay ( void )
{
    /* [Polling] Wait until Timer2 overflows */
    while ( PIR1bits.TMR2IF == 0U );                  
            
    /* Clear the interrupt flag   */
    PIR1bits.TMR2IF = 0U;
}