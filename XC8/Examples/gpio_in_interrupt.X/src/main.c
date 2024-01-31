/**
 * @brief       main.c
 * @details     This program shows how to work with the internal peripheral: External interrupt (INT).
 *              Every time that RB0 goes from high level to low level, the D5 LED changes its state.
 * 
 *              The microcontroller is in sleep mode the rest of the time.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        30/January/2024
 * @version     30/January/2024    The ORIGIN
 * @pre         The PIC16F1937 has the INT on RB0.
 * @warning     N/A
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
volatile uint8_t myState;

/**@brief Function for application main entry.
 */
void main(void) {
    conf_GPIO ();
    
    /* Interrupt on falling edge of INT pin */
    OPTION_REGbits.INTEDG   =   0U; 
    
    /* Enable interrupts    */
    INTCONbits.PEIE =   0U; // Disable all active peripheral interrupts
    INTCONbits.INTE =   1U; // Enables the INT external interrupt
    INTCONbits.GIE  =   1U; // Enables all active interrupts
    
    /* Reset the variables  */
    myState =   0U;
    
    while ( 1U )
    {
        /* Check if an interrupt is triggered on RB0    */
        if ( myState == 1U )
        {
            /* Change the state of D5 LED    */
            LATB    ^=  D5;
            
            /* Reset the variable  */
            myState =   0U;
        }
        else
        {
            /* Low power mode   */
            SLEEP();
        }
    }
}
