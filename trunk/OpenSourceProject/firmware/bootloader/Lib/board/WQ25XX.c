/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    WQ25XX.c
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
//0XEF13 ---- W25Q08  
//0XEF14 ---- W25Q16    
//0XEF15 ---- W25Q32  
//0XEF16 ---- W25Q64 
//0XEF17 ---- W25Q128
*******************************************************************************/
#include "Includes.h"

Flash_Info st_FlashInfor;

#define SF_CS_GPIO               GPIOC
#define SF_CS_PIN                GPIO_Pin_13
#define RCC_FLASH                RCC_APB2Periph_GPIOC

#define SPI_FLASH_CS_LOW()       GPIO_ResetBits(SF_CS_GPIO, SF_CS_PIN) 
#define SPI_FLASH_CS_HIGH()      GPIO_SetBits(SF_CS_GPIO, SF_CS_PIN)

INT8U SPI_FLASH_SendByte( INT8U dat )
{
    return SPI1_ReadWriteByte( dat );
}

static void W25QXX_WaitForWriteEnd( void )
{
    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte( W25X_READSTATUS );	

    while(( SPI_FLASH_SendByte(0) & 0x01 ) == SET);

    SPI_FLASH_CS_HIGH();        
}

static void W25QXX_WriteStatus( INT8U _ucValue)
{
    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte( W25X_WRITESTATUS );
    SPI_FLASH_SendByte(_ucValue);
    
    SPI_FLASH_CS_HIGH();
}

static void SPI_FLASH_CsInit( void )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_FLASH, ENABLE);
       
    SPI_FLASH_CS_HIGH();
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = SF_CS_PIN;
    GPIO_Init(SF_CS_GPIO, &GPIO_InitStructure);   
    
    SPIx_Init( SPIX1 );  //spi1
    
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte( W25X_WRITEDISABLE );
    SPI_FLASH_CS_HIGH();
    
    W25QXX_WaitForWriteEnd();
  
    W25QXX_WriteStatus( 0 );
}

static INT32U  SPI_FLASH_ReadID(void)
{
    INT32U ID = 0, Temp0 = 0, Temp1 = 0;
    
    SPI_FLASH_CS_LOW();
    
    SPI_FLASH_SendByte( 0x90 );
    
    SPI_FLASH_SendByte(0x00);
    SPI_FLASH_SendByte(0x00);
    SPI_FLASH_SendByte(0x00);
    Temp0 = SPI_FLASH_SendByte(DUMMY_BYTE);
    Temp1 = SPI_FLASH_SendByte(DUMMY_BYTE);
    
    SPI_FLASH_CS_HIGH();
    
    ID = (Temp0 << 8) | Temp1;
    
    return ID;
}

