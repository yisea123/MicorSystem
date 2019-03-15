/** \file

$Id: mcs_protocol.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

#ifndef _MCS_PROTOCOL_H
#define _MCS_PROTOCOL_H

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif
 
/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
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
  uint8_t  sourAddress;       
  uint8_t  targetAddress;
  uint8_t  frumIndex; 
  uint8_t  dataLength; 
  uint8_t  crc; 
  uint16_t cmdCode;
  uint8_t  dataBuff[DATALEN];
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

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
bool MCS_CommHandlerAction( MCS *pst_mcs, uint8_t *srcbuff);
bool MCS_HostSendPacket( MCS *pst_mcs );
bool MCS_SlaveExecuter( MCS *pst_mcs );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif


#endif  /* _MCS_PROTOCOL_H */ 

