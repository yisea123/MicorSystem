/** \file

$Id: light.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

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

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "light.h"
#include "log.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define LIGHT_DEBUGEN           1

#if  LIGHT_DEBUGEN
#define   light_debug          log_printf       
#else
#define   light_debug         
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static char light_PkgId[] = " light";

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
void vLight_Init( CtrlLight_lib *pCtrlLight )
{
    LightStatus_typedef *pCtrl;
    uint8_t i;

    for( i = 0; i < MAX_LIGHT_SUPPORT; i++ )
    {
        pCtrl = &pCtrlLight->st_LightCtr[i]; 
        memset( pCtrl->uid, 0, 5);
        pCtrl->uid[0] = 0x1a;
        pCtrl->uid[4] = i+1;
    }
}

void vLight_ContrlTurnOff( CtrlLight_lib *pCtr, int index  )
{
    LightStatus_typedef *pCtrlLight;
       
    pCtrlLight = &pCtr->st_LightCtr[index];
    
    pCtrlLight->lightCtrlWhiteCmd.mode = LIGHT_ONLY_OFF;
    pCtrlLight->lightCtrlYellowCmd.mode = LIGHT_ONLY_OFF;

    pCtrlLight->lightCtrlWhiteCmd.b_ctrlres = LIGHT_CTRL_ENABLE;
    pCtrlLight->lightCtrlYellowCmd.b_ctrlres = LIGHT_CTRL_ENABLE;

    pCtrlLight->lightCtrlWhiteCmd.luminance = 0;
    pCtrlLight->lightCtrlYellowCmd.luminance = 0;

    vLight_ContrlCmd( pCtr, index );
}

void vLight_ContrlTurnOn( CtrlLight_lib *pCtr, int index )
{
    LightStatus_typedef *pCtrlLight;
       
    pCtrlLight = &pCtr->st_LightCtr[index];
    
    pCtrlLight->lightCtrlWhiteCmd.mode = LIGHT_DIMMING;
    pCtrlLight->lightCtrlYellowCmd.mode = LIGHT_DIMMING;

    pCtrlLight->lightCtrlWhiteCmd.b_ctrlres = LIGHT_CTRL_ENABLE;
    pCtrlLight->lightCtrlYellowCmd.b_ctrlres = LIGHT_CTRL_ENABLE;

    //pCtrlLight->lightCtrlWhiteCmd.luminance = LIGHT_DEFAULT_LUM;
    //pCtrlLight->lightCtrlYellowCmd.luminance = LIGHT_DEFAULT_LUM;

    vLight_ContrlCmd( pCtr, index  );
}

void vLight_CheckStatus( CtrlLight_lib *pCtr, int index )
{
    uint8_t buff[16];
    uint8_t length = 0;
    LightStatus_typedef *pCtrlLight;
       
    pCtrlLight = &pCtr->st_LightCtr[index];
     
    for( uint8_t j = 0; j < 5; j++ )
    {
        buff[length++] = pCtrlLight->uid[j];
    }

    buff[length++] = LIGHT_CHECK_STATUS;
    buff[length++] = LIGHT_CHECK_STATUS;
    buff[length++] = LIGHT_CHECK_STATUS;

    buff[length++] = LIGHT_END_PACKET;

    pCtr->pf_SendPut( buff , length );
}


void vLight_ContrlCmd( CtrlLight_lib *pCtr, int index )
{
    LightStatus_typedef *pCtrlLight;
    uint8_t buff[16];
    uint8_t length = 0;

    pCtrlLight = &pCtr->st_LightCtr[index];
    for( uint8_t j = 0; j < 5; j++ )
    {
      buff[length++] = pCtrlLight->uid[j];
    }

    buff[length++] = pCtrlLight->lightCtrlWhiteCmd.mode;
    buff[length++] = pCtrlLight->lightCtrlWhiteCmd.luminance;
    buff[length++] = pCtrlLight->lightCtrlWhiteCmd.b_ctrlres;

    buff[length++] = pCtrlLight->lightCtrlYellowCmd.mode;
    buff[length++] = pCtrlLight->lightCtrlYellowCmd.luminance;
    buff[length++] = pCtrlLight->lightCtrlYellowCmd.b_ctrlres;

    buff[length++] = LIGHT_END_PACKET;

    pCtr->pf_SendPut( buff , length );
    
    light_debug( light_PkgId, buff, length);
}


/* End of this file */