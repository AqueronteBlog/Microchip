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
 *              Switches:
 *                  - S1. RB5: GPIO digital input pin, no pull-up
 *                  - S2. RB4: GPIO digital input pin, no pull-up
 *                  - S3. RA6: GPIO digital input pin, no pull-up
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
 * @version     04/October/2026   Switches added
 *              09/August/2026    The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
void conf_gpio (void)
{
    /* LED pins as digital outputs  */
    TRISC   &=  ~(LED0 | LED1| LED2 | LED3 | LED4 | LED5 | LED6 | LED7);

    /* LED pin. No pull-ups */
    CNPUC   &=  ~(LED0 | LED1| LED2 | LED3 | LED4 | LED5 | LED6 | LED7);

    /* LEDs OFF*/
    LATC    &=  ~(LED0 | LED1| LED2 | LED3 | LED4 | LED5 | LED6 | LED7);

    /* Switch pins as digital pins  */
    ANSELB  &=  ~(S1 | S2);
    ANSELA  &=  ~S3;

    TRISB   |=  (S1 | S2);
    TRISA   |=  S3;

    /* Switch pins. No pull-ups */
    CNPUB   &=  ~(S1 | S2);
    CNPUA   &=  ~S3;

    /* Polling mode. Disable interrupts */
    CNEN0B  &=  ~(S1 | S2);
    CNEN0A  &=  ~S3;
}