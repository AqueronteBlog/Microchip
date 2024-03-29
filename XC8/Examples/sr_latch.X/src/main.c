/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: SR Latch.
 * 
 *              Q and #Q will change their values every 0.26s according to the SR Latch pins: S and R.
 *              
 *              SR Latch:
 *                  - S = 1, R = 0 --> Q = 1, #Q = 0.  
 *                  - S = 0, R = 1 --> Q = 0, #Q = 1.
 *              
 *              The SR Latch is controlled by software using the SRPS and SRPR bits in SRCON0 register.
 *              Both bits change their values by the Timer4 every 0.26s.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        27/March/2024
 * @version     27/March/2024    The ORIGIN
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

/**@brief Variables.
 */

/**@brief Function prototypes.
 */
/** Delay function.
  */
void delay_260ms ( void );

/**@brief Function for application main entry.
 */
void main(void) { 
    conf_clk        ();
    conf_gpio       ();
    conf_Timer4     ();
    conf_sr_latch   ();
       
    /* Disable interrupts    */
    INTCONbits.PEIE =   0U; // Disable all active peripheral interrupts
    INTCONbits.GIE  =   0U; // Disable all active interrupts
       
    while ( 1U )
    {
        /* SR Latch. Set = 1, Reset = 0 --> Q = 1, #Q = 0   */
        SRCON0bits.SRPS =   1U;
        SRCON0bits.SRPR =   0U;
        delay_260ms ();
        
        /* SR Latch. Set = 0, Reset = 1 --> Q = 0, #Q = 1   */
        SRCON0bits.SRPS =   0U;
        SRCON0bits.SRPR =   1U;
        delay_260ms ();
    }
}



/**
 * @brief       void delay_260ms ( void )
 * @details     260ms delay function by Timer4 module (polling mode).
 *
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A.
 *
 * @author      Manuel Caballero
 * @date        29/March/2024
 * @version     29/March/2024   The ORIGIN
 * @pre         N/A
 * @warning     N/A.
 */
void delay_260ms ( void )
{
    /* Start timer4 */
    T4CONbits.TMR4ON   =  1U;
    
    /* Check if Timer4 Overflow is triggered by polling */
    while ( PIR3bits.TMR4IF == 0U );
    
    /* Clear the interrupt flag   */
    PIR3bits.TMR4IF = 0U;
    
    /* Stop timer4 */
    T4CONbits.TMR4ON   =  0U;
}
