/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    WQ25XX.h
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
*/
#ifndef  __W25QXX_H
#define  __W25QXX_H

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
    INT8U prodVer;
    INT8U staRegByte;
    INT16U ID;
    INT16U res;
    INT16U pageSize;
    INT32U pageTotal;
    INT32U memSize;
} Flash_Info;

void W25QXX_Init( void );
void W25QXX_Erase_Chip(void);
void W25QXX_Write( INT32U WriteAddr, INT8U *pBuffer, INT16U NumByteToWrite) ;
void W25QXX_Read( INT32U ReadAddr, INT8U* pBuffer,  INT16U NumByteToRead) ;
Flash_Info W25QXX_Infor( void );

void WQ25XXtest( void );


 #endif /* __W25QXX_H */

