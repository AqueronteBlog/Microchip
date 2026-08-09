/**
 * @brief       main.c
 * @details     This is just a template project.
 *
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

    // Add your code here and press Ctrl + Shift + B to build
    TRISCbits.TRISC3    =   0UL;
    while(1) {
        LATCbits.LATC3  =   0UL;
        for(i = 0UL; i < 0x232323; i++);
        LATCbits.LATC3  =   1UL;
        for(i = 0UL; i < 0x232323; i++);
    }

    return 0;
}
