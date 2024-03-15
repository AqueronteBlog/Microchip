/**
 * @brief       main.c
 * @details     [todo] This example shows how to work with the internal peripheral: Timer2/4/6.
 * 
 *              Timer1 will generate an interrupt every 0.5s changing the state of the D5 LED.
 *              Timer2 will change the state of the D4 LED every 1s by polling.
 *              Timer6 will generate an interrupt every 1.5s changing the state of the D3 LED.
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


/**@brief Variables.
 */
volatile uint8_t myState;   

/**@brief Function for application main entry.
 */
void main(void) {
    conf_clk    ();
    conf_gpio   ();
    conf_timer2 ();
    
    /* Enable interrupts    */
    INTCONbits.PEIE =   1U; // Enables all active peripheral interrupts
    INTCONbits.GIE  =   1U; // Enables all active interrupts
    
    /* Start timers */
    T2CONbits.TMR2ON   =  1U;
    
    /* Reset the variables  */
    myState =   0U;
    
    while ( 1U )
    {
        /* Update DAC output value    */
        if ( myState != 0U )
        {
            /* LED D5 on    */
            LATB   |=  D5;
            
            /* Reset the variable  */
            myState =   0U;
            
            /* LED D5 off    */
            LATB    &=  ~D5;
        }
    }
}
