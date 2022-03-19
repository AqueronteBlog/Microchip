/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        27/February/2022
 * @version     27/February/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#include "board.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */



/**@brief Constants.
 */



/**@brief Variables.
 */
extern volatile uint32_t myState;
extern volatile uint8_t  *myPtr;

#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */