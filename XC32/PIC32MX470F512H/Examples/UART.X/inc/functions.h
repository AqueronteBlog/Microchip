/**
 * @brief       functions.h
 * @details     Functions header.
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
 

#ifndef FUNCTION_H_
#define FUNCTION_H_

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Function prototypes.
 */
void conf_CLK   ( void );
void conf_GPIO  ( void );
void conf_UART1 ( uint32_t f_pb, uint32_t baudrate );

/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTION_H_ */