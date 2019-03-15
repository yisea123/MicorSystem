/** \file

$Id: user_kichen.c 40486 2018-09-23 18:30:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "board.h"
#include "motor_handler.h"
#include "usart.h"
#include "timer.h"
#include "apps_commHandler.h"
#include "log.h"
#include "Includes.h"
#include "Interface_kitchen.h"
#include "Interface_jdq.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "user_kitchen.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define KITCHEN_DEBUGEN           1
#define READDEV_ADD               JDQ_CH4_READADD

#if  KITCHEN_DEBUGEN
#define   kitchen_debug           log_printstring
#else
#define   kitchen_debug
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static uint8_t yunID = DPID_YUN_ID_NULL;
static uint32_t timer100msID;
static uint32_t timer300msID;
static bool b_run100Flag = false;
static CtrlJDQ_typedef st_CtrlJDQ;
static CtrlJDQ_typedef st_CtrlReadJDQ;

static char kitchen_PkgId[] = " kitchen";
/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void vUser_kitchenSet(  uint8_t id, uint8_t dir  );
static void vAppsCtrl_ReadJdqStatus( void );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vUserKitchen_Init( void )
{ 
    st_CtrlReadJDQ.st_JdqCtrlPara.SetAddress =  READDEV_ADD;
    st_CtrlReadJDQ.st_JdqCtrlPara.SetTotalChn  = 4;
    Ctrl_MotorKitchenInit();
    vCtrl_ResetKitchenMotor();

    vJdq_CtrlInit( &st_CtrlJDQ );
    vJdq_CtrlInit( &st_CtrlReadJDQ );
}

void vUserKitchen_SetDevicePara(uint8_t id, uint8_t type, uint8_t *dir )
{ 
    switch( id )
    {
      case DPID_YUN_ID_1: 
         if( type != KITCHEN_TYPE)
           return;
         break;

      default:
         break;
    }

    if( yunID == DPID_YUN_ID_NULL || dir[0] == DIR_STOP )
    {
       kitchen_debug( kitchen_PkgId, "reset dir value \r\n");
       vUser_kitchenSet( id, dir[0]);
       vCtrl_ResetKitchenMotor();
    }
}

void vUser_Kitchen_Process( void )
{
    CTRL_RESULT_ENUM e_res;

    if( yunID == DPID_YUN_ID_NULL )
    {
        if( timerIsEnd(timer300msID, 300))
        {
            vAppsCtrl_ReadJdqStatus();
            timer300msID = timerGetId();
        }
        return;
    }

    /*
         Enable timer
    */
    if( timerIsEnd(timer100msID, 100))
    {
        timer100msID = timerGetId();
        b_run100Flag = true;
    }

    switch( yunID ) 
    {
        /*
             kitchen control
        */
        case DPID_YUN_ID_1:
           if( b_run100Flag )
           {
                b_run100Flag = false;
                e_res = Ctrl_MotorKitchenInterface();
                if( e_res == CTRL_OK || e_res == CTRL_FAIL )
                { 
                     yunID = DPID_YUN_ID_NULL;
                }
            }
          break;

        default:
          yunID = DPID_YUN_ID_NULL;
          break;
    }
}

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void vAppsCtrl_ReadJdqStatus( void )
{
    CTRL_RESULT_ENUM e_res;
    uint8_t value_level, buff[1];

    e_res = jdq_ReadBoolValueHandler( &st_CtrlReadJDQ );
    if( e_res == CTRL_OK )
    {
         //kitchen
         value_level = st_CtrlReadJDQ.st_JdqCtrlPara.boolValue&0x03;
         if( value_level == 0x01 )   // kitchen up
         {
             buff[0]= DIR_UP;
             vUserKitchen_SetDevicePara( DPID_YUN_ID_1, KITCHEN_TYPE, buff );
         }
        else if( value_level == 0x02) // kitchen down
        {
             buff[0]= DIR_DOWN;
             vUserKitchen_SetDevicePara( DPID_YUN_ID_1, KITCHEN_TYPE, buff );
        }
    }
}

static void vUser_kitchenSet(  uint8_t id, uint8_t dir  )
{
    yunID = id;
    Ctrl_MotorKitchenStart( dir );
}

/* End of this file */
