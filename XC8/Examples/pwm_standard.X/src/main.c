/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: Standard PWM.
 * 
 *              A 1kHz signal with 50% duty cycle on pin RE2 is present when the program starts,
 *              when the user pushes the S3 button (RB0), the PWM duty cycle will change as shown below:
 * 
 *              - PWM duty cycle:
 *                  -   0%
 *                  -  25%
 *                  -  50%
 *                  -  75%
 *                  - 100%
 * 
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        13/February/2024
 * @version     13/February/2024    The ORIGIN
 * @pre         This project was tested on a PIC16F1937 using a PICDEM 2 Plus.
 * @warning     N/A
 * @pre         PWM: The Timer2/4/6 interrupt cannot wake the processor from Sleep since the timer is frozen during Sleep
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


/**@brief Function for application main entry.
 */
void main(void) {
    uint8_t myState;  // variable for changing the PWM duty cycle 
    
    conf_clk    ();
    conf_gpio   ();
    conf_pwm_standard ();
    
    /* Disable interrupts    */
    INTCONbits.PEIE =   0U; // Disable all active peripheral interrupts
    INTCONbits.GIE  =   0U; // Disable all active interrupts
    
    /* Reset the variables  */
    myState =   0U;
    
    while ( 1U )
    {
        /* Wait until S3 is pressed to change the PWM duty cycle    */
        while ( PORTBbits.RB0 == 1U );
        
        /* Anti-bouncing method    */
        while ( PORTBbits.RB0 == 0U );
        
        /* Disable the CCP5 pin output driver  */
        TRISE   |=   CCP5;
        
        switch ( myState )
        {
            default:
            case 0:
                /* Duty cycle: 0%   */
                CCPR5L              =   ( 0x00 >> 2U );
                CCP5CONbits.DC5B    =   ( 0b11 & 0x00 );
                
                /* Update my state variable, next state */
                myState =   1U;
                break;
                
            case 1:
                /* Duty cycle: 25%   */
                CCPR5L              =   ( 0x3F >> 2U );
                CCP5CONbits.DC5B    =   ( 0b11 & 0x3F );
                
                /* Update my state variable, next state */
                myState =   2U;
                break;
                
            case 2:
                /* Duty cycle: 50%   */
                CCPR5L              =   ( 0x7E >> 2U );
                CCP5CONbits.DC5B    =   ( 0b11 & 0x7E );
                
                /* Update my state variable, next state */
                myState =   3U;
                break;
                
            case 3:
                /* Duty cycle: 75%   */
                CCPR5L              =   ( 0xBD >> 2U );
                CCP5CONbits.DC5B    =   ( 0b11 & 0xBD );
                
                /* Update my state variable, next state */
                myState =   4U;
                break;
                
            case 4:
                /* Duty cycle: 100%   */
                CCPR5L              =   ( 0xFC >> 2U );
                CCP5CONbits.DC5B    =   ( 0b11 & 0xFC );
                
                /* Update my state variable, next state */
                myState =   0U;
                break;
        }
        
        /* Clear the TMR2IF interrupt flag */
        PIR1bits.TMR2IF   =   0U;
    
        /* Wait until the Timer2 overflows   */
        while ( PIR1bits.TMR2IF == 0U );
    
        /* Enable the CCP5 pin output driver  */
        TRISE   &=   ~CCP5;
    }
}
