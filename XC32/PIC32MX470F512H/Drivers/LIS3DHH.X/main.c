/**
 * @brief       main.c
 * @details     [TODO]This project shows how to work with the internal peripherals UART at 115200 baud rate. 
 *              The LEDs will change if the user sends through the UART the following code:
 *                  1 --> LED1 changes its status.
 *                  2 --> LED2 changes its status.
 *                  3 --> LED3 changes its status.
 *                  Other --> All lEDs are off
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        27/February/2022
 * @version     27/February/2022    The ORIGIN
 * @pre         This firmware was tested on the PIC32MX470 Curiosity Development Board with MPLAB X IDE v5.50.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - Twitter: https://twitter.com/aqueronteblog
 */

#include <stdio.h>
#include <stdlib.h>
#include "inc/board.h"
#include "inc/variables.h"
#include "inc/functions.h"
#include "inc/interrupts.h"


/**@brief Constants.
 */
#define TX_BUFF_SIZE    64                    /*!<   UART buffer size                                       */

#define SYSCLK          8000000
#define PBCLK           SYSCLK

#define UART1_BAUDRATE  115200


/**@brief Variables.
 */
volatile uint32_t  myState	 =	 0U;		/*!<   State that indicates when to perform the next action   */
volatile uint8_t  *myPtr;                   /*!<   Pointer to point out myMessage                         */


/**@brief Function for application main entry.
 */
void main ( void ) 
{
    uint8_t  myMessage[ TX_BUFF_SIZE ];
    
    /* Initialized the message	 */
	myMessage[ 0 ]   =  'L';
	myMessage[ 1 ]   =  'E';
	myMessage[ 2 ]   =  'D';
	myMessage[ 3 ]   =  ' ';
	myMessage[ 4 ]   =  ' ';
	myMessage[ 11 ]  =  '\n';
    
    
    /* Configure the peripherals*/
    conf_CLK    ();
    conf_GPIO   ();
    conf_UART1  ( PBCLK, UART1_BAUDRATE );    
    
     /* All interrupts are enabled     */
    __builtin_enable_interrupts();
    
    while ( 1 )
    {
        /* Perform a dummy instruction before WAIT instruction*/
        asm volatile ( "NOP" );
        
        /* uC in low power mode: Idle Mode     */
        asm volatile ( "WAIT" );
        
        if ( myState != 0U )
		{
			/* Initialized the message	 */
			myMessage[ 5 ]   =  'T';
			myMessage[ 6 ]   =  'O';
			myMessage[ 7 ]   =  'G';
			myMessage[ 8 ]   =  'G';
			myMessage[ 9 ]   =  'L';
			myMessage[ 10 ]  =  'E';

			switch ( myState )
			{
				case '1':
					/* Toggle LED1	 */
					PORTEINV   = LED1;
					myMessage [ 3 ]	 =	 '1';
					break;

				case '2':
					/* Toggle LED2	 */
					PORTEINV   = LED2;
					myMessage [ 3 ]	 =   '2';
					break;

				case '3':
					/* Toggle LED3	 */
					PORTEINV   = LED3;
					myMessage [ 3 ]	 =   '3';
					break;

				default:
					/* All LEDs off	 */
					PORTECLR   |=   ( LED1 | LED2 | LED3 );  

					/* Initialized the message	 */
					myMessage[ 3 ]   =  ' ';
					myMessage[ 5 ]   =  'E';
					myMessage[ 6 ]   =  'R';
					myMessage[ 7 ]   =  'R';
					myMessage[ 8 ]   =  'O';
					myMessage[ 9 ]   =  'R';
					myMessage[ 10 ]  =  '!';
					break;
			}
            
            /* Transmit data back	 */
			myPtr    =   &myMessage[0];
			U1TXREG	 =	 *myPtr;

			/* Transmit Buffer Empty Interrupt: Enabled	 */
			U1STAbits.UTXEN = 1UL;

			/* Reset variables	 */
			myState	 =	 0U;
        }
    }
}
