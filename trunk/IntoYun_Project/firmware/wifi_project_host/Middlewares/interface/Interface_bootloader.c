/** \file

$Id: interface_bootloader.c 40486 2018-08-15 13:50:21Z tangmingfei2013@126.com $

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
#include "iap.h"
#include "WQ25XX.h"

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "Interface_bootloader.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define FW_FLASH_ADDRESS                                100*256 
#define ApplicationAddress                              0x08008000
#define FW_FLAG                                         0X5A5A
#define DATA_LEN                                        1024
#define HEADER_LEN                                      128

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
FwInfor st_FwInfor;
static uint8_t dataBuff[DATA_LEN];
typedef  void (*pFunction)(void);

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void AppFwUpdate_ParserHeader(  uint8_t *buff );
static uint8_t AppBoot_CheckFlag( void );
static void AppBoot_Reset( void );
static void Main_AppRun( void );
static uint8_t AppBoot_PrgramAction( void );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void AppBoot_Program( void )
{
    uint16_t BootFlag;
    uint8_t buff[HEADER_LEN];
    uint32_t FwStartAddress;
    uint8_t Flagbuff[2];

    FwStartAddress = 0;
    W25QXX_Read( FwStartAddress, Flagbuff, 2 );
    BootFlag = Flagbuff[0]<<8|Flagbuff[1];

    if( BootFlag == FW_FLAG )
    {
        FwStartAddress = FW_FLASH_ADDRESS; 
        W25QXX_Read( FwStartAddress, buff, HEADER_LEN );  
        AppFwUpdate_ParserHeader( buff );
        AppBoot_PrgramAction();

        AppBoot_Reset();
    }     
    Main_AppRun();
}

void AppFwUpdate_Action( void )
{
    uint8_t step = 0xff;
    uint8_t flag; 

    flag = AppBoot_CheckFlag();
    if( flag )
    {
        step = 1;
    }     

    switch( step )
    {
      case 1:
        AppBoot_Program();
        break;
      default:
        Main_AppRun();
        break;
    }    
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void AppFwUpdate_ParserHeader(  uint8_t *buff )
{
    uint16_t i, len;

    len = 0;
    for( i = 0 ; i < 32; i++  ) 
    {
          st_FwInfor.FwVender[i] = buff[len++];     
    }

    for( i = 0; i < 16; i++ )
    {
          st_FwInfor.Platform[i] = buff[len++];
    } 

    for( i = 0; i < 8; i++ )
    {
         st_FwInfor.AppfwVer[i] = buff[len++];
    } 

    for( i = 0; i < 8; i++ )
    {
         st_FwInfor.BootLaoderfwVer[i] = buff[len++];
    } 

    for( i = 0; i < 8; i++ )
    {
         st_FwInfor.MCSVer[i] = buff[len++];
    }        

    st_FwInfor.IntFlashFileSize  = buff[len++]<<24;   
    st_FwInfor.IntFlashFileSize |= buff[len++]<<16;
    st_FwInfor.IntFlashFileSize |= buff[len++]<<8;
    st_FwInfor.IntFlashFileSize |= buff[len++];	

    st_FwInfor.IntFlashStartAddr  = buff[len++]<<24;   
    st_FwInfor.IntFlashStartAddr |= buff[len++]<<16;
    st_FwInfor.IntFlashStartAddr |= buff[len++]<<8;
    st_FwInfor.IntFlashStartAddr |= buff[len++];	

    st_FwInfor.IntFlashEndAddr  = buff[len++]<<24;   
    st_FwInfor.IntFlashEndAddr |= buff[len++]<<16;
    st_FwInfor.IntFlashEndAddr |= buff[len++]<<8;
    st_FwInfor.IntFlashEndAddr |= buff[len++];			

    st_FwInfor.ExFlashFileSize  = buff[len++]<<24;   
    st_FwInfor.ExFlashFileSize |= buff[len++]<<16;
    st_FwInfor.ExFlashFileSize |= buff[len++]<<8;
    st_FwInfor.ExFlashFileSize |= buff[len++];	

    st_FwInfor.ExFlashStartAddr  = buff[len++]<<24;   
    st_FwInfor.ExFlashStartAddr |= buff[len++]<<16;
    st_FwInfor.ExFlashStartAddr |= buff[len++]<<8;
    st_FwInfor.ExFlashStartAddr |= buff[len++];	

    st_FwInfor.ExFlashEndAddr  = buff[len++]<<24;   
    st_FwInfor.ExFlashEndAddr |= buff[len++]<<16;
    st_FwInfor.ExFlashEndAddr |= buff[len++]<<8;
    st_FwInfor.ExFlashEndAddr |= buff[len++];			
            
    st_FwInfor.DevType = buff[len++];

    for( i = 0 ; i < 29; i++ )
    {
        st_FwInfor.res[i] = buff[len++]; 
    }

    st_FwInfor.crc16 = buff[len++]<<8;
    st_FwInfor.crc16 |= buff[len++];	
}

static void AppBoot_Reset( void )
{
    uint32_t FwStartAddress;
    uint8_t buff[2];

    FwStartAddress = 0;

    buff[0] = 0;
    buff[1] = 0;

    W25QXX_Write(FwStartAddress, buff , 2 );
}

static uint8_t AppBoot_CheckFlag( void )
{
    uint32_t FwStartAddress;
    uint8_t Flagbuff[2];
    uint16_t BootFlag;

    FwStartAddress = 0;
    W25QXX_Read( FwStartAddress, Flagbuff, 2 );
    BootFlag = Flagbuff[0]<<8|Flagbuff[1];

    if( BootFlag == FW_FLAG )
    {
        return 1;
    }

    return 0;
}

static void Main_AppRun( void )
{
    pFunction Jump_To_Application;
    uint32_t JumpAddress;

    /* Test if user code is programmed starting from address 0x08008000 */
    if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
    { /* Jump to user application */

          JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
          Jump_To_Application = (pFunction) JumpAddress;
          /* Initialize user application's Stack Pointer */
          __set_MSP(*(__IO uint32_t*) ApplicationAddress);
          Jump_To_Application();
    }  
}

