/**
 * @brief       interrupts.c
 * @details     Interruption sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/January/2022
 * @version     12/January/2022   The ORIGIN
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
 * @date        08/December/2021
 * @version     08/December/2021   The ORIGIN
 * @pre         N/A.
 * @warning     N/A
 */
void __attribute__ ( ( vector(_TIMER_1_VECTOR), interrupt(IPL3SOFT) ) ) T1Handler ( void )
{
    /* Execute new action    */
    changeLEDstate   =   1UL;
    
    
    /* Clear the Timer1 interrupt status flag ( T1IF )     */
    IFS0CLR  =   0x00000010;
}