/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    apps_download.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/07/02
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#ifndef _APPS_DOWNLOAD_H
#define _APPS_DOWNLOAD_H

typedef struct{
    INT8U   FwVender[32];
    INT8U   Platform[16];
    INT8U   AppfwVer[8];
    INT8U   BootLaoderfwVer[8];
    INT8U   MCSVer[8];

    INT32U IntFlashFileSize;
    INT32U IntFlashStartAddr;
    INT32U IntFlashEndAddr;

    INT32U ExFlashFileSize;
    INT32U ExFlashStartAddr;
    INT32U ExFlashEndAddr;

    INT8U DevType;

    INT8U res[29];
    INT16U crc16;
}FwInfor;

typedef enum
{
  ERR_NULL = 0, 
  ERR_PARAM, 
  ERR_OK, 
  ERR_END,
}enum_DownLoad; 

uint16_t AppFwUpdate_DownLoad( uint8_t *buff, uint16_t len, uint16_t index  );
void AppFwUpdate_Finish( void );

#endif  /* _APPS_DOWNLOAD_H */