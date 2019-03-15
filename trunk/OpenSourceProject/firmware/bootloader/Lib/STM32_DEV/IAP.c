/**
  ******************************************************************************
  *                     (c) Copyright 2018, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    iap.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/10
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#include "includes.h"

#define FLASH_START_ADDRESS     0x08000000

#ifdef STM32F10X_LD
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#elif defined STM32F10X_MD
  #define FLASH_PAGE_SIZE    ((uint16_t)0x400)
#elif defined STM32F10X_HD
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)
#elif defined STM32F10X_CL
  #define FLASH_PAGE_SIZE    ((uint16_t)0x800)  
#endif /* STM32F10X_LD */

static INT32U FlashWbuff[512];

void FLASH_If_Init(void)
{ 
    /* Unlock the Flash Program Erase controller */
    FLASH_Unlock(); 
    
    /* Clear All pending flags */
    FLASH_ClearFlag(FLASH_FLAG_BSY | 
                    FLASH_FLAG_EOP | 
                    FLASH_FLAG_PGERR | 
                    FLASH_FLAG_WRPRTERR);
}

static uint32_t IAP_FlashReadWord(uint32_t addr)
{
    return *(vu32*)addr; 
} 

static uint32_t GetPageAddress(uint32_t Address)
{
    INT32U index = 0;
    INT32U eraseAddress = 0;
      
    index = (Address - FLASH_START_ADDRESS)/FLASH_PAGE_SIZE;
    eraseAddress = FLASH_START_ADDRESS + index*FLASH_PAGE_SIZE;
    if(Address < eraseAddress)
    {    
         eraseAddress = FLASH_START_ADDRESS + (index-1)*FLASH_PAGE_SIZE;
    }
    
    return eraseAddress;
}

INT8U IAP_FlashProgram( INT32U WriteAddr,INT8U *pRbuff, INT32U len )
{
      INT32U *pBuffer;
      INT32U NumToWrite, i, data;
      FLASH_Status status = FLASH_COMPLETE;
      
      INT32U addrx=0;
      INT32U endaddr=0;
      
      FLASH_Unlock();
      
      pBuffer = FlashWbuff;
      NumToWrite = 0;
      
      for( i = 0; i < len; )
      {
        
          data =  pRbuff[i++];
          data |= pRbuff[i++]<<8;
          data |= pRbuff[i++]<<16;
          data |= pRbuff[i++]<<24;
          
          pBuffer[NumToWrite++] = data;
      }     
      
      addrx = WriteAddr;
      endaddr = WriteAddr+NumToWrite*4;
   
      while( addrx < endaddr )
      {
              if( IAP_FlashReadWord( addrx ) != 0XFFFFFFFF )
              {   
                      status = FLASH_ErasePage( GetPageAddress(addrx));
                      if( status != FLASH_COMPLETE )
                        break;
              }
              else 
              {
                      addrx+=4;
              }
      } 
 
      if( status == FLASH_COMPLETE )
      {
		while( WriteAddr < endaddr )
		{
			if( FLASH_ProgramWord(WriteAddr,*pBuffer)!= FLASH_COMPLETE )
			{ 
				return 0;
			}
			WriteAddr+=4;
			pBuffer++;
		} 
	}
  
	FLASH_Lock();
 
	return 1;
}

/* End of this file */