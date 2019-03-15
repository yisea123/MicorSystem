/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    mcs_protocol.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @brief   McsParser ctrl interface
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
/* Includes -------------------------------------------------------------------*/
#ifndef _MCS_PROTOCOL_H
#define _MCS_PROTOCOL_H

#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#define   HEAD                              '['
#define   END                               ']'
#define   DATALEN                           256

#define   MCS_SUCESS                        0x8000
#define   MCS_READ                          0x4000
#define   CAL_CMD_CODE                      0x3fff

#define PROTOCOL_HEADER_OFFSET              0
#define PROTOCOL_SOURADDR_OFFSET            1
#define PROTOCOL_TARADDR_OFFSET             2    
#define PROTOCOL_FUMN_OFFSET                3    
#define PROTOCOL_CMD_OFFSET                 5
#define PROTOCOL_DATA_LENGTH_OFFSET         7
#define PROTOCOL_DATA_OFFSET                8

typedef enum
{
  ERROR_NONE                 = 0, 
  ERROR_OUT_OF_RANGE         = 0x0001,
  ERROR_UN_RECONGNITION      = 0x0002,
  ERROR_FAIL_SAVE_PARAMATER  = 0x0003,
  ERROR_PARAMATER_NOT_ESIXIT = 0x0004,
}MCS_ErrorCode_enum;

typedef struct {
  uint16_t OptCode        :14;
  uint16_t TransfMode     :1;
  uint16_t OptMode        :1;
} MCS_CommStatus;

typedef struct
{
  uint8_t *McsParserBuff;
  uint8_t  HostSendBuf[DATALEN];
  uint8_t  sourAddress;          /* 源地址          */
  uint8_t   targetAddress;       /* 目的地址         */
  uint16_t  frumIndex;            /* 帧指针          */
  uint8_t  dataLength;           /* 数据长度         */
  uint8_t  crc;                  /* 帧数据包CRC      */
  uint16_t cmdCode;              /* 命令码          */  
  uint8_t  dataBuff[DATALEN];    /* 数据区Buff      */
  void     (*pf_SendPut)(uint8_t*, uint16_t);
  void*    CmdTable;
  uint16_t CmdTotal;
}MCS;

typedef void (*PFNCT_MCS)(MCS *);

typedef struct 
{
  uint8_t     command;
  PFNCT_MCS   pf_FuncPtr;
} MCS_CmdNode;

bool MCS_CommHandlerAction( MCS *pst_mcs, uint8_t *srcbuff);
bool MCS_HostSendPacket( MCS *pst_mcs );
bool MCS_SlaveExecuter( MCS *pst_mcs );

#endif  /* _MCS_PROTOCOL_H */ 

