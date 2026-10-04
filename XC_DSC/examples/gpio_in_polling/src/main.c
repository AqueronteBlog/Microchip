/**
 * @brief       main.c
 * @details     This project shows how to configure the internal peripheral: GPIO as a digital input pins (Switche pins).
 *              
 *              Switch S1 changes the state of LED0.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        04/October/2026
 * @version     04/October/2026    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 * @pre         N/A
 */
 #include "../inc/board.h"
#include "../inc/interrupts.h"
#include "../inc/functions.h"

int main(){
    conf_gpio ();

    while (1)
    {
        /* Change the state LED0 when S1 is pressed */
        if ((PORTB & S1_MSK)    ==  0UL)
        {
            while ((PORTB & S1_MSK)    ==  0UL);    // Debouncing - Wait until S1 is released
            LATC    ^=  LED0;   // Change LED0 state
        }
    }

    return 0;
}
