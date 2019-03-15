/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    mcs_protocol.c
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
#include "mcs_protocol.h"
#include "Util.h"

static bool MCS_SearchCmd( MCS *pst_mcs, PFNCT_MCS* func );
static bool MCS_Builder(MCS *pst_mcs);
static bool MCS_ActionExecuter( MCS* pst_mcs );

bool MCS_CommHandlerAction( MCS *pst_mcs, uint8_t *srcbuff )
{
    uint8_t packetlen = 0;

    pst_mcs->dataLength = 0;
    if( srcbuff[PROTOCOL_HEADER_OFFSET] != '[')
       return false;

    packetlen++;

    pst_mcs->sourAddress = srcbuff[PROTOCOL_SOURADDR_OFFSET];
    packetlen++;

    pst_mcs->targetAddress = srcbuff[PROTOCOL_TARADDR_OFFSET];
    packetlen++;

    pst_mcs->frumIndex = (srcbuff[PROTOCOL_FUMN_OFFSET]<<8)|srcbuff[PROTOCOL_FUMN_OFFSET+1];
    packetlen += 2;

    pst_mcs->cmdCode = (srcbuff[PROTOCOL_CMD_OFFSET]<<8)|srcbuff[PROTOCOL_CMD_OFFSET+1];
    packetlen += 2;

    pst_mcs->dataLength = srcbuff[PROTOCOL_DATA_LENGTH_OFFSET];
    packetlen++;

    if( pst_mcs->dataLength > 0 )
    {
        memcpy( pst_mcs->dataBuff, srcbuff+PROTOCOL_DATA_OFFSET, pst_mcs->dataLength);
        packetlen += pst_mcs->dataLength;
    }

    if(UTL_blCheckCRC16(srcbuff,packetlen+2) == false)
    {
        return false ;
    }    
    
    if( srcbuff[packetlen+2] == ']')
    {
        MCS_SlaveExecuter( pst_mcs );
        return true; 
    }
 
    return false;
}

/*******************************************************************************
            Host action 
********************************************************************************/
bool MCS_HostSendPacket( MCS *pst_mcs )
{
    if( !MCS_Builder( pst_mcs ) == true ) 
    {
        return false;
    }
    
    return true;
}

/*******************************************************************************
            slave action 
********************************************************************************/
bool MCS_SlaveExecuter( MCS *pst_mcs )
{
    if(MCS_ActionExecuter( pst_mcs ))
    {
        //Refrsh command
        pst_mcs->cmdCode |= MCS_SUCESS;
    }
    else
    {
        pst_mcs->cmdCode &=~MCS_SUCESS;
    }
    /* Slave action */
    if( !MCS_Builder( pst_mcs ) == 1 ) 
    {
        return false;
    }
    
    return true;
}

/*******************************************************************************
            private function definition 
********************************************************************************/
/* return 1: support, 0: not support */
static bool MCS_SearchCmd( MCS *pst_mcs, PFNCT_MCS* func )
{
    uint16_t cmdCode; 
    uint16_t i;
    MCS_CmdNode* tptr;
    
    /* Search command set */
    tptr = (MCS_CmdNode *)pst_mcs->CmdTable;
    for( i=0; i<pst_mcs->CmdTotal; i++ ) 
    {
        cmdCode =  pst_mcs->cmdCode & CAL_CMD_CODE;
        if( cmdCode == (tptr+i)->command ) 
        {
            *func = (PFNCT_MCS)(tptr+i)->pf_FuncPtr;
            return true;
        }
    }
    return false;
}

static bool MCS_Builder(MCS *pst_mcs)
{
    uint16_t index = 0;
    uint16_t i=0;
    uint16_t crc;

    pst_mcs->HostSendBuf[index++] = '[';
    pst_mcs->HostSendBuf[index++] = pst_mcs->sourAddress;
    pst_mcs->HostSendBuf[index++] = pst_mcs->targetAddress;

    pst_mcs->HostSendBuf[index++] = pst_mcs->frumIndex>>8;
    pst_mcs->HostSendBuf[index++] = pst_mcs->frumIndex;

    pst_mcs->HostSendBuf[index++] = pst_mcs->cmdCode>>8;
    pst_mcs->HostSendBuf[index++] = pst_mcs->cmdCode;
    
    pst_mcs->HostSendBuf[index++] = pst_mcs->dataLength;

    if( pst_mcs->dataLength > 0 )
    {
      for( i = 0 ; i <pst_mcs->dataLength; i++  )
      {
          pst_mcs->HostSendBuf[index++] = pst_mcs->dataBuff[i];
      }
    }
    crc = UTL_ChkCrc16(  pst_mcs->HostSendBuf, index);

    pst_mcs->HostSendBuf[index++] = crc>>8;
    pst_mcs->HostSendBuf[index++] = crc;

    pst_mcs->HostSendBuf[index++] = ']';

    if( pst_mcs->pf_SendPut != NULL ) 
    {
        pst_mcs->pf_SendPut(  pst_mcs->HostSendBuf, index);
        return true; 
    } 
    
    return false;
}


/* return 1: support, 0: not support */
static bool MCS_ActionExecuter( MCS* pst_mcs )
{
    PFNCT_MCS fptr = NULL;

    if( MCS_SearchCmd(pst_mcs, &fptr ) == false ) 
    {
         goto exit;
    }
    
    if( fptr != NULL ) 
    {
        fptr( pst_mcs );
    }
    
    return( true );
    
exit:
    return( false );
}

/* End of this file */