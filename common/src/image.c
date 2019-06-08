/*
 * 文件名: image.c
 *
 * 文件说明：image 文件校验
 *
 */

#include <string.h>
#include "image.h"
#include "endian.h"
#include "binFile.h"

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
int imageCheck(const uint32_t addr)
{
    image_header_t hdr;    
    uint32_t checksum;
    uint8_t         buf[32];
    uint32_t        size;
    uint8_t         u32tmp;
    
    HalFlashRead(&hdr, addr, sizeof(image_header_t));
    
    if (ntohl(hdr.ih_magic) != IH_MAGIC)
        return -1;
    
    checksum = ntohl(hdr.ih_hcrc);
    hdr.ih_hcrc = 0;
    
    if (checksum != crc32(0, (unsigned char *)&hdr, sizeof(image_header_t)))
        return -1;
    
    size = ntohl(hdr.ih_size);
    u32tmp = addr + sizeof(image_header_t);
    checksum = 0;
    
    while(size)
    {
        uint32_t    len;
        
        len = (size > sizeof(buf))?sizeof(buf):size;
        
        HalFlashRead(buf, u32tmp, len);
        
        checksum = crc32(checksum, buf, len);
        
        u32tmp += len;
        size -= len;
    }
    
    if (checksum != ntohl(hdr.ih_dcrc))
        return -1;
        
    return binFileValid(addr + sizeof(image_header_t));
}

