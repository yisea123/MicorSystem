/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    apps_commHandler.h
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
#ifndef _APPS_COMMHANDLER_H
#define _APPS_COMMHANDLER_H

typedef enum
{
  PROTOCOL_TEST_CMD = 0x0010, 
  PROTOCOL_RTC_CMD = 0x0011, 
  PROTOCOL_DOWNLOAD_CMD = 0x0012, 
  PROTOCOL_SHT20_CMD = 0x0013, 
  NULL_CMD = 0xff,
}Protocol_Cmd;    
    
   
void vApps_DebugActionInit( void );
void vApps_DebugPortActionHandler( void );
void vApps_UploadSht20Value( int8_t *data );

extern const MCS_CmdNode AppActionCmdTable[];
extern const uint8_t AppActionCmdTotal; 

#endif  /* _APPS_COMMHANDLER_H */