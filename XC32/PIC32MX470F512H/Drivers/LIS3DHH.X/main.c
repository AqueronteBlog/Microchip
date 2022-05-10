/**
 * @brief       main.c
 * @details     [TODO]This project shows how to work with the internal peripherals UART at 115200 baud rate. 
 *              The LEDs will change if the user sends through the UART the following code:
 *                  1 --> LED1 changes its status.
 *                  2 --> LED2 changes its status.
 *                  3 --> LED3 changes its status.
 *                  Other --> All lEDs are off
 *
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        19/March/2022
 * @version     19/March/2022    The ORIGIN
 * @pre         This firmware was tested on the PIC32MX470 Curiosity Development Board with MPLAB X IDE v5.50.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - Twitter: https://twitter.com/aqueronteblog
 */

#include <stdio.h>
#include <stdlib.h>
#include "inc/board.h"
#include "inc/variables.h"
#include "inc/functions.h"
#include "inc/interrupts.h"
#include "D:\Workspaces\Personal\Drivers\LIS3DHH\LIS3DHH.h"

/**@brief Constants.
 */
#define TX_BUFF_SIZE    64                    /*!<   UART buffer size                                       */

#define SYSCLK          8000000
#define PBCLK           SYSCLK

#define UART1_BAUDRATE  115200


/**@brief Variables.
 */
volatile uint32_t  myState	 =	 0U;		/*!<   State that indicates when to perform the next action   */
volatile uint8_t  *myPtr;                   /*!<   Pointer to point out myMessage                         */


/**@brief Function for application main entry.
 */