static uint8_t AppBoot_PrgramAction( void )
{
    uint8_t *pWrBuff;
    uint32_t TotalPack;
    uint32_t Prolen;
    uint32_t FwStartAddress;
    uint32_t i;
    uint16_t Wrlen;
    static uint32_t address;

    TotalPack = st_FwInfor.IntFlashFileSize/DATA_LEN;
    TotalPack += st_FwInfor.IntFlashFileSize%DATA_LEN ? 1 : 0;

    FwStartAddress = FW_FLASH_ADDRESS;    
    address = 0;
    Prolen = 0;
    Wrlen = 0;

    for( i = 0; i < TotalPack; i++ )
    {
          pWrBuff = dataBuff;
          if( st_FwInfor.IntFlashFileSize  > DATA_LEN )
          {
                W25QXX_Read( FwStartAddress+address, pWrBuff, DATA_LEN );
                address += DATA_LEN;
                if( i == 0 )
                {
                    Wrlen = DATA_LEN - HEADER_LEN;
                    pWrBuff += HEADER_LEN;      
                }
                else
                {
                     Wrlen = DATA_LEN;
                }
                
                st_FwInfor.IntFlashFileSize -= DATA_LEN;
          }
          else
          {
                Wrlen = st_FwInfor.IntFlashFileSize%DATA_LEN;
                W25QXX_Read( FwStartAddress+address, pWrBuff, Wrlen);
          }
          
          __set_PRIMASK(1);
          IAP_FlashProgram(ApplicationAddress+Prolen, pWrBuff, Wrlen);
          Prolen += Wrlen;
          __set_PRIMASK(0);
    }	

    return 1;
}


/* End of this file */

