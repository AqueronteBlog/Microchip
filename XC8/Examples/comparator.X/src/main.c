/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: Comparator (C1).
 * 
 *              C1- (RA0 -> C12IN0-) is the reference voltage while C1+ (RA3 -> C1IN+) is the input value.
 *              The D5 LED changes its state depending of C1 comparator:
 *                  - D5 LED ON:    C1+ > C1-
 *                  - D5 LED OFF:   C1+ <= C1-
 *                             
 *              The microcontroller is in SLEEP mode the rest of the time.  
 * 
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
volatile uint8_t    myFlag;         /* Flag that indicates if there is a change by the comparator module */

/**@brief Function for application main entry.
 */
void main(void) {    
    conf_clk        ();
    conf_gpio       ();
    conf_comparator ();
       
    /* Enable interrupts    */
    INTCONbits.PEIE =   1U; // Enables all active peripheral interrupts
    INTCONbits.GIE  =   1U; // Enables all active interrupts
    
    /* Reset variables  */
    myFlag  =   0U;
    
    while ( 1U )
    {
       /* Change the state of the D5 LED depending of C1 output, go to sleep mode otherwise */
        if ( myFlag != 0U )
        {
            /* Check comparator output  */
            if ( CMOUTbits.MC1OUT == 0U )
            {
                /* If comparator output is low, D5 LED is off then   */
                LATB    &=  ~D5;
            }
            else
            {
                /* If comparator output is high, D5 LED is on then   */
                LATB    |=  D5;
            }
            
            /* Reset variable  */
            myFlag  =   0U;  
        }
        else
        {
            SLEEP();
        }
    }
}
