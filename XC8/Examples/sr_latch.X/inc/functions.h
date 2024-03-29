/**
 * @brief       functions.h
 * @details     Functions header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        27/March/2024
 * @version     27/March/2024    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Function prototypes.
 */
void conf_clk       ( void );
void conf_gpio      ( void );
void conf_Timer4    ( void );
void conf_sr_latch  ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */