/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): PIC32MX470 Development Board.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        12/January/2022
 * @version     12/January/2022   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
#include <xc.h>


#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

    
/**@brief LEDs.
 */
typedef enum{
  LED1  = ( 1UL << 4UL ),      /*!<   LED1: RE4    */
  LED2  = ( 1UL << 6UL ),      /*!<   LED2: RE6    */
  LED3  = ( 1UL << 7UL )       /*!<   LED3: RE7    */
} PIC32MX_Curiosity_leds_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */