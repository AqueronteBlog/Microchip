/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/June/2019
 * @version     01/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "../inc/interrupts.h"


/**
 * @brief       void T1Interrupt ()
 * @details     Timer interruption. 
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        02/June/2019
 * @version     02/June/2019   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __attribute__ ( ( vector(_TIMER_1_VECTOR) , interrupt(IPL3SOFT) ) ) T1Interrupt ( void )
{
    /* Execute new action    */
    changeLEDstate   =   1UL;
    
    
    /* Clear the timer interrupt status flag ( T1IF )     */
    IFS0CLR  =   0x00020000;
}