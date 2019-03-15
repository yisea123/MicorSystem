/** \file

$Id: Interface_tv.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "board.h"
#include "motor_handler.h"
#include "usart.h"
#include "timer.h"
#include "apps_commHandler.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "Interface_tv.h"
#include "Interface_local.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define      WAIT_COUNT                         50
#define      TV_MOTOR                           MOTOR_5 

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static MotorStatus_typedef st_MotorStatus; 
static uint8_t actionStep = MOTOR_RUNIDLE;
static uint8_t MotorunWait;
static monitor_infor st_Monitor;
static uint8_t MotorTvReadWait;
static CtrlMotor_typedef st_CtrlMotor;
static uint8_t dirRun;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res );
static CTRL_RESULT_ENUM eMotor_ReadStatus( CtrlMotor_typedef *pCtrlMotor );
static CTRL_RESULT_ENUM eMotor_WriteCmdStatus( CtrlMotor_typedef *pCtrlMotor,uint8_t dir);
static void vCtrlAction_TvError( void );

static void vMotor_CheckMotorControllerError( void );
static CTRL_RESULT_ENUM vMotor_CheckMotorSpeed( void );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vMotorTV_CtrlInit( void )
{
    CtrlMotor_typedef *pCtrlMotor = &st_CtrlMotor;
    UART *pUart = &st_Uart1;
    
    pCtrlMotor->pf_SendPut = HAL_485WriteSerial_Port1;
    pCtrlMotor->length = &(pUart->u16_RxHead);
    pCtrlMotor->datapacket = pUart->u8_RxBuf;
    actionStep = MOTOR_RUNIDLE;
}

void vCtrl_MotorTVStart( uint8_t dir  )
{
   actionStep = MOTOR_CHECKERROR;
   dirRun = dir;
   vMotor_ResetPara( &st_MotorStatus );
   MotorunWait = 0;
   MotorTvReadWait = 0;
}

CTRL_RESULT_ENUM eCtrl_MotorTVInterface( void )
{
   CTRL_RESULT_ENUM e_res;
   CtrlMotor_typedef *pCtrlMotor = &st_CtrlMotor;
  
   switch( actionStep )
   {
       case MOTOR_CHECKERROR:      //Check error
         e_res = eMotor_CtrlStatus( pCtrlMotor, true);
         if( e_res == CTRL_FAIL )
         {
             vMotor_CheckMotorControllerError();
             tim_SetTimIsr( TIMER2, vCtrlAction_TvError, 5);
             actionStep = MOTOR_STOPRUN;
         }
         if( e_res == CTRL_OK )
         {
            actionStep = MOTOR_WRITESPEED;
         }
         break;
         
       case MOTOR_WRITESPEED:      //Write speed
         e_res = eMotor_WriteCmdStatus( pCtrlMotor, dirRun );
         if( e_res == CTRL_FAIL )
         {
             vMotor_CheckMotorControllerError();
             tim_SetTimIsr( TIMER2, vCtrlAction_TvError, 5);
             actionStep = MOTOR_STOPRUN;
         }
         else if( e_res == CTRL_OK )
         {
             if( dirRun != DIR_STOP )
             {
                  actionStep = MOTOR_DELAY;
                  return CTRL_IDLE;
             }
             return CTRL_OK;
         }     
         break;
         
       case MOTOR_DELAY:            //Delay
         MotorunWait++;
         if( MotorunWait > WAIT_COUNT )
         {
            actionStep = MOTOR_READSTATUS;
            MotorunWait = 0;
         }     
         break;
         
       case MOTOR_READSTATUS:        //Read status;
         e_res = eMotor_ReadStatus( pCtrlMotor );
         if( e_res == CTRL_FAIL )
         {
             vMotor_CheckMotorControllerError();
             tim_SetTimIsr( TIMER2, vCtrlAction_TvError, 5);
             actionStep = MOTOR_STOPRUN;
         } 
         else if( e_res == CTRL_OK )
         {
             e_res = vMotor_CheckMotorSpeed();
             if( e_res == CTRL_FAIL )
             {
                 actionStep = MOTOR_STOPRUN;
             }
         }          
         break;
         
       case MOTOR_STOPRUN:          //Stop
          e_res = eMotor_CtrlStatus( pCtrlMotor, false);
          if( e_res == CTRL_OK )
          {
              actionStep = MOTOR_CHECKERROR;
              return CTRL_OK;
          }
         break;
         
       case MOTOR_POWEROFF:         //Power off 
         break;
         
       default:
         break;
   }
   
   return CTRL_IDLE;
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void  vCtrlAction_TvError( void )
{
    uint8_t buff[3];

    buff[0] =  TV_TYPE;
    buff[1] =  DPID_YUN_ID_5;
    buff[2] =  st_Monitor.PingTaiDevFlags;
    apps_SendErrorCode( buff, 3);
}

static void vMotor_CheckMotorControllerError( void )
{
    st_Monitor.TVDevFlags_bit.Motor_Ctrl = st_MotorStatus.Onlive;
}

static CTRL_RESULT_ENUM vMotor_CheckMotorSpeed( void )
{
    if( st_MotorStatus.speed == 0 )
    {
          MotorTvReadWait++;
          if( MotorTvReadWait > WAIT_COUNT)
              return CTRL_FAIL;
          else
              return CTRL_IDLE;
    }
    else
    {
          MotorTvReadWait = 0;
    }

    return  CTRL_OK;
}

static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res )
{
     CTRL_RESULT_ENUM e_res;
     
     pCtrlMotor->status = res;
     pCtrlMotor->pMotorStatus = &st_MotorStatus;
     e_res = vMotor_CtrlHandler( pCtrlMotor,  TV_MOTOR , DIR_STOP);
     if( e_res == CTRL_OK || e_res == CTRL_FAIL)
     {
          return CTRL_OK;
     }
     
     return CTRL_IDLE;
}

static CTRL_RESULT_ENUM eMotor_ReadStatus( CtrlMotor_typedef *pCtrlMotor )
{
     CTRL_RESULT_ENUM e_res;
     
     pCtrlMotor->status = true;
     pCtrlMotor->pMotorStatus = &st_MotorStatus;
     e_res = vMotor_CtrlHandler( pCtrlMotor,  TV_MOTOR , DIR_STOP);
     
     return e_res;
}

static CTRL_RESULT_ENUM eMotor_WriteCmdStatus( CtrlMotor_typedef *pCtrlMotor,  uint8_t dir )
{
     CTRL_RESULT_ENUM e_res;
     
     pCtrlMotor->status = false;
     pCtrlMotor->pMotorStatus = &st_MotorStatus;
     e_res = vMotor_CtrlHandler( pCtrlMotor,  TV_MOTOR , dir);

     return e_res;
}


/* End of this file */