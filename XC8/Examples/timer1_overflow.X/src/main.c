/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: Timer1.
 * 
 *              Timer1 clock is connected to an external 32.768kHz crystal, it overflows every 0.5s making
 *              the D5 LED change its state.
 * 
 *              The microcontroller is in sleep mode the rest of the time.
 * 
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        11/April/2024
 * @version     11/April/2024    The ORIGIN
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
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
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
volatile uint8_t    myFlag;         /* Flag that indicates either if the Timer overflows    */

/**@brief Function prototypes.
 */


/**@brief Function for application main entry.
 */
void main(void) {        
    conf_clk    ();
    conf_gpio   ();
    conf_timer1 ();
       
    /* Enable/disable interrupts    */
    INTCONbits.PEIE =   1U; // Enable all active peripheral interrupts
    INTCONbits.GIE  =   1U; // Enable all active interrupts
        
    /* Reset variables  */
    myFlag  =   0U;
    
    /* Start Timer1 */
    T1CONbits.TMR1ON   =  1U;
        
    while ( 1U )
    {
        if ( myFlag ==  1U )
        {
            /* Stop Timer1 */
            T1CONbits.TMR1ON   =  0U;
            
            /* Change the D5 LED state  */
            LATB    ^=  D5;
            
            /* Timer1 overflows every 0.5s  */
            TMR1H   =   0xC0;
            TMR1L   =   0x00;
    
            /* Clear flag   */
            myFlag  =   0U;
            
            /* Start Timer1 */
            T1CONbits.TMR1ON   =  1U;
        }
        else
        {
            /* Sleep mode   */
            SLEEP();
        }
    }
}