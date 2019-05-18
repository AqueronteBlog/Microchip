/**
 * @brief       main.c
 * @details     [TODO] This project shows how to work with the internal peripherals GPIO and Timer0.
 *              An interrupt will be generated every 0.5s by the TIMER0, the state of all the LEDs
 *              will be changed then.
 *
 *              The microcontroller remains in low power the rest of the time.
 *
 * @return      N/A
 *
 * @author      Manuel Caballero
 * @date        18/May/2019
 * @version     18/May/2019    The ORIGIN
 * @pre         This firmware was tested on the PIC32MM USB Curiosity Development Board with MPLAB X IDE v5.20.
 * @warning     N/A.
 * @pre         This code belongs to AqueronteBlog ( http://unbarquero.blogspot.com ). All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>


/**@brief Constants.
 */


// PIC32MM0256GPM064 Configuration Bit Settings

// 'C' source line config statements

// FDEVOPT
#pragma config SOSCHP = OFF             // Secondary Oscillator High Power Enable bit (SOSC oprerates in normal power mode.)
#pragma config ALTI2C = OFF             // Alternate I2C1 Pins Location Enable bit (Primary I2C1 pins are used)
#pragma config FUSBIDIO = OFF           // USBID pin control (USBID pin is controlled by the USB module)
#pragma config FVBUSIO = OFF            // VBUS Pin Control (VBUS pin is controlled by the USB module)
#pragma config USERID = 0xFFFF          // User ID bits (Enter Hexadecimal value)

// FICD
#pragma config JTAGEN = ON              // JTAG Enable bit (JTAG is enabled)
#pragma config ICS = PGx2               // ICE/ICD Communication Channel Selection bits (Communicate on PGEC2/PGED2)

// FPOR
#pragma config BOREN = BOR3             // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware; SBOREN bit disabled)
#pragma config RETVR = OFF              // Retention Voltage Regulator Enable bit (Retention regulator is disabled)
#pragma config LPBOREN = ON             // Downside Voltage Protection Enable bit (Low power BOR is enabled, when main BOR is disabled)

// FWDT
#pragma config SWDTPS = PS1048576       // Sleep Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config FWDTWINSZ = PS25_0       // Watchdog Timer Window Size bits (Watchdog timer window size is 25%)
#pragma config WINDIS = OFF             // Windowed Watchdog Timer Disable bit (Watchdog timer is in non-window mode)
#pragma config RWDTPS = PS1048576       // Run Mode Watchdog Timer Postscale Selection bits (1:1048576)
#pragma config RCLKSEL = LPRC           // Run Mode Watchdog Timer Clock Source Selection bits (Clock source is LPRC (same as for sleep mode))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable bit (WDT is disabled)

// FOSCSEL
#pragma config FNOSC = LPRC             // Oscillator Selection bits (Low power RC oscillator (LPRC))
#pragma config PLLSRC = FRC             // System PLL Input Clock Selection bit (FRC oscillator is selected as PLL reference input on device reset)
#pragma config SOSCEN = ON              // Secondary Oscillator Enable bit (Secondary oscillator is enabled)
#pragma config IESO = ON                // Two Speed Startup Enable bit (Two speed startup is enabled)
#pragma config POSCMOD = OFF            // Primary Oscillator Selection bit (Primary oscillator is disabled)
#pragma config OSCIOFNC = OFF           // System Clock on CLKO Pin Enable bit (OSCO pin operates as a normal I/O)
#pragma config SOSCSEL = OFF            // Secondary Oscillator External Clock Enable bit (SOSC pins configured for Crystal mode)
#pragma config FCKSM = CSECME           // Clock Switching and Fail-Safe Clock Monitor Enable bits (Clock switching is enabled; Fail-safe clock monitor is enabled)

// FSEC
#pragma config CP = OFF                 // Code Protection Enable bit (Code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>




/**@brief Variables.
 */



/**@brief Function for application main entry.
 */
void main ( void ) 
{
    uint32_t    i   =   0UL;
    
    TRISDbits.TRISD3     =   0;
    
    while ( 1 )
    {
        LATDbits.LATD3   =   1;
        for ( i = 0UL; i < 0x2323; i++ );
        LATDbits.LATD3   =   0;
        for ( i = 0UL; i < 0x2323; i++ );
    }
}

