/** \file

$Id: user_Action.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#include "includes.h"

#include "platform_def.h"
#include "Interface_dev.h"
#include "Interface_jdq.h"
#include "Interface_tv.h"
#include "Interface_light.h"
#include "Interface_presence.h"
#include "Interface_inclin.h"
#include "Interface_stair.h"
#include "user_Handler.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "user_Action.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define NULL_ID             0xff

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static CtrL_typedef st_CtrlTypdef;
static Inclin_typedef st_Inclin;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void vCtrlAction_Init( void );
static void vCtrlAction_SetPara(uint8_t dev_type ,uint8_t id, uint8_t *ctrlRes, uint8_t length );
static void vCtrlAction_Handler( void );

/******************************************************************************
* LOCAL FUNCTIONS IMPLEMENT
******************************************************************************/
static void vCtrlAction_Init( void )
{
    CtrL_typedef *pCtrlTypdef;

    pCtrlTypdef = &st_CtrlTypdef;
    
    vMotor_CtrlInit();
    vMotorTV_CtrlInit();
    vLight_CtrlInit();
    vClin_Init( &st_Inclin );
    vAppsCtrl_Init();   

    pCtrlTypdef->addres = NULL_ADDR;
    pCtrlTypdef->YunID = NULL_ID;
}

static void vCtrlAction_SetPara(uint8_t dev_type ,uint8_t id, uint8_t *ctrlRes, uint8_t length )
{
    CtrL_typedef *pCtrlTypdef;

    pCtrlTypdef = &st_CtrlTypdef;
    memcpy( pCtrlTypdef->b_ctrlres, ctrlRes, length);
    vCloud_RefreshCtrlStatus( id, ctrlRes, length);
    
    pCtrlTypdef->dev_type = dev_type;
    pCtrlTypdef->addres = NULL_ADDR;
    pCtrlTypdef->YunID = NULL_ID;
     
    vAppsCtrl_SetDevicePara( id, dev_type, pCtrlTypdef->b_ctrlres);
}

static void vCtrlAction_Handler( void )
{
    vAppsCtrl_Process();
}
/******************************************************************************
* EXPORT VARIABLES
******************************************************************************/
const vCtrlAction_t mainCtrl =
{
    vCtrlAction_Init,
    vCtrlAction_SetPara,
    vCtrlAction_Handler
};

/*End of this file */
