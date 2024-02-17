/**
 * @brief       main.c
 * @details     [todo]This example shows how to work with the internal peripheral: Interrupt-On-Change (IOC).
 * 
 *              Every time the switch S3 is pushed, D5 changes its state.
 * 
 *              The microcontroller is in SLEEP mode the rest of the time.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero (aqueronteblog@gmail.com)
 * @date        17/February/2024
 * @version     17/February/2024    The ORIGIN
 * @pre         This project was tested on a PIC16F1937 using a PICDEM 2 Plus.
 * @warning     N/A
 * @pre         This code belongs to AqueronteBlog. 
 *                  - GitHub:  https://github.com/AqueronteBlog
 *                  - YouTube: https://www.youtube.com/user/AqueronteBlog
 *                  - X:       https://twitter.com/aqueronteblog
 */

// PIC16F1937 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
//#pragma config DEBUG = ON       // In-Circuit Debugger Mode (In-Circuit Debugger enabled, ICSPCLK and ICSPDAT are dedicated to the debugger)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include "../inc/board.h"
#include "../inc/functions.h"
#include "../inc/interrupts.h"
#include "../../../../../Drivers/TC74/inc/TC74.h"

/**@brief Constants.
 */
#define I2C0_FREQUENCY   		100000U	/*!< I2C frequency */
#define I2C_MASTER_TIMEOUT_MS	500		/*!< I2C master communication timeout */
#define ACK_CHECK_EN        	0x01    /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS       	0x00    /*!< I2C master will not check ack from slave */
#define ACK_VAL             	0x00    /*!< I2C ack value */
#define NACK_VAL            	0x01    /*!< I2C nack value */

/**@brief Variables.
 */
volatile uint8_t myState;

/**@brief Function prototypes.
 */
/** I2C writing function.
  */
static i2c_status_t	i2c_write	( uint8_t dev_addr, uint8_t* i2c_buff, uint32_t length, i2c_stop_bit_t i2c_generate_stop );

/** I2C reading function.
  */
static i2c_status_t	i2c_read	( uint8_t dev_addr, uint8_t* i2c_buff, uint32_t length );


/**@brief Function for application main entry.
 */
void main(void) {
    TC74_data_t     myTC74_param = { 0 };	
	TC74_status_t   err = TC74_SUCCESS;
	
	/* Configure I2C for external peripheral: TC74	*/
	static TC74_i2c_comm_t myTC74_i2c = {
		.i2c.address	= TC74_A5,
		.i2c.read 		= i2c_read,
		.i2c.write 		= i2c_write
	};
    
    conf_CLK        ();
    conf_GPIO       ();
    conf_master_i2c ();
    
    /* Disable TC74  */
    myTC74_param.config.standby =   CONFIG_STANDBY_STANDBY;
    err =   TC74_SetConfig  ( &myTC74_i2c, myTC74_param.config.standby );
    
    /* Enable interrupts    */
    INTCONbits.IOCIE    =   1U; // Enable the interrupt-on-change
    INTCONbits.PEIE     =   0U; // Disable all active peripheral interrupts
    INTCONbits.GIE      =   1U; // Enable all active interrupts
       
    /* Reset the variables  */
    myState =   0U;
    
    while ( 1U )
    {
        /* Check if an interrupt is triggered by TMR2 or TMR6    */
        if ( myState != 0U )
        {
            /* D5 LED on    */
            LATB    |=  D5;
            
            /* TC74. Enabled  */
            myTC74_param.config.standby =   CONFIG_STANDBY_NORMAL;
            err =   TC74_SetConfig ( &myTC74_i2c, myTC74_param.config.standby );
            
            /* TC74. Wait until the data is ready */
            do{
                myTC74_param.config.data_ready  =   CONFIG_DATA_READY_NOT_READY;
                err =   TC74_GetConfig ( &myTC74_i2c, &myTC74_param.config );
            }while( myTC74_param.config.data_ready == CONFIG_DATA_READY_NOT_READY );
            
            /* TC74. Get temperature  */
            err =   TC74_GetTemperature ( &myTC74_i2c, &myTC74_param.raw_temperature );
            
            /* TC74. Disabled  */
            myTC74_param.config.standby =   CONFIG_STANDBY_STANDBY;
            err =   TC74_SetConfig  ( &myTC74_i2c, myTC74_param.config.standby );
            
            /* Reset the variable  */
            myState =   0U;
            
            /* D5 LED off    */
            LATB    &=  ~D5;
        }
        else
        {
            /* Sleep mode */
            SLEEP();
        }
    }
}



/**
 * @brief       i2c_status_t i2c_read ( uint8_t , uint8_t* , uint32_t )
 * @details     [todo]I2C read fucntion.
 *
 *
 * @param[in]    dev_addr: 	Device address.
 * @param[in]    length: 	How many bytes to be transmitted.
 *
 * @param[out]   i2c_buff:	Data output.
 *
 *
 * @return      Status of i2c_read
 *
 * @author      Manuel Caballero
 * @date        17/February/2024
 * @version     17/February/2024   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
static i2c_status_t i2c_read ( uint8_t dev_addr, uint8_t* i2c_buff, uint32_t length )
{
    
    
    if ( 1 )
	{
		return I2C_SUCCESS;
	}
	else
	{
		return I2C_FAILURE;
	}
}



/**
 * @brief       i2c_status_t i2c_write ( uint8_t , uint8_t* , uint32_t , i2c_stop_bit_t )
 * @details     [todo]I2C write function.
 *
 *
 * @param[in]    dev_addr: 			Device address.
 * @param[in]    length: 			How many bytes to be transmitted.
 * @param[in]    i2c_buff: 			Data input.
 * @param[in]    i2c_generate_stop:	Stop bit generation.
 *
 * @param[out]   N/A.
 *
 *
 * @return      Status of i2c_write
 *
 * @author      Manuel Caballero
 * @date        17/February/2024
 * @version     17/February/2024   The ORIGIN
 * @pre         N/A
 * @warning     N/A
 */
static i2c_status_t i2c_write ( uint8_t dev_addr, uint8_t* i2c_buff, uint32_t length, i2c_stop_bit_t i2c_generate_stop )
{
	


	if ( 1 )
	{
		return I2C_SUCCESS;
	}
	else
	{
		return I2C_FAILURE;
	}
}
