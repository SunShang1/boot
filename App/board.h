/*
 *
 * 文件名称：board.h
 *
 * 文件说明：CC2530 硬件板接口定义头文件
 * 
 *
 */  


#ifndef   BOARD_H
#define   BOARD_H

#include "pub_def.h"
#include "layout.h"
#include "hal_mcu.h"
#include "hal_uart.h"
#include "hal_flash.h"



/********************************************
* Defines *
********************************************/ 




/********************************************
* Typedefs *
********************************************/




/********************************************
* Function *
********************************************/
void halBoardInit(void);

#endif