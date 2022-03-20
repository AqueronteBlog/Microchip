/**
 * @brief       spi.c
 * @details     NRF52 SPI function libraries.
 *              Function file.
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        26/April/2019
 * @version     26/April/2019    The ORIGIN
 * @pre         N/A
 * @warning     This file is ONLY for NRF52 device.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ).
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
 * @date        26/April/2019
 * @version     26/April/2019   The ORIGIN
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
 * @date        26/April/2019
 * @version     26/April/2019      The ORIGIN
 * @pre         N/A.
 * @warning     N/A.
 */
spi_status_t    spi_init     ( spi_parameters_t mySPIparameters )
{
    uint8_t mySPI_CPOL          =   0;
    uint8_t mySPI_CPHA          =   0;
    uint8_t mySPI_ByteOrder     =   0;

    


    return SPI_SUCCESS;
}
