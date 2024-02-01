/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: WDT in SLeep mode.
 * 
 *              WDT will overflows every 512ms, when a WDT time-out occurs while the device is in
 *              sleep mode, no Reset is generated. Instead, the device wakes up and resumes operation,
 *              changing the state of the D5 LED.
 * 
 *              The microcontroller is in SLEEP mode the rest of the time.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        01/February/2024
 * @version     01/February/2024    The ORIGIN
 * @pre         This project was tested on a PIC16F1937 using a PICDEM 2 Plus.
 * @pre         When the device enters Sleep mode, the WDT is cleared. If the WDT is enabled during Sleep, the WDT resumes counting.
 * @warning     N/A
 */

// PIC16F1937 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = SWDTEN    // Watchdog Timer Enable (WDT controlled by the SWDTEN bit in the WDTCON register)
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
// #pragma config DEBUG = ON       // In-Circuit Debugger Mode (In-Circuit Debugger enabled, ICSPCLK and ICSPDAT are dedicated to the debugger)
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


/**@brief Function for application main entry.
 */
void main(void) {
    conf_CLK    ();
    conf_GPIO   ();
    conf_WDT    ();
    
    
    /* Disable interrupts    */
    INTCONbits.PEIE =   0U; // Disables all active peripheral interrupts
    INTCONbits.GIE  =   0U; // Disables all active interrupts
        
    while ( 1U )
    {
        /* Wait until WDT overflows (~512ms)    */
        SLEEP();
        
        /* Check if the wake-up is occurred by the WDT and by execution of the SLEEP instruction   */
        if ( ( STATUSbits.nTO == 0U ) && ( STATUSbits.nPD == 0U ) )
        {
            /* Change the state of D5 LED    */
            LATB    ^=  D5;
        }
    }
}
