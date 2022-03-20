/**
 * @brief       spi.c
 * @details     PIC32MX470 SPI function libraries.
 *              Functions file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        20/May/2022
 * @version     20/May/2022    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for PIC32MX470 device.
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - Twitter: https://twitter.com/aqueronteblog
 */

#include "spi.h"


/**
 * @brief       spi_transfer   ( spi_parameters_t , uint8_t* , uint32_t , uint8_t* , uint32_t )
 *
 * @details     Send/Receive data through the SPI bus.
 *
 * @param[in]    mySPI_parameters:      SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 * @param[in]    spi_tx_buff:           Data to be transmitted through SPI bus.
 * @param[in]    spi_tx_length:         Amount of data to be transmitted through SPI bus.
 * @param[in]    spi_rx_length:         Amount of data to be read through SPI bus.
 *
 * @param[out]   spi_rx_buff:           Data from the SPI bus.
 *
 *
 * @return      Status of spi_transfer
 *
 *
 * @author      Manuel Caballero
 * @date        20/May/2022
 * @version     20/May/2022   The ORIGIN
 * @pre         SPI communication is by polling mode.
 * @warning     N/A.
 */
spi_status_t    spi_transfer ( spi_parameters_t mySPIparameters, uint8_t* spi_tx_buff, uint32_t spi_tx_length, uint8_t* spi_rx_buff, uint32_t spi_rx_length )
{
    uint32_t     i                   =   0;
    uint32_t     spi_timeout1        =   232323;
    uint32_t     spi_timeout2        =   232323;


    /* Check if everything went fine */
    if ( ( spi_timeout1 < 1 ) || ( spi_timeout2 < 1 ) )
        return SPI_FAILURE;
    else
        return SPI_SUCCESS;
}



/**
 * @brief       spi_init     ( spi_parameters_t )
 *
 * @details     It configures the SPI peripheral.
 *
 * @param[in]    mySPI_parameters:  SPI instance, MOSI pin, MISO pin, SCLK pin, CS pin, SPI frequency and the port for each pin.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of spi_init
 *
 *
 * @author      Manuel Caballero
 * @date        20/May/2022
 * @version     20/May/2022      The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
spi_status_t    spi_init     ( spi_parameters_t mySPIparameters )
{
    uint8_t mySPI_ByteOrder     =   0;
    
    /* SPI1 Disabled     */
    SPI1CONbits.ON  =   0UL;
    
    /* Framed SPI support is enabled    */
    SPI1CONbits.FRMEN   =   1UL;
    
    /* Frame sync pulse output (Master mode)    */
    SPI1CONbits.FRMSYNC   =   0UL;
    
    /* Frame Sync Polarity bit    */
    if ( mySPIparameters.SPIenable_line_mode == SPI_ENABLE_LINE_HIGH )
    {
        SPI1CONbits.FRMPOL   =   1UL;
    }
    else
    {
        SPI1CONbits.FRMPOL   =   0UL;
    }
    
    /* Slave select SPI support enabled    */
    SPI1CONbits.MSSEN   =   1UL;
    
    /* Frame sync pulse is one clock wide    */
    SPI1CONbits.FRMSYPW   =   0UL;
    
    /* Generate a frame sync pulse on every data character    */
    SPI1CONbits.FRMCNT   =   0b000;
    
    /* PBCLK is used by the Baud Rate Generator    */
    SPI1CONbits.MCLKSEL   =   0UL;
    
    /* Continue operation in Idle mode    */
    SPI1CONbits.SIDL   =   0UL;
    
    /* SDO1 pin is controlled by the module    */
    SPI1CONbits.DISSDO   =   0UL;
    
    /* 8-bit Communication    */
    SPI1CONbits.MODE32   =   0UL;
    SPI1CONbits.MODE16   =   0UL;
    
    /* Input data sampled at middle of data output time    */
    SPI1CONbits.SMP   =   0UL;
    
    /* SPI mode: CPOL and CPHA     */
    switch( mySPIparameters.SPImode )
    {
        default:
        case SPI_MODE_0:
            SPI1CONbits.CKE   =   1UL;
            SPI1CONbits.CKP   =   0UL;
            break;
            
        case SPI_MODE_1:
            SPI1CONbits.CKE   =   0UL;
            SPI1CONbits.CKP   =   0UL;
            break;
            
        case SPI_MODE_2:
            SPI1CONbits.CKE   =   1UL;
            SPI1CONbits.CKP   =   1UL;
            break;
            
        case SPI_MODE_3:
            SPI1CONbits.CKE   =   0UL;
            SPI1CONbits.CKP   =   1UL;
            break;
    }
    
    /* Master mode    */
    SPI1CONbits.MSTEN   =   1UL;
    
    /* SDI pin is controlled by the SPI module    */
    SPI1CONbits.DISSDI   =   0UL;
    
    /* Interrupt is generated when the last transfer is shifted out of SPISR and transmit operations are complete   */
    SPI1CONbits.STXISEL   =   0b00;
    
    /* Interrupt is generated when the buffer is not empty   */
    SPI1CONbits.SRXISEL   =   0b01;

    
    
    
    return SPI_SUCCESS;
}
