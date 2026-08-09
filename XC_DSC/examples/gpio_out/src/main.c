/**
 * @brief       main.c
 * @details     This project shows how to configure the internal peripheral: GPIO as a digital output port (LED pins).
 *              
 *              LED0-LED7 blinks for a certain amount of time.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        23/July/2026
 * @version     23/July/2026    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         N/A
 */

#include "../inc/board.h"
#include "../inc/interrupts.h"
#include "../inc/functions.h"

int main(){
    uint32_t    i   =   0UL;

    conf_gpio ();

    while ( 1 )
    {
        /* LEDs are OFF */
        LATC    &=  ~( LED0 | LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 );
        for ( i = 0UL; i < 0x232323; i++ );

        /* LEDs are ON */
        LATC    |=  ( LED0 | LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 );
        for ( i = 0UL; i < 0x232323; i++ );
    }

    return 0;
}