void W25QXX_Init( void )
{
    INT32U ID;

    SPI_FLASH_CsInit();
    
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


Flash_Info W25QXX_Infor( void )
{
    return st_FlashInfor;
}

void W25QXX_Write_Enable(void)
{
    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte( W25X_WRITEENABLE );
    
    SPI_FLASH_CS_HIGH();
} 

void W25QXX_Write_Disable(void)
{
    SPI_FLASH_CS_LOW();
    
    SPI_FLASH_SendByte( W25X_WRITEDISABLE );
    
    SPI_FLASH_CS_HIGH();
} 

void W25QXX_Write_SR( INT8U sr )
{
    SPI_FLASH_CS_LOW();
    
    SPI_FLASH_SendByte( W25X_WRITESTATUS );
    SPI_FLASH_SendByte(sr);
    
    SPI_FLASH_CS_HIGH();
}

u8 W25QXX_ReadSR(void)
{  
    INT8U byte=0; 

    SPI_FLASH_CS_LOW();
    
    SPI_FLASH_SendByte( W25X_READSTATUS );
    byte=SPI_FLASH_SendByte( DUMMY_BYTE );

    SPI_FLASH_CS_HIGH();

    return byte;
} 


void W25QXX_Read( INT32U ReadAddr, INT8U* pBuffer, INT16U NumByteToRead )
{ 
 
    if ((NumByteToRead == 0) ||(ReadAddr + NumByteToRead) > st_FlashInfor.memSize )
    {
       return;
    }
 
  
    SPI_FLASH_CS_LOW();
    
    SPI_FLASH_SendByte( W25X_READBYTE );

    SPI_FLASH_SendByte( (ReadAddr & 0xFF0000) >>16 );
    SPI_FLASH_SendByte( (ReadAddr & 0xFF00) >>8 );
    SPI_FLASH_SendByte( ReadAddr & 0xff );
    
    while (NumByteToRead--)
    {
      *pBuffer++ = SPI_FLASH_SendByte(DUMMY_BYTE);
    } 
    
    SPI_FLASH_CS_HIGH();
}

void W25QXX_WritePage(INT8U* pBuffer,u32 WriteAddr,u16 NumByteToWrite)
{
    u16 i;
    
    W25QXX_Write_Enable();

    SPI_FLASH_CS_LOW();
    
    SPI_FLASH_SendByte( W25X_PAGEPROGRAM );

    SPI_FLASH_SendByte((INT8U)((WriteAddr)>>16));
    SPI_FLASH_SendByte((INT8U)((WriteAddr)>>8));
    SPI_FLASH_SendByte((INT8U)WriteAddr);
    
    for( i=0; i < NumByteToWrite; i++ )
    {
        SPI_FLASH_SendByte(pBuffer[i]);
    }
    
    SPI_FLASH_CS_HIGH();
    
    W25QXX_WaitForWriteEnd();
} 


static void W25QXX_Erase_Sector(INT32U Dst_Addr)
{  
    Dst_Addr*=4096;
    
    W25QXX_Write_Enable();
    W25QXX_WaitForWriteEnd();
    
    SPI_FLASH_CS_LOW();

    SPI_FLASH_SendByte( W25X_SECTORERASE );
    SPI_FLASH_SendByte( (INT8U)((Dst_Addr)>>16) );
    SPI_FLASH_SendByte( (INT8U)((Dst_Addr)>>8) );
    SPI_FLASH_SendByte( (INT8U)Dst_Addr );
    
    SPI_FLASH_CS_HIGH();
    
    W25QXX_WaitForWriteEnd();
}

void W25QXX_Erase_Chip(void)
{
    W25QXX_Write_Enable();                  //SET WEL 
    W25QXX_WaitForWriteEnd();
    
    SPI_FLASH_CS_LOW();
    SPI_FLASH_SendByte( W25X_CHIPERASE );
    
    SPI_FLASH_CS_HIGH();
    
    W25QXX_WaitForWriteEnd();
} 


void W25QXX_Write_NoCheck(INT8U* pBuffer,INT32U WriteAddr,INT16U NumByteToWrite)   
{
    INT16U pageremain;

    pageremain = 256-WriteAddr%256;
        
    if(NumByteToWrite <= pageremain )
          pageremain=NumByteToWrite;

    while(1)
    {
            W25QXX_WritePage(pBuffer,WriteAddr,pageremain);

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


INT8U W25QXX_BUFFER[4096];
void W25QXX_Write( INT32U WriteAddr, INT8U *pBuffer, INT16U NumByteToWrite)   
{ 
    INT32U secpos;
    INT16U secoff;
    INT16U secremain;
    INT16U i;
    INT8U * W25QXX_BUF;

    W25QXX_BUF = W25QXX_BUFFER;
    secpos = WriteAddr/4096;
    secoff = WriteAddr%4096;
    secremain = 4096-secoff;

    if(NumByteToWrite <= secremain)
        secremain = NumByteToWrite;
    
    while(1) 
    {
            W25QXX_Read(secpos*4096, W25QXX_BUF, 4096); 
            for(i=0;i<secremain;i++)
            {
                  if(W25QXX_BUF[secoff+i]!=0XFF)
                          break;  
            }

            if(i<secremain)
            {
                  W25QXX_Erase_Sector(secpos);
                  for(i=0;i<secremain;i++)
                  {
                          W25QXX_BUF[i+secoff]=pBuffer[i];
                  }
                  W25QXX_Write_NoCheck(W25QXX_BUF,secpos*4096,4096);
            }
            else
            {
                  W25QXX_Write_NoCheck(pBuffer,WriteAddr,secremain);
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


/*  EOF */