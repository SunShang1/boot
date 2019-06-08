/******************************************************************************
    Filename: uart.c

    This file defines uart related functions for the CC253x family
    of RF system-on-chips from Texas Instruments.

******************************************************************************/


/*******************************************************************************
 * INCLUDES
 */

#include "hal_uart.h"

/*******************************************************************************
 * TYPEDEF
 */


/*******************************************************************************
 * GLOBALE
 */
#if (ENABLE_UART0) || (ENABLE_UART1)
const static uint8_t baudRate[12][2] =
{
    {59, 6},    //2400
    {59, 7},
    {59, 8},    //9600
    {216, 8},
    {59, 9},    //19200
    {216, 9},
    {59, 10},
    {216, 10},  //57600
    {59, 11},
    {216, 11},  //115200
    {216, 12}   //230400
};
#endif

/*******************************************************************************
 * PUBLIC FUNCTIONS
 */
error_t halUartInit(uint8_t port, struct uartOpt_t *opt)
{
#if ENABLE_UART0
    if (port == 0)
    {
        MCU_IO_DIR_OUTPUT_PREP(0, 3);
        MCU_IO_PERIPHERAL_PREP(0, 3);
        
        MCU_IO_DIR_INPUT_PREP(0, 2);
        MCU_IO_PERIPHERAL_PREP(0, 2);
        
        PERCFG &= ~(1 << 0);
        
        if (opt->parity == 'E')
        {
            U0UCR = (1<<3);
        }
        else if (opt->parity == 'O')
        {
            U0UCR = (1<<5)|(1<<3);
        }
        else // if (opt->parity == 'N')
            U0UCR = 0x0;
        
        if (opt->dataBits == UART_DATA_BIT8)
        {
            U0UCR &= ~(1<<4);
        }
        else // if (opt->dataBits == UART_DATA_BIT9)
        {
            U0UCR |= (1<<4);
        }
        
        if (opt->stopBits == UART_STOP_BIT1)
        {
            U0UCR &= ~(1<<2);
        }
        else // if (opt->stopBits == UART_STOP_BIT2)
        {
            U0UCR |= (1<<2);
        }
        
        U0UCR |= (0x2<<0);
        
        U0GCR = baudRate[opt->baudRate][1];
        U0BAUD = baudRate[opt->baudRate][0];
        
        URX0IE = 0; //enable Rx interrupt
        U0CSR = (1<<7) | (1<<6); // UART mode, start rx
    }
#endif

    return EOK;
}

int halUartPutChar(uint8_t port, char ch)
{
#if ENABLE_UART0    
    if (port == 0)
    {
        U0CSR &= ~(1<<1);
    
        U0DBUF = ch;
            
        while(!(U0CSR&(1<<1)));
        U0CSR &= ~(1<<1);
        
        return EOK;
    }
#endif
     
    return - ERROR;
}
                 
int halUartGetChar(uint8_t port, char *ch)
{
    if (ch == NULL)
        return - ERROR;

#if ENABLE_UART0 
    if (port == 0)
    {
        if (URX0IF == 1)
        {
            // Read UART0 RX buffer.
            *ch = U0DBUF;
            URX0IF = 0;
            
            return EOK;
        }
        
        return - ERROR;
    }
#endif      
    
    return - ERROR;
}

