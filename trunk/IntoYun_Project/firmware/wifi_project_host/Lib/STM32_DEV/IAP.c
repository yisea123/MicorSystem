/** \file

$Id: IAP.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "stm32f10x.h"

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "IAP.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
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

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static uint32_t FlashWbuff[512];

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static uint32_t IAP_FlashReadWord(uint32_t addr);
static uint32_t GetPageAddress(uint32_t Address);

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
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

uint8_t IAP_FlashProgram( uint32_t WriteAddr,uint8_t *pRbuff, uint32_t len )
{
      uint32_t *pBuffer;
      uint32_t NumToWrite, i, data;
      FLASH_Status status = FLASH_COMPLETE;
      
      uint32_t addrx=0;
      uint32_t endaddr=0;
      
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

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static uint32_t IAP_FlashReadWord(uint32_t addr)
{
    return *(vu32*)addr; 
} 

static uint32_t GetPageAddress(uint32_t Address)
{
    uint32_t index = 0;
    uint32_t eraseAddress = 0;
      
    index = (Address - FLASH_START_ADDRESS)/FLASH_PAGE_SIZE;
    eraseAddress = FLASH_START_ADDRESS + index*FLASH_PAGE_SIZE;
    if(Address < eraseAddress)
    {    
         eraseAddress = FLASH_START_ADDRESS + (index-1)*FLASH_PAGE_SIZE;
    }
    
    return eraseAddress;
}


/* End of this file */