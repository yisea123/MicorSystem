/** \file

$Id: inclination.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

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
#include "inclination.h"

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "util.h"

#define JDRETRY                             5

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static bool Inclin_ParserPacket(  Inclin_typedef *pCtrL );
static void Inclin_SendHeaderCmd( Inclin_typedef *pCtrL );
static void Inclin_ReadValueCmd( Inclin_typedef *pCtrL );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
CTRL_RESULT_ENUM Inclin_ReadValue( Inclin_typedef *pCtrL )
{
    bool b_ReadValueStart = false;
    switch( pCtrL->step )
    {
        case 0:
            Inclin_SendHeaderCmd( pCtrL );
            if( pCtrL->retry < JDRETRY )
            {
                pCtrL->retry++;
            }
            else
            {
                pCtrL->step = 1;
                pCtrL->retry = 0;
            }
        break;

        case 1:
            b_ReadValueStart = true;
        break;

        default:
        return CTRL_FAIL;
    }
     
    if( b_ReadValueStart )
    {
        b_ReadValueStart = false;
        if( Inclin_ParserPacket( pCtrL ))
        {
            pCtrL->retry = 0;
            pCtrL->step = 1;
            return CTRL_OK;
        }
        else
        {
            if( pCtrL->retry > JDRETRY)
            {
                pCtrL->step = 0xff;
                pCtrL->retry = 0;
                return CTRL_FAIL;
            }
            
            Inclin_ReadValueCmd( pCtrL );
            pCtrL->retry++;
        }
    }

    return CTRL_IDLE;
}

void vInclin_Reset( Inclin_typedef *pCtrL )
{
    pCtrL->step = 0;
    pCtrL->retry = 0;
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void Inclin_SendHeaderCmd( Inclin_typedef *pCtrL )
{
    uint8_t Cmd[11] = { 0xC0, 0x65, 0x03, 0x04, 0, 0, 0, 0, 0, 0, 0xC0 };

    pCtrL->pf_SendPut( Cmd, sizeof(Cmd));
}

static void Inclin_ReadValueCmd( Inclin_typedef *pCtrL )
{
    uint8_t Cmd[8] = { 0x02, 0x03, 0, 0x5D, 0, 0x02, 0x55, 0xEA };
    uint16_t crc;

    Cmd[0] = pCtrL->address;       //485 address

    //calcrate crc16
    crc = UTL_ChkCrc16( Cmd, 6);
    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 

    pCtrL->pf_SendPut( Cmd, sizeof(Cmd));
}

static bool Inclin_ParserPacket(  Inclin_typedef *pCtrL )
{
    uint16_t crc, calCrc;

    if( *pCtrL->length >= 8 )
    {
        *pCtrL->length = 0;
        //Check crc
        calCrc = pCtrL->datapacket[7]<<8|pCtrL->datapacket[8];
        crc = UTL_ChkCrc16( pCtrL->datapacket, 7);
        if( calCrc == crc )
        {
          if( pCtrL->address == pCtrL->datapacket[0] )
          {
              pCtrL->x_value =  (int)(pCtrL->datapacket[3] << 8 | pCtrL->datapacket[4]);
              pCtrL->y_value =  (int)(pCtrL->datapacket[5] << 8 | pCtrL->datapacket[6]);
              return true;
          }
          else
            return false;
        }
    }

    return false;
}


/* End of this file */
