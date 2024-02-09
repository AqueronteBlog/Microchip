/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: Timer2/4/6.
 * 
 *              Timer1 will generate an interrupt every 0.5s changing the state of the D5 LED.
 *              Timer2 will change the state of the D4 LED every 1s by polling.
 *              Timer6 will generate an interrupt every 1.5s changing the state of the D3 LED.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
 * @pre         This project was tested on a PIC16F1937 using a PICDEM 2 Plus.
 * @warning     N/A
 * @pre         The Timer2/4/6 interrupt cannot wake the processor from Sleep since the timer is frozen during Sleep
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
volatile uint8_t myState;   // BIT0 -> D5 LED | BIT1 -> D3 LED

/**@brief Function for application main entry.
 */
void main(void) {
    conf_CLK    ();
    conf_GPIO   ();
    conf_Timer2 ();
    conf_Timer4 ();
    conf_Timer6 ();
    
    /* Enable interrupts    */
    INTCONbits.PEIE =   1U; // Enables all active peripheral interrupts
    INTCONbits.GIE  =   1U; // Enables all active interrupts
    
    /* Start timers */
    T2CONbits.TMR2ON   =  1U;
    T4CONbits.TMR4ON   =  1U;
    T6CONbits.TMR6ON   =  1U;
    
    /* Reset the variables  */
    myState =   0U;
    
    while ( 1U )
    {
        /* Check if an interrupt is triggered by TMR2 or TMR6    */
        if ( myState != 0U )
        {
            /* Check if TMR2 interrupt is triggered */
            if ( ( myState & 0b01 ) != 0U )
            {
                /* Change the state of D5 LED    */
                LATB    ^=  D5;
            
                /* Reset the variable  */
                myState &=   ~0b01;
            }
            
            /* Check if TMR6 interrupt is triggered */
            if ( ( myState & 0b10 ) != 0U )
            {
                /* Change the state of D3 LED    */
                LATB    ^=  D3;
            
                /* Reset the variable  */
                myState &=   ~0b10;
            }
        }
        else
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
}
