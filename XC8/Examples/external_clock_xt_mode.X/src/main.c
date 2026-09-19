/**
 * @brief       main.c
 * @details     This programs shows how to work with the external clock (XT) mode as a main frequency source.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        19/September/2026
 * @version     19/September/2026    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         N/A
 */
#include "../inc/board.h"
#include "../inc/functions.h"
#include "../inc/interrupts.h"

/**@brief Constants.
 */
// PIC16F1937 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection (XT Oscillator, Crystal/resonator connected between OSC1 and OSC2 pins)
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
// #pragma config DEBUG = OFF      // In-Circuit Debugger Mode (In-Circuit Debugger disabled, ICSPCLK and ICSPDAT are general purpose I/O pins)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void main(void) {    
    conf_clk    ();
    conf_gpio   ();
    conf_timer4 ();
    
    /* Disable interrupts    */
    INTCONbits.PEIE =   0U; // Disable all active peripheral interrupts
    INTCONbits.GIE  =   0U; // Disable all active interrupts
    
    /* Start timer */
    T4CONbits.TMR4ON   =  1U;
    
    while ( 1U )
    {
        /* Check if Timer4 Overflow is triggered by polling */
        if ( PIR3bits.TMR4IF == 1U )
        { 
            /* Change the state of D4 LED    */
            LATB    ^=  D4;
            
            /* Clear the interrupt flag   */
            PIR3bits.TMR4IF = 0U;
        } 
    }
}
