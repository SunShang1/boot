/*
 * �ļ����ƣ� main.c
 *
 * �ļ�˵���� main �ļ�
 */

#include "board.h"
#include "crc.h"
#include "image.h"
#include "binFile.h"
#include "release.h"

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
* Function *
********************************************/
int main(void)
{
    DisableInterrupts();

    halBoardInit();    

    if(imageCheck(CFG_IMG2_ADDR) == 0)
    {
        binFileCopy(CFG_IMG_ADDR, CFG_IMG2_ADDR + sizeof(image_header_t));
        
        HalFlashErase(CFG_IMG2_ADDR);
    }
    
    asm("LJMP 0x2000\n");
}


