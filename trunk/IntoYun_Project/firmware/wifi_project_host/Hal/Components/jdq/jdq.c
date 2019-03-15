/** \file

$Id: jdq.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "jdq.h"

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "util.h"
#include "log.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define JDQ_DEBUGEN          1

#if  JDQ_DEBUGEN
#define   jdq_debug          log_printf
#else
#define   jdq_debug         
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static char jdq_PkgId[] = " jdq";

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void jdq_SendCmd( CtrlJDQ_typedef *pJdq );
static bool jdq_ParserCmd( CtrlJDQ_typedef *pJdq );
static void jdq_CheckAnalValue( CtrlJDQ_typedef *pJdq );
static bool jdq_ParserAnalValue( CtrlJDQ_typedef *pJdq );
static void jdq_CheckBoolAnalValue( CtrlJDQ_typedef *pJdq );
static bool jdq_ParserBoolValue( CtrlJDQ_typedef *pJdq );

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void jdq_SendCmd( CtrlJDQ_typedef *pJdq )
{
    uint8_t Cmd[8] = {0x01,  0x05,  0,  0,  0,  0,  0,  0};
    uint8_t pkt_len;
    uint16_t crc;

    pkt_len = sizeof( Cmd );
    Cmd[0] = pJdq->st_JdqCtrlPara.SetAddress;       // address 
    
    Cmd[3] = pJdq->st_JdqCtrlPara.SetChannel;       //Contrl channel
    Cmd[4] = pJdq->st_JdqCtrlPara.SetStatus;
    
    //calcrute crc16
    crc = UTL_ChkCrc16( Cmd, 6);
    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 
    
    pJdq->pf_SendPut( Cmd, pkt_len);
    log_printf( jdq_PkgId, Cmd, pkt_len);
}

static void jdq_CheckAnalValue( CtrlJDQ_typedef *pJdq )
{
    uint8_t Cmd[8] = {0x01,  0x04,  0,  0,  0,  0x01,  0,  0};
    uint8_t pkt_len;
    uint16_t crc;

    pkt_len = sizeof( Cmd );
    Cmd[0] = pJdq->st_JdqCtrlPara.SetAddress;       // address 
    
    Cmd[3] = pJdq->st_JdqCtrlPara.SetChannel;       //Contrl channel    
    //calcrute crc16
    crc = UTL_ChkCrc16( Cmd, 6);
    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 

    pJdq->pf_SendPut( Cmd, pkt_len);
    
    log_printf( jdq_PkgId, Cmd, pkt_len);
}

static void jdq_CheckBoolAnalValue( CtrlJDQ_typedef *pJdq )
{
    uint8_t Cmd[8] = {0x01,  0x02,  0,  0,  0,  0x04,  0,  0};
    uint8_t pkt_len;
    uint16_t crc;

    pkt_len = sizeof( Cmd );
    Cmd[0] = pJdq->st_JdqCtrlPara.SetAddress;       // address 
    
    Cmd[3] = pJdq->st_JdqCtrlPara.SetChannel;       //Contrl channel 
    Cmd[5] = pJdq->st_JdqCtrlPara.SetTotalChn;       //total channel       
    //calcrute crc16
    crc = UTL_ChkCrc16( Cmd, 6);
    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 

    pJdq->pf_SendPut( Cmd, pkt_len);
    
    log_printf( jdq_PkgId, Cmd, pkt_len);
}

static bool jdq_ParserCmd( CtrlJDQ_typedef *pJdq )
{
    bool res = false;
    uint16_t crc, calCrc;

    if( *pJdq->length >= 8 )
    {
        //Check crc
        calCrc = pJdq->datapacket[6]<<8|pJdq->datapacket[7];
        crc = UTL_ChkCrc16( pJdq->datapacket, 6);
        if( calCrc == crc )
        { 
            pJdq->st_JdqCtrlPara.GetAddress = pJdq->datapacket[0];
            pJdq->st_JdqCtrlPara.GetChannel = pJdq->datapacket[3];
            pJdq->st_JdqCtrlPara.GetStatus =  pJdq->datapacket[4];
            res = true;
        }
        log_printf( jdq_PkgId, pJdq->datapacket, *pJdq->length);
        *pJdq->length = 0;
    }
    
    return res;
}


static bool jdq_ParserAnalValue( CtrlJDQ_typedef *pJdq )
{
    bool res = false;
    uint16_t crc, calCrc;

    if( *pJdq->length >= 7 )
    {
        *pJdq->length = 0;
        //Check crc
        calCrc = pJdq->datapacket[5]<<8|pJdq->datapacket[6];
        crc = UTL_ChkCrc16( pJdq->datapacket, 5);
        if( calCrc == crc )
        { 
            pJdq->st_JdqCtrlPara.GetAddress = pJdq->datapacket[0];
            pJdq->st_JdqCtrlPara.analValue = pJdq->datapacket[3]<<8|pJdq->datapacket[4];
            res = true;
        }
    }
    
    return res;
}

static bool jdq_ParserBoolValue( CtrlJDQ_typedef *pJdq )
{
    bool res = false;
    uint16_t crc, calCrc;

    if( *pJdq->length >= 6 )
    {
        *pJdq->length = 0;
        //Check crc
        calCrc = pJdq->datapacket[4]<<8|pJdq->datapacket[5];
        crc = UTL_ChkCrc16( pJdq->datapacket, 4);
        if( calCrc == crc )
        { 
            pJdq->st_JdqCtrlPara.GetAddress = pJdq->datapacket[0];
            pJdq->st_JdqCtrlPara.boolValue = pJdq->datapacket[3];
            res = true;
        }
    }
    
    return res;
}


CTRL_RESULT_ENUM jdq_Handler( CtrlJDQ_typedef *pJdq )
{
    bool res = false; 
    
    res = jdq_ParserCmd( pJdq );
    if( res )
    {
        //check address
        if(  pJdq->st_JdqCtrlPara.SetAddress == pJdq->st_JdqCtrlPara.GetAddress )
        {
            pJdq->st_JdqCtrlPara.Onlive = true;
            pJdq->st_JdqCtrlPara.SendCmdCnt = 0;
            return CTRL_OK;
        }
    }
    else
    {
        jdq_SendCmd( pJdq );
        pJdq->st_JdqCtrlPara.SendCmdCnt++;     
        if(  pJdq->st_JdqCtrlPara.SendCmdCnt > JDQ_RUNWRITE )
        {
            pJdq->st_JdqCtrlPara.Onlive = false;
            pJdq->st_JdqCtrlPara.SendCmdCnt = 0;
            return CTRL_FAIL;
        }
    }
      
    return CTRL_IDLE;
}


CTRL_RESULT_ENUM jdq_ReadAnalValueHandler( CtrlJDQ_typedef *pJdq )
{
    bool res = false; 
    
    res = jdq_ParserAnalValue( pJdq );
    if( res )
    {
        if( pJdq->st_JdqCtrlPara.SetAddress == pJdq->st_JdqCtrlPara.GetAddress )
        {
            pJdq->st_JdqCtrlPara.Onlive = true;
            pJdq->st_JdqCtrlPara.SendCmdCnt = 0;
            return CTRL_OK;
        }
    }
    else
    {
        jdq_CheckAnalValue( pJdq );
        pJdq->st_JdqCtrlPara.SendCmdCnt++;     
        if( pJdq->st_JdqCtrlPara.SendCmdCnt > JDQ_RUNWRITE )
        {
            pJdq->st_JdqCtrlPara.Onlive = false;
            pJdq->st_JdqCtrlPara.SendCmdCnt = 0;
            return CTRL_FAIL;
        }
    }
      
    return CTRL_IDLE;
}

CTRL_RESULT_ENUM jdq_ReadBoolValueHandler( CtrlJDQ_typedef *pJdq )
{
    bool res = false; 
    
    res = jdq_ParserBoolValue( pJdq );
    if( res )
    {
        if( pJdq->st_JdqCtrlPara.SetAddress == pJdq->st_JdqCtrlPara.GetAddress )
        {
            pJdq->st_JdqCtrlPara.Onlive = true;
            pJdq->st_JdqCtrlPara.SendCmdCnt = 0;
            return CTRL_OK;
        }
    }
    else
    {
        jdq_CheckBoolAnalValue( pJdq );
        pJdq->st_JdqCtrlPara.SendCmdCnt++;     
        if( pJdq->st_JdqCtrlPara.SendCmdCnt > JDQ_RUNWRITE )
        {
            pJdq->st_JdqCtrlPara.Onlive = false;
            pJdq->st_JdqCtrlPara.SendCmdCnt = 0;
            return CTRL_FAIL;
        }
    }
      
    return CTRL_IDLE;
}

/* End of this file */
