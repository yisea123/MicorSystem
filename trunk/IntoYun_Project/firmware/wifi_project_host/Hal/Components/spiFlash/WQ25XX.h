/** \file

$Id: WQ25XX.h 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
** Flash ID:   
//0XEF13 ---- W25Q08  
//0XEF14 ---- W25Q16    
//0XEF15 ---- W25Q32  
//0XEF16 ---- W25Q64 
//0XEF17 ---- W25Q128
*/
/*****************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/

#ifndef  __W25QXX_H
#define  __W25QXX_H

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define DUMMY_BYTE              0x5A
#define W25X_WRITESTATUS        0x01 
#define W25X_PAGEPROGRAM        0x02 
#define W25X_READBYTE           0x03 
#define W25X_WRITEDISABLE       0x04 
#define W25X_READSTATUS         0x05 
#define W25X_WRITEENABLE        0x06 

#define W25X_FASTREADATA        0x0B 
#define W25X_FASTREADDUAN       0x3B 
#define W25X_BLOCKERASE         0xD8 
#define W25X_SECTORERASE        0x20 

#define W25X_CHIPERASE          0xC7 
#define W25X_POWERDOWN          0xB9 
#define W25X_RELEASEPOWERDOWN   0xAB 
#define W25X_DEVICEID           0xAB 
#define W25X_MDEVICEID          0x90 
#define W25X_JVEDICECID         0x9F 
#define READYBIT_MASK           0x01

#define W25Q_WSTATUS_REGISTER3  0x11
#define W25Q_RSTATUS_REGISTER3  0X15


#define READ_GISTER3            0x15
#define WRITE_REGISTER3         0x11
#define W_PROTOC                0x64
#define W_UNPROTOC              0x60

typedef struct {
    uint8_t prodVer;
    uint8_t staRegByte;
    uint16_t ID;
    uint16_t res;
    uint16_t pageSize;
    uint32_t pageTotal;
    uint32_t memSize;
} Flash_Info;


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void W25QXX_Init( void );
void W25QXX_Erase_Chip(void);
void W25QXX_Write( uint32_t WriteAddr, uint8_t *pBuffer, uint16_t NumByteToWrite) ;
void W25QXX_Read( uint32_t ReadAddr, uint8_t* pBuffer,  uint16_t NumByteToRead) ;
Flash_Info W25QXX_Infor( void );

void WQ25XXtest( void );


 #endif /* __W25QXX_H */

