/** \file

$Id: interface_bootloader.c 40486 2018-08-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

#ifndef _INTERFACE_BOOTLOADER_H
#define _INTERFACE_BOOTLOADER_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/ 

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
    ERR_OK = 0,
    ERR_END ,
}enum_fw_code;


typedef struct{
    uint8_t   FwVender[32];
    uint8_t   Platform[16];
    uint8_t   AppfwVer[8];
    uint8_t   BootLaoderfwVer[8];
    uint8_t   MCSVer[8];

    uint32_t IntFlashFileSize;
    uint32_t IntFlashStartAddr;
    uint32_t IntFlashEndAddr;

    uint32_t ExFlashFileSize;
    uint32_t ExFlashStartAddr;
    uint32_t ExFlashEndAddr;

    uint8_t DevType;

    uint8_t res[29];
    uint8_t crc16;
}FwInfor;

extern FwInfor st_FwInfor;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void AppFwUpdate_Action( void );


/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
}
#endif


#endif /* __FW_UPLOAD_H */