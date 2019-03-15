/** \file

$Id: interface_light.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "board.h"
#include "usart.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "Interface_light.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define LIGHT_RETRY                         3

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static CtrlLight_lib st_CtrlLight_lib;
static CtrlLight_typedef st_CtrlLight;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vLight_CtrlInit( void )
{
    UART *pUart = &st_Uart2;

    st_CtrlLight_lib.pf_SendPut = HAL_485WriteSerial_Port2;
    st_CtrlLight_lib.length = &(pUart->u16_RxHead);
    st_CtrlLight_lib.datapacket = pUart->u8_RxBuf;
    vLight_Init( &st_CtrlLight_lib ); 
}

void vLight_SetPara(uint8_t id, uint8_t status, uint8_t wLuminance, uint8_t yLuminance )
{
    CtrlLight_typedef *pCtrlLight = &st_CtrlLight;
    
    pCtrlLight->bStatus = status;
    pCtrlLight->wLuminance = wLuminance;
    pCtrlLight->yLuminance = yLuminance;
    pCtrlLight->retry = 0;
    pCtrlLight->id = id;
}

CTRL_RESULT_ENUM eLight_CtrlInterface( void )
{
    CtrlLight_typedef *pCtrlLight = &st_CtrlLight;
    LightStatus_typedef *pLightStatus;

    pLightStatus = &st_CtrlLight_lib.st_LightCtr[pCtrlLight->id];
    if( pCtrlLight->bStatus )
    {
        /*
              white light
        */
        if( pCtrlLight->wLuminance == 0 )
        {
            pLightStatus->lightCtrlWhiteCmd.luminance= LIGHT_DEFAULT_LUM;
        }
        else
        {
            pLightStatus->lightCtrlWhiteCmd.luminance= pCtrlLight->wLuminance;
        }

        /*
               yellow light
        */
        if( pCtrlLight->yLuminance == 0 )
        {
            pLightStatus->lightCtrlYellowCmd.luminance= LIGHT_DEFAULT_LUM;
        }
        else
        {
            pLightStatus->lightCtrlYellowCmd.luminance= pCtrlLight->wLuminance;
        }
        
        vLight_ContrlTurnOn( &st_CtrlLight_lib,  pCtrlLight->id );
    }
    else
    {
        vLight_ContrlTurnOff(  &st_CtrlLight_lib,  pCtrlLight->id );
    }
    
    if( pCtrlLight->retry < LIGHT_RETRY)
    {
        pCtrlLight->retry++;
    }
    else
    {
        return CTRL_OK;
    }    

    return CTRL_IDLE;
}

/* End of this file */

