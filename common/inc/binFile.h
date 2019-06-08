/**
  ******************************************************************************
  * @file    binFile.h 
  * @author  George
  * @date    
  * @brief   header file for bin file
  ******************************************************************************
***/
#ifndef __BINFILE_H__
#define __BINFILE_H__

#include "pub_def.h"
#include "crc.h"

/********************************************
* Defines *
********************************************/



/********************************************
* Typedefs *
********************************************/
typedef struct
{
    uint16_t    icrc;
    uint16_t    isize;  /* unit: word */
} binHdr_t;


/********************************************
* Function defines *
********************************************/
int binFileValid(uint32_t addr);

void binFileCopy(const uint32_t addr1, const uint32_t addr2);

#endif
