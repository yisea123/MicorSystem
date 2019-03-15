/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmingfei2013@126.com
  *                                      All Rights Reserved
  * @file    apps_commHandler.c
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
#include "Includes.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define STR_DEBUGPORT                          st_Uart3
#define DEBUGPORT_SEND                         UART3_Put

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
MCS MCS_RespDebugPort;

/* Private function prototypes -----------------------------------------------*/

void vApps_DebugActionInit( void )
{ 
    MCS *pst_mcs;

    pst_mcs = &MCS_RespDebugPort;
    pst_mcs->pf_SendPut = DEBUGPORT_SEND;
    pst_mcs->CmdTable = (void *)AppActionCmdTable;
    pst_mcs->CmdTotal = AppActionCmdTotal;
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

static void apps_protocolRtc( MCS *pst_mcs )
{
    if( pst_mcs->dataLength == 6  )
    {
        RTC_Set(pst_mcs->dataBuff);
        pst_mcs->dataLength = 0;
    }
}

static void apps_protocolTest( MCS *pst_mcs )
{
    int len;
    uint8_t CtrCmd[128];
    
    memset(CtrCmd, 0, sizeof(CtrCmd));
    len = pst_mcs->dataLength;   
    
    if( len > 0 )
    {
        for( int i = 0; i < len; i++)
        {
            CtrCmd[i] = pst_mcs->dataBuff[i];
        }
    }
}

static void apps_FileDownLoad( MCS *pst_mcs )
{  
    uint16_t error_Code;
    
    if( pst_mcs->dataLength > 0 )
    {
        error_Code = AppFwUpdate_DownLoad(pst_mcs->dataBuff,
                                          pst_mcs->dataLength,
                                          pst_mcs->frumIndex);
        if( error_Code == ERR_PARAM )
        {
                pst_mcs->dataBuff[0] = error_Code>>8;
                pst_mcs->dataBuff[1] = error_Code;
                pst_mcs->dataLength = 2;
        }
        else
        {
                pst_mcs->dataLength = 0;
        }
    }
}

static void apps_UploadSht20( MCS *pst_mcs )
{
    uint16_t interVal;
    
    pst_mcs->dataLength = 0;
    interVal =  pst_mcs->dataBuff[0] << 8 | pst_mcs->dataBuff[1];
    UploadSht20_SetInterval( interVal );
}

void vApps_UploadSht20Value( int8_t *data )
{
    MCS *pst_mcs = &MCS_RespDebugPort;
    
    pst_mcs->dataBuff[0] = data[0];
    pst_mcs->dataBuff[1] = data[1];
    pst_mcs->dataBuff[2] = data[2];
    pst_mcs->dataBuff[3] = data[3];

    pst_mcs->dataLength = 4; 
    MCS_HostSendPacket( pst_mcs );
}

/* Command set table */
const MCS_CmdNode   AppActionCmdTable[] =
{
  PROTOCOL_RTC_CMD,        apps_protocolRtc,
  PROTOCOL_TEST_CMD,       apps_protocolTest,
  PROTOCOL_DOWNLOAD_CMD,   apps_FileDownLoad,
  PROTOCOL_SHT20_CMD,      apps_UploadSht20,
};

const uint8_t AppActionCmdTotal = dim(AppActionCmdTable);

/* End of this file */