void main ( void ) 
{
    uint8_t  myMessage[ TX_BUFF_SIZE ];
    spi_parameters_t     myLIS3DHH_SPI_parameters;
	LIS3DHH_user_data_t  myLIS3DHH_Data;
	LIS3DHH_status_t     aux;
        
    
    /* Configure the peripherals*/
    conf_CLK    ();
    conf_GPIO   ();
    conf_UART1  ( PBCLK, UART1_BAUDRATE );    
    
    
    /* SPI definition   */
	myLIS3DHH_SPI_parameters.mosi         	 		 =   SPI1_MOSI;
	myLIS3DHH_SPI_parameters.miso         	 		 =   SPI1_MISO;
	myLIS3DHH_SPI_parameters.sclk         	 		 =   SPI1_CLK;
	myLIS3DHH_SPI_parameters.cs         	 		 =   SPI1_CS1;
	myLIS3DHH_SPI_parameters.spi_mode		 		 =	 SPI_MODE_0;
	myLIS3DHH_SPI_parameters.spi_enable_line_mode	 =	 SPI_ENABLE_LINE_LOW;
	myLIS3DHH_SPI_parameters.spi_freq        	 	 =   1000000;
    myLIS3DHH_SPI_parameters.freq_sck                =	 6400000;
    
    /* Configure I2C peripheral */
	aux  =   LIS3DHH_Init ( myLIS3DHH_SPI_parameters );

	/* Get device ID */
	aux  =   LIS3DHH_GetDeviceIdentification	( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.who_am_i );

	/* Reset the device, wait until the device resets */
	aux  =   LIS3DHH_SoftwareReset ( myLIS3DHH_SPI_parameters );
	do{
		LIS3DHH_GetSoftwareResetStatus ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.sw_reset );
	}while( myLIS3DHH_Data.sw_reset == CTRL_REG1_SW_RESET_RESET_DEVICE );

	/* Set register address auto incremented */
	myLIS3DHH_Data.if_add_inc	=	 CTRL_REG1_IF_ADD_INC_ENABLED;
	aux  =   LIS3DHH_SetRegisterAutoIncrement ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.if_add_inc );

	/* Set block data update: Continuous */
	myLIS3DHH_Data.bdu	=	 CTRL_REG1_BDU_CONTINUOUS_UPDATE;
	aux  =   LIS3DHH_SetBlockDataUpdate	( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.bdu );

	/* Set Digital filtering selection: FIR Linear Phase */
	myLIS3DHH_Data.dsp_lp_type	 =	 CTRL_REG4_DSP_LP_TYPE_FIR_LINEAR_PHASE;
	aux  =   LIS3DHH_SetDigitalFilter ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.dsp_lp_type );

	/* Set User-selectable bandwidth: 440Hz */
	myLIS3DHH_Data.dsp_bw_sel	 =	 CTRL_REG4_DSP_BW_SEL_440_HZ_TYP;
	aux  =   LIS3DHH_SetUserBandwidth ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.dsp_bw_sel );

	/* Set Self-test enable: Self-test disabled ( Normal mode ) */
	myLIS3DHH_Data.st	 =	 CTRL_REG4_ST_NORMAL_MODE;
	aux  =   LIS3DHH_SetSelfTest ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.st );

	/* Push-pull/open drain selection on INT2 pin: push-pull mode */
	myLIS3DHH_Data.pp_od_int2	 =	 CTRL_REG4_PP_OD_INT2_PUSH_PULL_MODE;
	aux  =   LIS3DHH_SetINT2_PinMode ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.pp_od_int2 );

	/* Push-pull/open drain selection on INT1 pin: push-pull mode */
	myLIS3DHH_Data.pp_od_int1	 =	 CTRL_REG4_PP_OD_INT1_PUSH_PULL_MODE;
	aux  =   LIS3DHH_SetINT1_PinMode ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.pp_od_int1 );

	/* FIFO memory enable: disabled */
	myLIS3DHH_Data.fifo_en	 =	 CTRL_REG4_FIFO_EN_DISABLED;
	aux  =   LIS3DHH_SetFIFO_MemoryEnable ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.fifo_en );

	/* Disables the SPI high speed configuration for the FIFO block */
	myLIS3DHH_Data.fifo_spi_hs_on	 =	 CTRL_REG5_FIFO_SPI_HS_ON_DISABLED;
	aux  =   LIS3DHH_SetFIFO_SPI_HighSpeed ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.fifo_spi_hs_on );

	/* Bypass mode. FIFO turned off, FIFO threshold level setting = 0 */
	myLIS3DHH_Data.fifo.fmode	 =	 FIFO_CTRL_FMODE_FIFO_OFF;
	myLIS3DHH_Data.fifo.fth		 =	 0U;
	aux  =   LIS3DHH_SetFIFO_Control ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.fifo );

	/* Power mode: Normal mode */
	myLIS3DHH_Data.norm_mod_en	 =	 CTRL_REG1_NORM_MOD_EN_ENABLED;
	aux  =   LIS3DHH_SetPowerMode ( myLIS3DHH_SPI_parameters, myLIS3DHH_Data.norm_mod_en );
    
     /* All interrupts are enabled     */
    __builtin_enable_interrupts();
    
    while ( 1 )
    {
        /* Perform a dummy instruction before WAIT instruction*/
        asm volatile ( "NOP" );
        
        /* uC in low power mode: Idle Mode     */
        asm volatile ( "WAIT" );
        
        if ( myState != 0U )
		{
            /* Wait until new data is available	 */
			do
			{
				aux	 =	 LIS3DHH_GetStatusRegister ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.status );
			}while( ( myLIS3DHH_Data.status & STATUS_ZYXDA_MASK ) != STATUS_ZYXDA_NEW_DATA );   			// [TODO] Dangerous!!! The uC may get stuck here if something goes wrong!
			                                                                                                // [WORKAROUND] Insert a counter.

			/* Read the new acceleration data, X-axis, Y-axis and Z-axis */
			aux  =   LIS3DHH_GetAccelerationData ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.acc );

			/* Read the new temperature value */
			aux  =   LIS3DHH_GetRawTemperature ( myLIS3DHH_SPI_parameters, &myLIS3DHH_Data.out_temp );


			/* Transmit data through the UART	 */
			sprintf ( (char*)myMessage, "X: %0.3f mG | Y: %0.3f mG | Z: %0.3f mG |T: %0.2f C\r\n", myLIS3DHH_Data.acc.acc.out_x, myLIS3DHH_Data.acc.acc.out_y, myLIS3DHH_Data.acc.acc.out_z, myLIS3DHH_Data.out_temp.temperature );
			
            
            /* Transmit data back	 */
			myPtr    =   &myMessage[0];
			U1TXREG	 =	 *myPtr;

			/* Transmit Buffer Empty Interrupt: Enabled	 */
			U1STAbits.UTXEN = 1UL;
            
			/* Reset variables	 */
			myState	 =	 0U;
        }
    }
}
