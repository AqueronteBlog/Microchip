/**
 * @brief       functions.h
 * @details     Functions header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        01/June/2019
 * @version     01/June/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include "board.h"
 

#ifndef FUNCTION_H_
#define FUNCTION_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Function prototypes.
 */
void conf_CLK    ( void );
void conf_PWRCON ( void );
void conf_GPIO   ( void );
void conf_TIMER1 ( void );

/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */