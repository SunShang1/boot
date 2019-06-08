/**
  ******************************************************************************
  * @file    image.h 
  * @author  George
  * @date    
  * @brief   header file for image
  ******************************************************************************
***/
#ifndef __IMAGE_H__
#define __IMAGE_H__

#include "pub_def.h"
#include "crc.h"

/********************************************
* Defines *
********************************************/
#define IH_MAGIC    0x20190123


/********************************************
* Typedefs *
********************************************/
typedef struct
{
    uint32_t        ih_magic;           /* Image Magic Number */
    uint32_t        ih_hcrc;            /* Image CRC Checksum */
    uint32_t        ih_dcrc;            /* Image Data CRC Checksum */
    uint32_t        ih_size;            /* Image Data Size */
    uint8_t         ih_version[8];      /* Image version */
    /* the image header length is 128, so padding 104 bytes */
    uint8_t         reserved[104];      /* pad */
}image_header_t;


/********************************************
* Function defines *
********************************************/
int imageCheck(const uint32_t img_addr);

#endif
