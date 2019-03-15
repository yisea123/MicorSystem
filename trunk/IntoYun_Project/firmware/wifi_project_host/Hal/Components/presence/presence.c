/** \file

$Id: presence.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
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
#include "log.h"

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "presence.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define RETRY                                     3

#define PRESENCE_DEBUGEN                          1

#if  PRESENCE_DEBUGEN
#define   presence_debug                          log_printf
#else
#define   presence_debug         
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static char presence_PkgId[] = " presence";

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static bool Presence_PacketPaeserID( Presence_TypeDef *pCtr_Presence );
static CTRL_RESULT_ENUM Presence_Checked_ID( Presence_TypeDef *pCtr_Presence );
static bool Presence_PacketPaeserValue( Presence_TypeDef *pCtr_Presence );
static CTRL_RESULT_ENUM Presence_Checked_Value( Presence_TypeDef *pCtr_Presence );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
CTRL_RESULT_ENUM vPresence_ReadValue( Presence_TypeDef *pCtr_Presence )
{
    CTRL_RESULT_ENUM res = CTRL_IDLE;

    switch( pCtr_Presence->step)
    {
        case PENSENCE_ID:
         res = Presence_Checked_ID( pCtr_Presence );
         if( res == CTRL_OK )
         {
            pCtr_Presence->step = PENSENCE_VALUE;
         }
         if( res == CTRL_FAIL )
         {
            return CTRL_FAIL;
         }
         break;
         
        case PENSENCE_VALUE:
         res = Presence_Checked_Value( pCtr_Presence );
         if( res == CTRL_OK )
         {
            return CTRL_OK;
         }
         if( res == CTRL_FAIL )
         {
            pCtr_Presence->step = PENSENCE_ID;
            return CTRL_FAIL;
         }         
         break;
    }

    return CTRL_IDLE;
}

CTRL_RESULT_ENUM ePresence_OnlyReadValue( Presence_TypeDef *pCtr_Presence )
{
    CTRL_RESULT_ENUM res = CTRL_IDLE;

         
    res = Presence_Checked_Value( pCtr_Presence );
    if( res == CTRL_OK || res == CTRL_FAIL )
    {
        pCtr_Presence->retry = 0;
    }       

    return res;
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static bool Presence_PacketPaeserID( Presence_TypeDef *pCtr_Presence )
{
     
    if( *pCtr_Presence->length > 3 )
    {
        if( pCtr_Presence->datapacket[0] == 'I' &&
            pCtr_Presence->datapacket[1] == 'D' &&
            pCtr_Presence->datapacket[2] == '=')
        {
             presence_debug( presence_PkgId,pCtr_Presence->datapacket, *pCtr_Presence->length); 
             for(int i = 0; i < *pCtr_Presence->length; i++ )
             {
                 if(pCtr_Presence->datapacket[3+i] != 0x0d )
                 {
                      pCtr_Presence->id[i] = pCtr_Presence->datapacket[3+i];
                 }
                 else
                 {
                      *pCtr_Presence->length = 0;
                      return true;
                 } 
             }
        }
        *pCtr_Presence->length = 0;
    }

    return false;
}

static CTRL_RESULT_ENUM Presence_Checked_ID( Presence_TypeDef *pCtr_Presence )
{
    uint8_t checkID_Cmd[] = "ID=?";

    if( Presence_PacketPaeserID( pCtr_Presence ))
        return CTRL_OK;
    else
    {
       *pCtr_Presence->length = 0;  
       if( pCtr_Presence->retry > RETRY )
       {
           pCtr_Presence->retry = 0;
           return CTRL_FAIL;
       }
       pCtr_Presence->retry++; 
       pCtr_Presence->pf_SendPut( checkID_Cmd, sizeof(checkID_Cmd));
       presence_debug( presence_PkgId,checkID_Cmd, sizeof(checkID_Cmd));
    }

    return CTRL_IDLE;
}

/*
  Presence status checked  VALUE
*/
static bool Presence_PacketPaeserValue( Presence_TypeDef *pCtr_Presence )
{
    if( *pCtr_Presence->length > 3 )
    {
        if( pCtr_Presence->datapacket[0] == 'I' &&
            pCtr_Presence->datapacket[1] == 'D' &&
            pCtr_Presence->datapacket[2] == '=')
        {
             for(int i = 0; i < *pCtr_Presence->length; i++)
             {
                 if(pCtr_Presence->datapacket[3+i] == 'B'&&
                    pCtr_Presence->datapacket[3+i+1] == 'T'&&
                    pCtr_Presence->datapacket[3+i+2] == '=')
                 {
                    pCtr_Presence->res = pCtr_Presence->datapacket[3+i+3]&0x0f;
                    presence_debug( presence_PkgId, pCtr_Presence->datapacket, *pCtr_Presence->length);
                    *pCtr_Presence->length = 0;
                    return true;
                 }
             }
        }
    }

    return false;
}

static CTRL_RESULT_ENUM Presence_Checked_Value( Presence_TypeDef *pCtr_Presence )
{
    uint8_t checkValue_Cmd[32];

    memset( checkValue_Cmd, 0, 32);
    sprintf( (char*)checkValue_Cmd,"ID=%s BT=?", pCtr_Presence->id);
    if( Presence_PacketPaeserValue( pCtr_Presence ))
        return CTRL_OK;
    else
    {
        *pCtr_Presence->length = 0;  
        if( pCtr_Presence->retry > RETRY )
        {
            pCtr_Presence->retry = 0;
            return CTRL_FAIL;
        }
        pCtr_Presence->retry++; 
        pCtr_Presence->pf_SendPut( checkValue_Cmd, sizeof(checkValue_Cmd));
        presence_debug( presence_PkgId, checkValue_Cmd, sizeof(checkValue_Cmd));
    }

    return CTRL_IDLE;
}

/* End of this files */
