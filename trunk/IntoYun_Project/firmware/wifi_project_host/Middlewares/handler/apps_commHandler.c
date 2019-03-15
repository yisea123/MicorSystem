/** \file

$Id: apps_commHandler.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "includes.h"
#include "user_Action.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define STR_BLUTOOTH                           st_Uart5
#define BLUETOOTH_SEND                         UART5_Put

#define STR_DEBUGPORT                          st_Uart3
#define DEBUGPORT_SEND                         UART3_Put

MCS MCS_RespBlueTooth;
MCS MCS_RespDebugPort;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/

void vApps_BlueToothActionInit( void )
{ 
    MCS *pst_mcs;

    pst_mcs = &MCS_RespBlueTooth;
    pst_mcs->pf_SendPut = BLUETOOTH_SEND;
    pst_mcs->CmdTable = (void *)BlueToothActionCmdTable;
    pst_mcs->CmdTotal =  BlueToothActionCmdTotal;
}

void vApps_DebugActionInit( void )
{ 
    MCS *pst_mcs;

    pst_mcs = &MCS_RespDebugPort;
    pst_mcs->pf_SendPut = DEBUGPORT_SEND;
    pst_mcs->CmdTable = (void *)BlueToothActionCmdTable;
    pst_mcs->CmdTotal = BlueToothActionCmdTotal;
}

void vApps_BlueToothActionHandler( void )
{
    UART *uart = &STR_BLUTOOTH; 
    MCS *pst_mcs = &MCS_RespBlueTooth;

    while(uart->u16_RxCnts >= 11 ) 
    {
        MCS_CommHandlerAction( pst_mcs, uart->u8_RxBuf);
        memset(uart, 0, sizeof(UART));
    }
}

void vApps_DebugPortActionHandler( void )
{
    UART *uart = &STR_DEBUGPORT; 
    MCS *pst_mcs = &MCS_RespDebugPort;

    while(uart->u16_RxCnts >= 11 ) 
    {
      MCS_CommHandlerAction( pst_mcs, uart->u8_RxBuf);
      memset(uart, 0, sizeof(UART));
    }
}

void apps_SendErrorCode( uint8_t *para, uint8_t len )
{
    MCS *pst_mcs;

    pst_mcs = &MCS_RespBlueTooth;
    pst_mcs->cmdCode = DEVICE_ERROR_CMD;
    pst_mcs->dataLength = len;
    for( int i = 0; i < len; i++)
    {
        pst_mcs->dataBuff[i]= para[i];
    }
    
    MCS_HostSendPacket( pst_mcs );   
}


static void apps_SystemConfig( MCS *pst_mcs )
{
    uint8_t buffer[32];
    uint8_t type;

    if( pst_mcs->cmdCode & MCS_READ )
    { 
        /* read project parameter */
        type = pst_mcs->dataBuff[0];
        Sys_InformationRead( type, pst_mcs->dataBuff, &pst_mcs->dataLength);
    }
    else
    {
        /* config project parameter */
        memcpy(buffer, pst_mcs->dataBuff, pst_mcs->dataLength);
        sys_InformationConfig(pst_mcs->dataBuff, pst_mcs->dataLength);    
    }
}

/* Command set table */
const MCS_CmdNode   BlueToothActionCmdTable[] = 
{
  DEVICE_CONFIG_CMD,     apps_SystemConfig,
};

const uint8_t BlueToothActionCmdTotal = dim(BlueToothActionCmdTable);

/* End of this file */

