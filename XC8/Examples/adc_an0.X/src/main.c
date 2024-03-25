/**
 * @brief       main.c
 * @details     This example shows how to work with the internal peripheral: ADC channel AN0 enabled.
 * 
 *              The code is led by a state machine.
 *              
 *                  - SM_SLEEP:                 It waits until the ADC completes a new measurement.
 *                  - SM_WAIT_TIMER:            It indicates when a new ADC measurement is needed [default].
 *                  - SM_NEW_ADC_AN0:           It makes the ADC start a new measurement.
 *                  - SM_SEND_DATA_OVER_UART:   It sends the ADC measurement over the UART.
 *                  - SM_WAIT_DATA_TRANSMITTED: It waits until the ADC measurement is sent over the UART.
 *              
 *              Every ~0.26s, a new value on AN0 pin will be transmitted over the UART. The SLEEP mode is only
 *              used to wait for the ADC module to complete a new measurement.  
 * 
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        14/March/2024
 * @version     14/March/2024    The ORIGIN
 * @pre         This project was tested on a PIC16F1937 using a PICDEM 2 Plus.
 * @pre         In asynchronous mode, the SLEEP mode cannot be used due to EUSART clock source (F_OSC).
 * @pre         The SLEEP mode cannot be used for the Timer2 due to Timer2/4/6 clock source (F_OSC).
 * @warning     [Errata] The ADC doesn't seem to wake the uC up after an ADC conversion.
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
#define EUSART_BUFF 16U

#define ADC_VDD_REF 5.0               /*!<   ADC VDD = 5V    */  
#define ADC_RES     ( 1024.0 - 1.0 )  /*!<   ADC 10-bit resolution    */  

typedef enum{
  SM_SLEEP                 = 0U,      /*!<   Sleep mode    */
  SM_WAIT_TIMER            = 1U,      /*!<   Wait until timer overlows for new ADC measurement    */
  SM_NEW_ADC_AN0           = 2U,      /*!<   New ADC measurement    */
  SM_SEND_DATA_OVER_UART   = 3U,      /*!<   Send data over the UART    */
  SM_WAIT_DATA_TRANSMITTED = 4U       /*!<   Wait until data is sent over the UART    */
} my_sm_t;

/**@brief Variables.
 */
my_sm_t             myState;        /* State that indicates when to perform the next action */
volatile uint8_t    *myPtr;         /* Pointer to point out myMessage   */
volatile uint8_t    myFlag;         /* Flag that indicates either if the Timer overflows (0b11), the ADC measurement is transmitted over the UART (0b01) or ADC finishes the current measurement conversion (0b10) */
volatile uint16_t   myADCresult;    /* ADC result */

/**@brief Function for application main entry.
 */
void main(void) {
    uint8_t my_message[EUSART_BUFF] = {0};
    
    conf_clk    ();
    conf_gpio   ();
    conf_adc    ();
    conf_eusart ();
    conf_Timer2 ();
       
    /* Enable interrupts    */
    INTCONbits.PEIE =   1U; // Enables all active peripheral interrupts
    INTCONbits.GIE  =   1U; // Enables all active interrupts
    
    /* Start timer */
    T2CONbits.TMR2ON   =  1U;
    
    /* Reset variables  */
    myState =   SM_WAIT_TIMER;
    myFlag  =   0U;
    
    while ( 1U )
    {
        /* State machine    */
        switch ( myState )
		{
            default:
            case SM_WAIT_TIMER:
                if ( myFlag == 0b11 )
                {
                    /* Stop timer */
                    T2CONbits.TMR2ON   =  0U;
    
                    /* Reset flag   */
                    myFlag  =   0U;
                    
                    /* Next state   */
                    myState =  SM_NEW_ADC_AN0; 
                }
                else
                {
                    /* Do nothing   */
                }
                break;
                
            case SM_NEW_ADC_AN0:
                LATB    |=  D5;
                
                /* Reset variable to store the ADC value    */
                myADCresult =   0U;
                
                /* ADC enabled and start a new ADC sampling   */
                ADCON0bits.ADON     =   1U;
                ADCON0bits.GO_nDONE =   1U;
                
                /* Next state   */
                myState =  SM_SLEEP; 
                break;
                
            case SM_SEND_DATA_OVER_UART:
                /* D5 LED on    */
                LATB    |=  D5;
                
                /* Pack the message. Turn ADC data into voltage data  */
                sprintf ((char*)my_message, "V = %0.2f V\r\n", (float)( ( ADC_VDD_REF * myADCresult ) / ADC_RES ));
                
                /* Transmit data  */
                myPtr    =   &my_message[0];
            
                /* Reset variables	 */
                myState	 =	 0U;
            
                /* Enables the USART transmit interrupt	 */
                PIE1bits.TXIE = 1UL;
            
                /* Enable transmission    */
                TXSTAbits.TXEN  =   1UL;
                
                /* Next state   */
                myState =  SM_WAIT_DATA_TRANSMITTED; 
                break;
                
            case SM_WAIT_DATA_TRANSMITTED:
                if ( myFlag ==   0b01 )
                {
                    /* D5 LED off    */
                    LATB    &=  ~D5;
                
                    /* Reset flag   */
                    myFlag  =   0U;
                    
                    /* Start timer */
                    T2CONbits.TMR2ON   =  1U;
                    
                    /* Next state   */
                    myState =  SM_WAIT_TIMER; 
                }
                else
                {
                    /* Do nothing   */
                }
                break;    
            
            case SM_SLEEP:
                //SLEEP();
                
                if ( myFlag ==   0b10 )
                {
                    /* Reset flag   */
                    myFlag  =   0U;
                    
                    /* Next state   */
                    myState =  SM_SEND_DATA_OVER_UART; 
                }
                break;                
        }
    }
}
