/** \file

$Id: spiflash.h 40486 2018-09-21 14:32:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
#ifndef __SPIFLASH_H
#define __SPIFLASH_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "spi.h"
/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define DUMMY_BYTE              0x5A
#define CMD_WRITESTATUS        0x01 
#define CMD_PAGEPROGRAM        0x02 
#define CMD_READBYTE           0x03 
#define CMD_WRITEDISABLE       0x04 
#define CMD_READSTATUS         0x05 
#define CMD_WRITEENABLE        0x06 

#define CMD_FASTREADATA        0x0B 
#define CMD_FASTREADDUAN       0x3B 
#define CMD_BLOCKERASE         0xD8 
#define CMD_SECTORERASE        0x20 

#define CMD_CHIPERASE          0xC7 
#define CMD_POWERDOWN          0xB9 
#define CMD_RELEASEPOWERDOWN   0xAB 
#define CMD_DEVICEID           0xAB 
#define CMD_MDEVICEID          0x90 
#define CMD_JVEDICECID         0x9F 
#define READYBIT_MASK           0x01

#define CMD_WSTATUS_REGISTER3  0x11
#define CMD_RSTATUS_REGISTER3  0X15


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
void spiflash_Write( uint32_t WriteAddr, uint8_t *pBuffer, uint16_t NumByteToWrite);
void spiflash_Read( uint32_t ReadAddr, uint8_t* pBuffer, uint16_t NumByteToRead );
void spiflash_Init( void );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __SPIFLASH_H */