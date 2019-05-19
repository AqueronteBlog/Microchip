/**
 * @brief       board.h
 * @details     It characterizes the board ( for this example ): PIC32MM USB Development Board.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        19/May/2019
 * @version     19/May/2019   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */

#ifndef BOARD_H_
#define BOARD_H_

#ifdef __cplusplus
extern "C" {
#endif

/**@brief LEDs.
 */
typedef enum{
  LED1              = ( 1UL << 3UL ),   /*!<   LED1: RD3   */
  LED2              = ( 1UL << 13UL ),  /*!<   LED2: RC13  */
  LED3_RGB_RED      = ( 1UL << 1UL ),   /*!<   LED3: RD1   */
  LED3_RGB_GREEN    = ( 1UL << 3UL ),   /*!<   LED3: RC3   */
  LED3_RGB_BLUE     = ( 1UL << 15UL )   /*!<   LED3: RC15  */
} PIC32MM_USB_Curiosity_leds_t;



#ifdef __cplusplus
}
#endif

#endif /* BOARD_H_ */