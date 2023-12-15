/**
 * @brief       board.h
 * @details     Board header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        15/December/2023
 * @version     15/December/2023    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#ifndef BOARD_H_
#define BOARD_H_

#include <xc.h>
#include <pic16f1937.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


/**@brief Function prototypes.
 */


/**@brief Constants.
 */
/**@brief LEDS.
 */
typedef enum{
  D2  = ( 1U << 0U ),      /*!<   LED1: RB0    */
  D3  = ( 1U << 1U ),      /*!<   LED2: RB1    */
  D4  = ( 1U << 2U ),      /*!<   LED3: RB2    */
  D5  = ( 1U << 3U )       /*!<   LED3: RB3    */
} picdem2_plus_leds_t;


/**@brief SWITCHES.
 */
typedef enum{
  S2_MSK    = ( 1U << 4U ),      /*!<   S2 mask    */
  S2        = ( 1U << 4U ),      /*!<   S2: RA4    */
  S3_MSK    = ( 1U << 0U ),      /*!<   S3 mask    */
  S3        = ( 1U << 0U )       /*!<   S3: RB0    */
} picdem2_plus_switches_t;



/**@brief Variables.
 */



#ifdef __cplusplus
}
#endif

#endif /* FUNCTIONS_H_ */