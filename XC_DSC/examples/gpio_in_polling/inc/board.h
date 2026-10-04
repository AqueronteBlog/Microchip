/**
 * @brief       board.h
 * @details     Board header.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        23/July/2026
 * @version     23/July/2026   The ORIGIN
 * @pre         dsPIC33A Curiosity Platform Development Board (EV74H48A) and dsPIC33AK128MC106 Curiosity GP DIM (EV02G02A)
 * @warning     N/A
 */
#ifndef BOARD_H_
#define BOARD_H_

#include "xc.h"
#include <stdio.h>
#include <stdlib.h>


#ifdef __cplusplus
extern "C" {
#endif


/**@brief LEDS.
 */
typedef enum{
    LED0    =   (1UL    <<  3UL),   /*!<    LED0: P28 -> RC3    */
    LED1    =   (1UL    <<  4UL),   /*!<    LED1: P30 -> RC4    */
    LED2    =   (1UL    <<  5UL),   /*!<    LED2: P32 -> RC5    */
    LED3    =   (1UL    <<  6UL),   /*!<    LED3: P34 -> RC6    */
    LED4    =   (1UL    <<  7UL),   /*!<    LED4: P36 -> RC7    */
    LED5    =   (1UL    <<  8UL),   /*!<    LED5: P50 -> RC8    */
    LED6    =   (1UL    <<  9UL),   /*!<    LED6: P52 -> RC9    */
    LED7    =   (1UL    <<  10UL)   /*!<    LED7: P54 -> RC10   */
} ev74h48a_ev02g02a_leds_t;


/**@brief SWITCHES.
 */
typedef enum{
    S1_MSK  =   (1UL    <<  5UL),   /*!<    S1 MASK:    P45 -> RB5    */
    S1      =   S1_MSK,             /*!<    S1:         P45 -> RB5    */
    S2_MSK  =   (1UL    <<  4UL),   /*!<    S2 MASK:    P43 -> RB4    */
    S2      =   S2_MSK,             /*!<    S2:         P43 -> RB4    */
    S3_MSK  =   (1UL    <<  6UL),   /*!<    S3 MASK:    P41 -> RA6    */
    S3      =   S3_MSK              /*!<    S3:         P41 -> RA6    */
} ev74h48a_ev02g02a_sw_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */