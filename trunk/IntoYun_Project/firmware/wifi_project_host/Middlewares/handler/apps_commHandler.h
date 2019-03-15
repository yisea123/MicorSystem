/** \file

$Id: apps_commHandler.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef _APPS_COMMHANDLER_H
#define _APPS_COMMHANDLER_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/ 
#include "mcs_protocol.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
  
typedef enum
{
  DEVICE_CONFIG_CMD = 0x0010,      //设备参数配置  
  DEVICE_ERROR_CMD = 0x0011, 
  DEVICE_CTRL_CMD = 0x0013,        //控制命令
  NULL_CMD = 0xff,
}SysCtrl_Cmd;

extern const MCS_CmdNode BlueToothActionCmdTable[];
extern const uint8_t BlueToothActionCmdTotal;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vApps_BlueToothActionInit( void );
void vApps_DebugActionInit( void );

void vApps_BlueToothActionHandler( void );
void vApps_DebugPortActionHandler( void );

void apps_SendErrorCode( uint8_t *para, uint8_t len );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _APPS_COMMHANDLER_H */ 