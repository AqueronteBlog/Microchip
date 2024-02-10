/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: EUSART as asynchronous mode.
 * 
 *              D5 LED changes its state depending on what it is received over the UART:
 *                  - D5 LED ON:    1, it is received from the UART.
 *                  - D5 LED OFF:   2, it is received from the UART.
 *              
 *              Anytime a character is received, it will transmit the state of D5 LED, if
 *              another character is received, D5 LED turns off and an error message is sent over the UART.
 * 
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        10/February/2024
 * @version     10/February/2024    The ORIGIN
 * @pre         This project was tested on a PIC16F1937 using a PICDEM 2 Plus.
 * @pre         In asynchronous mode, the SLEEP mode cannot be used due to EUSART clock source (F_OSC).
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
#define EUSART_BUFF 16


/**@brief Variables.
 */
volatile uint8_t    myState;    /* State that indicates when to perform the next action */
volatile uint8_t    *myPtr;     /* Pointer to point out myMessage   */

/**@brief Function for application main entry.
 */
void main(void) {
    uint8_t my_message[EUSART_BUFF] = {0};
    
    conf_clk    ();
    conf_gpio   ();
    conf_eusart ();
    
    /* Initiate variable  */
    my_message[0]   =   'L';
    my_message[1]   =   'E';
    my_message[2]   =   'D';
    my_message[3]   =   ' ';
    my_message[4]   =   'D';
    my_message[5]   =   '5';
    my_message[6]   =   ' ';
    my_message[7]   =   '0';
    my_message[8]   =   'F';
    my_message[9]   =   'F';
    my_message[10]  =   '\n';
    
    /* Enable interrupts    */
    INTCONbits.PEIE =   1U; // Enables all active peripheral interrupts
    INTCONbits.GIE  =   1U; // Enables all active interrupts
    
    /* Reset variables  */
    myState =   0U;
    
    while ( 1U )
    {
        if ( myState != 0U )
		{
            /* Reset variable  */
            my_message[5]   =   '5';
            my_message[6]   =   ' ';
            my_message[7]   =   'O';
    
			switch ( myState )
			{
				case '1':
					/* Turn D5 on	 */
					LATB    |=  D5;
					my_message[8]   =   'N';
                    my_message[9]  =   '\n';
					break;

				case '2':
					/* Turn D5 off	 */
					LATB    &=  ~D5;
					my_message[8]   =   'F';
                    my_message[9]   =   'F';
                    my_message[10]  =   '\n';
					break;

				default:
					/* Turn D5 off	 */
					LATB    &=  ~D5; 

					/* Initialized the message	 */
					my_message[ 7 ]   =  'E';
					my_message[ 8 ]   =  'R';
					my_message[ 9 ]   =  'R';
					my_message[ 10 ]  =  'O';
					my_message[ 11 ]  =  'R';
					my_message[ 12 ]  =  '!';
                    my_message[ 13 ]  =  '\n';
					break;
			}
            
            /* Transmit data back	 */
			myPtr    =   &my_message[0];
            
            /* Reset variables	 */
			myState	 =	 0U;
            
            /* Enables the USART transmit interrupt	 */
			PIE1bits.TXIE = 1UL;
            
            /* Disables receiver and enable transmission    */
            RCSTAbits.CREN  =   0U;
            TXSTAbits.TXEN  =   1UL;
        }
        else
        {
            /* Do nothing   */
            // SLEEP();
        }
    }
}
