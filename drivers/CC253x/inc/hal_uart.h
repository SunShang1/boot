/******************************************************************************
    Filename: uart.h

    This file defines interface for uart related functions for the
    CC253x family of RF system-on-chips from Texas Instruments.

******************************************************************************/
#ifndef __UART_H__
#define __UART_H__


/*******************************************************************************
 * INCLUDES
 */
#include "pub_def.h"
#include "hal_mcu.h"
#include "error.h"

 /*******************************************************************************
 * DEFINE
 */
#define ENABLE_UART0    1 
#define ENABLE_UART1    0 
   

/*******************************************************************************
 * TYPEDEF
 */
#define UART_BUF_SIZE   (1<<8)      //must be 2^n

/* uart tx mode define */
#define UART_DMA_TX         0
#define UART_INT_TX         1
#define UART_POLLING_TX     2

#define UART_TX_MODE        UART_POLLING_TX


struct uartInfo_t
{
#if (UART_TX_MODE != UART_POLLING_TX)
    /* Tx info */
    uint8_t     TxBuf[UART_BUF_SIZE];
    volatile uint16_t    TxBufWrite;
    volatile uint16_t    TxBufRead;
#endif
    
    /* Rx info */
    uint8_t     RxBuf[UART_BUF_SIZE];
    volatile uint16_t    RxBufWrite;
    volatile uint16_t    RxBufRead;
    volatile uint16_t    RxCnt;
    
    pInterruptHandler_t pRxCallBack;
};

struct uartOpt_t
{
    uint8_t     baudRate;   
    uint8_t     dataBits;       //����λ��ȡֵΪ7 ���� 8 
    uint8_t     stopBits;       //ֹͣλ��ȡֵΪ1 ���� 2
    uint8_t     parity;         //��żУ��λ��ȡֵΪ N,E,O
};

#define UART_DATA_BIT8      0
#define UART_DATA_BIT9      1

#define UART_STOP_BIT1      0
#define UART_STOP_BIT2      1

#define UART_BAUD_2400      0
#define UART_BAUD_4800      1
#define UART_BAUD_9600      2
#define UART_BAUD_14400     3
#define UART_BAUD_19200     4
#define UART_BAUD_28800     5
#define UART_BAUD_38400     6
#define UART_BAUD_57600     7
#define UART_BAUD_76800     8
#define UART_BAUD_115200    9
#define UART_BAUD_230400    10


error_t halUartInit(uint8_t port, struct uartOpt_t *opt);

int halUartPutChar(uint8_t port, char ch);
int halUartGetChar(uint8_t port, char *ch);


#endif