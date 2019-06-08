/*
 * 文件名: binFile.c
 *
 * 文件说明：cc2530 bin file 校验
 *
 */

#include <string.h>
#include "layout.h"
#include "binFile.h"
#include "endian.h"

#include "hal_flash.h"
/********************************************
* Defines *
********************************************/

/********************************************
* Typedefs *
********************************************/


/********************************************
* Globals * 
********************************************/


/********************************************
* Function defines *
********************************************/
int binFileValid(uint32_t addr)
{
    binHdr_t            binHdr;
    uint8_t             buf[4];
    uint16_t            i;
    uint16_t            crc=0;
    
    HalFlashRead(&binHdr, addr, sizeof(binHdr_t));
    
    if ((binHdr.icrc == 0xFFFF) && (binHdr.isize == 0xFFFF))
        return FALSE;
    
    if (binHdr.isize > (CFG_IMG_SIZE - sizeof(binHdr))>>2)
        return FALSE;
    
    addr += sizeof(binHdr_t);
    for (i = 0; i < binHdr.isize; i ++)
    {
        HalFlashRead(buf, addr, 4);
        
        crc = crc16(crc, buf, 4);
        
        addr += 4;
    }
    
    if (crc == binHdr.icrc)
        return 0;
    else
        return -1;
}

void binFileCopy(const uint32_t addr1, const uint32_t addr2)
{
    binHdr_t            hdr; 
    uint8_t             buf[4];
    uint16_t            i;
    uint16_t            crc;
    uint32_t            u32Val;
    uint32_t            srcAddr = addr2;
    uint32_t            dstAddr = addr1;

BIN_FILE_COPY:

    HalFlashRead(&hdr, srcAddr, sizeof(binHdr_t));
    srcAddr += sizeof(binHdr_t);
    
    /* erase dstAddr area */
    for (u32Val=0; u32Val < hdr.isize*4; u32Val+=HAL_FLASH_PAGE_SIZE)
        HalFlashErase(u32Val + dstAddr);
    
    for (i = 0; i < hdr.isize; i ++)
    {
        HalFlashRead(buf, srcAddr, 4);
        HalFlashWrite(dstAddr, buf, 4);
        
        srcAddr += 4;
        dstAddr += 4;
    }
    
    crc = 0;
    dstAddr = addr1;
    for (i = 0; i < hdr.isize; i ++)
    {
        HalFlashRead(buf, dstAddr, 4);
        
        crc = crc16(crc, buf, 4);
        dstAddr += 4;
    }
    
    if (crc != hdr.icrc)
        goto BIN_FILE_COPY;

    return;
}

