/**
 * @brief       functions.h
 * @details     Functions header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        09/February/2024
 * @version     09/February/2024    The ORIGIN
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
void conf_adc       ( void );
void conf_eusart    ( void );


/**@brief Constants.
 */



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */