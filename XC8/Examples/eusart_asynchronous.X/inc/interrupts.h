/**
 * @brief       interrupts.h
 * @details     Interrupts header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Subroutine prototypes.
 */
void __interrupt() ISR ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* INTERRUPTS_H_ */