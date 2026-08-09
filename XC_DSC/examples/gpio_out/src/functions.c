/**
 * @brief       functions.c
 * @details     Functions sources.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        23/July/2026
 * @version     23/July/2026   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
 
 #include "../inc/functions.h"


 /**
 * @brief       void conf_gpio( void )
 * @details     It configures GPIOs.
 * 
 *              LEDs:
 *                  - LED0. RC3: GPIO Output pin, no pull-up
 *                  - LED1. RC4: GPIO Output pin, no pull-up
 *                  - LED2. RC5: GPIO Output pin, no pull-up
 *                  - LED3. RC6: GPIO Output pin, no pull-up
 *                  - LED4. RC7: GPIO Output pin, no pull-up
 *                  - LED5. RC8: GPIO Output pin, no pull-up
 *                  - LED6. RC9: GPIO Output pin, no pull-up
 *                  - LED7. RC10: GPIO Output pin, no pull-up
 * 
 * @param[in]    N/A.
 *
 * @param[out]   N/A.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        09/August/2026
 * @version     09/August/2026    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
 void conf_gpio ( void )
 {
    /* LED PINs as digital outputs  */
    TRISC   &=  ~( LED0 | LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 );

    /* LEDs are OFF */
    LATC    &=  ~( LED0 | LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 ); 
    
    /* LED pins. No pull-ups */
    CNPUC    &=  ~( LED0 | LED1 | LED2 | LED3 | LED4 | LED5 | LED6 | LED7 );
 }