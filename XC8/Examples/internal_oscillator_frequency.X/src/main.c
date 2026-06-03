/**
 * @brief       main.c
 * @details     This programs shows how to work with the internal peripheral: Internal Oscillator Frequency.
 *              A new internal oscillator frequency is selected when the button is pressed.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        03/June/2026
 * @version     03/June/2026    The ORIGIN
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
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = ON    // Clock Out Enable (CLKOUT function is enabled on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
//#pragma config DEBUG = OFF      // In-Circuit Debugger Mode (In-Circuit Debugger disabled, ICSPCLK and ICSPDAT are general purpose I/O pins)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


/**@brief Variables.
 */


/**@brief Function for application main entry.
 */
void main(void) { 
    uint8_t mystate;
    
    conf_clk    ();
    conf_gpio   ();
    
    /* Disable  interrupts  */
    INTCONbits.PEIE =   0U;
    INTCONbits.GIE  =   0U;
    
    /* Reset variables  */
    mystate =   0U;
    
    while ( 1U )
    {
         /* Change the state of D5 when S2 is pressed    */
        if ( ( PORTA & S2_MSK ) == 0U )
        {
            /* Debouncing - Wait until S2 is released   */
            while ( ( PORTA & S2_MSK ) == 0U );
            
            /* Change the internal clock source frequency   */
            switch (mystate)
            {
                default:
                case 0U:
                    /* Internal oscillator block: 31kHz LF */
                    OSCCONbits.IRCF  =   0b0000;
                    while ( OSCSTATbits.LFIOFR == 0U ); // Wait until LFINTOSC is ready
                    
                    /* Next state   */
                    mystate =   1U;
                    break;
                
                case 1U:
                    /* Internal oscillator block: 125kHz LF */
                    OSCCONbits.IRCF  =   0b0101;
                    while ( OSCSTATbits.MFIOFR == 0U ); // Wait until MFINTOSC is ready
                    
                    /* Next state   */
                    mystate =   2U;
                    break;
                
                case 2U:
                    /* Internal oscillator block: 500kHz MF */
                    OSCCONbits.IRCF  =   0b0111;
                    while ( OSCSTATbits.MFIOFR == 0U ); // Wait until MFINTOSC is ready
                    
                    /* Next state   */
                    mystate =   3U;
                    break;
                    
                case 3U:
                    /* Internal oscillator block: 8MHz HF */
                    OSCCONbits.IRCF  =   0b1110;
                    while ( OSCSTATbits.HFIOFR == 0U ); // Wait until HFINTOSC is ready
                    
                    /* Next state   */
                    mystate =   4U;
                    break;
                    
                case 4U:
                    /* Internal oscillator block: 16MHz HF */
                    OSCCONbits.IRCF  =   0b1111;
                    while ( OSCSTATbits.HFIOFR == 0U ); // Wait until HFINTOSC is ready
                    
                    /* Next state   */
                    mystate =   0U;
                    break;
            }
        }
    }
}
