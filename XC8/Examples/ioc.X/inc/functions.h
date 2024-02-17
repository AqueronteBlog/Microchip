/**
 * @brief       functions.h
 * @details     Functions header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        17/February/2024
 * @version     17/February/2024    The ORIGIN
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
void conf_CLK       ( void );
void conf_GPIO      ( void );
void conf_Timer2    ( void );
void conf_Timer4    ( void );
void conf_Timer6    ( void );

/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */