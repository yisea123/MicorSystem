/**
  ******************************************************************************
  *                     (c) Copyright 2018, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    apps_download.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#include "Includes.h"

/* Private define ------------------------------------------------------------*/
#define FW_FLASH_ADDRESS                                100*256 
#define HEADER_LEN                                      128

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static FwInfor st_FwInfor;
static uint16_t PacketIndex;
static uint16_t TotalIndex;
static uint16_t result;
static uint8_t ReadBuff[HEADER_LEN];
/* Extern variables ----------------------------------------------------------*/

/* Private function ---------------------------------------------------------*/
static void AppBoot_Set( void );
static void AppFwUpdate_ParserHeader(  INT8U *buff );


static void AppBoot_Set( void )
{
      INT32U FwStartAddress;
      INT8U buff[2];
      
      FwStartAddress = 0;
      buff[0] = 0x5A;
      buff[1] = 0x5A;

      W25QXX_Write(FwStartAddress, buff , 2 );			  
}

static void AppFwUpdate_ParserHeader(  INT8U *buff )
{
        INT16U i, len;

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

uint16_t AppFwUpdate_DownLoad( uint8_t *buff, uint16_t len, uint16_t index  )
{
      INT32U address;
      INT32U FwStartAddress;
      
      FwStartAddress = FW_FLASH_ADDRESS;      	
      result = ERR_OK;
      if( index == 0 )   				
      {
              AppFwUpdate_ParserHeader( buff );
              address = 0;
              PacketIndex = 0xffff;
              
              TotalIndex = (st_FwInfor.IntFlashFileSize)/HEADER_LEN;
              TotalIndex += (st_FwInfor.IntFlashFileSize)%HEADER_LEN ? 1 : 0;             
      }
        
      if( PacketIndex != index )
      {
              address = index *HEADER_LEN;
              W25QXX_Write( FwStartAddress + address, buff, len );
              W25QXX_Read( FwStartAddress + address, ReadBuff, len );   
               
              PacketIndex = index;
              if( memcmp( buff, ReadBuff, len) != 0 )
              {
                   return ERR_PARAM;
              }               
      }
        
      if( TotalIndex == (index+1))		
      {
           AppBoot_Set();
           result = ERR_END;
      }
      
      return result;
}

void AppFwUpdate_Finish( void )
{
     if( result == ERR_END )
     {
         WDG_Init();
         while(1);
     }
}

/* End of this file */

