/** \file

$Id: spiflash.c 40486 2018-09-21 14:32:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "spiflash.h"

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "board.h"

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
Flash_Info st_FlashInfor;
const char l_spiflash_PkgId[] = "spiflash";

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static uint8_t SPI_FLASH_SendByte( uint8_t dat )
{
    return spif_Impl_SendByte( dat );
}

static void SPI_FLASH_CS_select( bool sel )
{
    board_SpiSlaveSelectSet( board_Spi_1, sel );
}

static void spiflash_WaitForWriteEnd( void )
{
    SPI_FLASH_CS_select( false);

    SPI_FLASH_SendByte( CMD_READSTATUS );	

    while(( SPI_FLASH_SendByte(0) & 0x01 ) == SET);

    SPI_FLASH_CS_select( true );        
}

static uint32_t  SPI_FLASH_ReadID(void)
{
    uint32_t ID = 0, Temp0 = 0, Temp1 = 0;
    
    SPI_FLASH_CS_select( false);
  
    SPI_FLASH_SendByte( 0x9F );
    
    SPI_FLASH_SendByte(0x00);
    SPI_FLASH_SendByte(0x00);
    SPI_FLASH_SendByte(0x00);
    Temp0 = SPI_FLASH_SendByte(DUMMY_BYTE);
    Temp1 = SPI_FLASH_SendByte(DUMMY_BYTE);
    
    SPI_FLASH_CS_select( true );
    
    ID = (Temp0 << 8) | Temp1;
    
    return ID;
}

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void spiflash_Init( void )
{
    uint32_t ID;

    spi_Impl_Init();
    
    ID = SPI_FLASH_ReadID();
    if( ID == 0XEF17)	      //W25Q128
    {
            st_FlashInfor.pageSize = 256;
            st_FlashInfor.pageTotal = 65536;
            st_FlashInfor.memSize = 256 * 65536;
    }
    else if( ID == 0XEF16 )   //W25Q64 
    {
            st_FlashInfor.pageSize = 256;
            st_FlashInfor.pageTotal = 32768;
            st_FlashInfor.memSize = 256 * 32768;
    }
    else if( ID == 0XEF15 )    //W25Q32
    {
            st_FlashInfor.pageSize = 256;
            st_FlashInfor.pageTotal = 16384;
            st_FlashInfor.memSize = 256 * 16384;
    }
    else if( ID == 0XEF14 )   //W25Q16
    {
            st_FlashInfor.pageSize = 256;
            st_FlashInfor.pageTotal = 8192;
            st_FlashInfor.memSize = 256 * 8192;
    }
    else if( ID == 0XEF13 )		//W25Q08
    {
            st_FlashInfor.pageSize = 256;
            st_FlashInfor.pageTotal = 4096;
            st_FlashInfor.memSize = 256 * 4096;
    }
    else
    {
            st_FlashInfor.pageSize = 0;
            st_FlashInfor.pageTotal = 0;
            st_FlashInfor.memSize = 0;
    }
}


Flash_Info spiflash_Infor( void )
{
    return st_FlashInfor;
}

void spiflash_Write_Enable(void)
{
    SPI_FLASH_CS_select( false);
    
    SPI_FLASH_SendByte( CMD_WRITEENABLE );
    
    SPI_FLASH_CS_select( true);
} 

void spiflash_Write_Disable(void)
{
    SPI_FLASH_CS_select( false);
    
    SPI_FLASH_SendByte( CMD_WRITEDISABLE );
    
    SPI_FLASH_CS_select( true);
} 

void spiflash_Write_SR( uint8_t sr )
{
    SPI_FLASH_CS_select( false);
    
    SPI_FLASH_SendByte( CMD_WRITESTATUS );
    SPI_FLASH_SendByte(sr);
    
   SPI_FLASH_CS_select( true);
}

uint8_t spiflash_ReadSR(void)
{  
    uint8_t byte=0; 

    SPI_FLASH_CS_select( false);
    
    SPI_FLASH_SendByte( CMD_READSTATUS );
    byte=SPI_FLASH_SendByte( DUMMY_BYTE );

    SPI_FLASH_CS_select( true);

    return byte;
} 


void spiflash_WritePage(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
    uint16_t i;
    
    spiflash_Write_Enable();

    SPI_FLASH_CS_select( false);
    
    SPI_FLASH_SendByte( CMD_PAGEPROGRAM );

    SPI_FLASH_SendByte((uint8_t)((WriteAddr)>>16));
    SPI_FLASH_SendByte((uint8_t)((WriteAddr)>>8));
    SPI_FLASH_SendByte((uint8_t)WriteAddr);
    
    for( i=0; i < NumByteToWrite; i++ )
    {
        SPI_FLASH_SendByte(pBuffer[i]);
    }
    
     SPI_FLASH_CS_select( true);
    
    spiflash_WaitForWriteEnd();
} 


static void spiflash_Erase_Sector(uint32_t Dst_Addr)
{  
    Dst_Addr*=4096;
    
    spiflash_Write_Enable();
    spiflash_WaitForWriteEnd();
    
    SPI_FLASH_CS_select( false);

    SPI_FLASH_SendByte( CMD_SECTORERASE );
    SPI_FLASH_SendByte( (uint8_t)((Dst_Addr)>>16) );
    SPI_FLASH_SendByte( (uint8_t)((Dst_Addr)>>8) );
    SPI_FLASH_SendByte( (uint8_t)Dst_Addr );
    
    SPI_FLASH_CS_select( true);
    
    spiflash_WaitForWriteEnd();
}

void spiflash_Erase_Chip(void)
{
    spiflash_Write_Enable();                  //SET WEL 
    spiflash_WaitForWriteEnd();
    
    SPI_FLASH_CS_select( false);

    SPI_FLASH_SendByte( CMD_CHIPERASE );
    
     SPI_FLASH_CS_select( true);
    
    spiflash_WaitForWriteEnd();
} 


void spiflash_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{
    uint16_t pageremain;

    pageremain = 256-WriteAddr%256;
        
    if(NumByteToWrite <= pageremain )
          pageremain=NumByteToWrite;

    while(1)
    {
            spiflash_WritePage(pBuffer,WriteAddr,pageremain);

            if( NumByteToWrite == pageremain )
                    break;
            else 
            {
                    pBuffer+=pageremain;
                    WriteAddr+=pageremain;

                    NumByteToWrite-=pageremain;
                    if(NumByteToWrite>256)
                       pageremain = 256;
                    else 
                       pageremain = NumByteToWrite; 
            }
    }
}

void spiflash_Read( uint32_t ReadAddr, uint8_t* pBuffer, uint16_t NumByteToRead )
{ 
 
    if ((NumByteToRead == 0) ||(ReadAddr + NumByteToRead) > st_FlashInfor.memSize )
    {
       return;
    }

    SPI_FLASH_CS_select( false);
    
    SPI_FLASH_SendByte( CMD_READBYTE );

    SPI_FLASH_SendByte( (ReadAddr & 0xFF0000) >>16 );
    SPI_FLASH_SendByte( (ReadAddr & 0xFF00) >>8 );
    SPI_FLASH_SendByte( ReadAddr & 0xff );
    
    while (NumByteToRead--)
    {
      *pBuffer++ = SPI_FLASH_SendByte(DUMMY_BYTE);
    } 
    
    SPI_FLASH_CS_select( true);
}

uint8_t spiflash_BUFFER[4096];
void spiflash_Write( uint32_t WriteAddr, uint8_t *pBuffer, uint16_t NumByteToWrite)   
{ 
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t * spiflash_BUF;

    spiflash_BUF = spiflash_BUFFER;
    secpos = WriteAddr/4096;
    secoff = WriteAddr%4096;
    secremain = 4096-secoff;

    if(NumByteToWrite <= secremain)
        secremain = NumByteToWrite;
    
    while(1) 
    {
            spiflash_Read(secpos*4096, spiflash_BUF, 4096); 
            for(i=0;i<secremain;i++)
            {
                  if(spiflash_BUF[secoff+i]!=0XFF)
                          break;  
            }

            if(i<secremain)
            {
                  spiflash_Erase_Sector(secpos);
                  for(i=0;i<secremain;i++)
                  {
                          spiflash_BUF[i+secoff]=pBuffer[i];
                  }
                  spiflash_Write_NoCheck(spiflash_BUF,secpos*4096,4096);
            }
            else
            {
                  spiflash_Write_NoCheck(pBuffer,WriteAddr,secremain);
            }    
            
            if( NumByteToWrite == secremain)
                  break;
            else
            {
                  secpos++;
                  secoff=0;

                  pBuffer += secremain; 
                  WriteAddr += secremain;
                  NumByteToWrite -= secremain;
                  if( NumByteToWrite>4096 )
                       secremain = 4096;
                  else
                      secremain = NumByteToWrite;	
            }
    }
}

/* End of this file */