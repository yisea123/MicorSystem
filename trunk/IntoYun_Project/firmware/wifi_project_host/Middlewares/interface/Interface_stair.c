/** \file

$Id: Interface_stair.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#include "usart.h"
#include "timer.h"
#include "apps_commHandler.h"
#include "motor_handler.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "Interface_jdq.h"
#include "Interface_stair.h"
#include "Interface_local.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define      WAIT_COUNT                        50
#define      STAIR_MOTOR                       MOTOR_6 

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static MotorStatus_typedef st_MotorStatus; 
static uint8_t actionStep = MOTOR_RUNIDLE;
static uint8_t stairActionStep = MOTOR_RUNIDLE;
static uint8_t MotoRunWait;
static monitor_infor st_Monitor;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res );
static CTRL_RESULT_ENUM eMotor_ReadStatus( CtrlMotor_typedef *pCtrlMotor );
static CTRL_RESULT_ENUM eMotor_WriteCmdStatus( CtrlMotor_typedef *pCtrlMotor,uint8_t dir);
static CTRL_RESULT_ENUM eMotor_CheckMotorSpeed( void );
static CTRL_RESULT_ENUM eMotor_CtrlStairStepOne( CtrlMotor_typedef *pCtrlMotor , uint8_t dir);
static CTRL_RESULT_ENUM eStair_Open( CtrlMotor_typedef *pCtrlMotor, CtrlJDQ_typedef *pJDQ_typedef, CtrL_typedef *pCtrL_typedef);
static CTRL_RESULT_ENUM eStair_Close( CtrlMotor_typedef *pCtrlMotor,CtrlJDQ_typedef *pJDQ_typedef, CtrL_typedef *pCtrL_typedef);

static void vMotor_CheckMotorControllerError( void );
static void vMotor_CheckMotorErrorBySpeed( void );
static void vMotor_StatusError( void );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vStair_Init( CtrlMotor_typedef *pCtrlMotor )
{
    UART *pUart = &st_Uart1;
    
    pCtrlMotor->pf_SendPut = HAL_485WriteSerial_Port1;
    pCtrlMotor->length = &(pUart->u16_RxHead);
    pCtrlMotor->datapacket = pUart->u8_RxBuf;
    actionStep = MOTOR_RUNIDLE;
    stairActionStep = 0;
}

void vStair_CtrlStart( void )
{
    actionStep = MOTOR_CHECKERROR;
    stairActionStep = 0;
}

CTRL_RESULT_ENUM eStair_CtrlInterface( CtrlMotor_typedef *pCtrlMotor,
                                       CtrlJDQ_typedef *pJDQ_typedef,
                                       CtrL_typedef *pCtrL_typedef)                                              
{
    return CTRL_IDLE;
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static CTRL_RESULT_ENUM eStair_Open( CtrlMotor_typedef *pCtrlMotor,
                                    CtrlJDQ_typedef *pJDQ_typedef,
                                    CtrL_typedef *pCtrL_typedef)
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    
    switch( stairActionStep )
    {
       case 0:
        e_res = eMotor_CtrlStairStepOne( pCtrlMotor, STAIR_OPEN );
        if( e_res == CTRL_OK)
        {
           pCtrL_typedef->b_ctrlres[0] = STAIR_OPEN;
        }
        else if( e_res == CTRL_FAIL )
        {
          return CTRL_FAIL;
        }
        break;

        case 1:
           e_res = eJDQ_CtrlInterface( pJDQ_typedef,1);
           if( e_res == CTRL_OK )
           {
               return CTRL_OK;
           }
           else if( e_res == CTRL_FAIL )
           {
               return CTRL_FAIL;
           }        
         break;
    }

    return CTRL_IDLE;
}


static CTRL_RESULT_ENUM eStair_Close( CtrlMotor_typedef *pCtrlMotor,
                                    CtrlJDQ_typedef *pJDQ_typedef,
                                    CtrL_typedef *pCtrL_typedef)
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    
    switch( stairActionStep )
    {
        case 0:
           stairActionStep = 1;
           pCtrL_typedef->b_ctrlres[0] = STAIR_CLOSE;
        break;
        
        case 1:
           e_res = eJDQ_CtrlInterface( pJDQ_typedef,1 );
           if( e_res == CTRL_OK )
           {
               stairActionStep = 2;
           }
           else if( e_res == CTRL_FAIL )
           {
               return CTRL_FAIL;
           }        
       break;

       case 2:
        e_res = eMotor_CtrlStairStepOne( pCtrlMotor, STAIR_CLOSE );
        if( e_res == CTRL_OK)
        {
            return CTRL_OK;
        }
        else if( e_res == CTRL_FAIL )
        {
          return CTRL_FAIL;
        }
        break;

    }

    return CTRL_IDLE;
}


static CTRL_RESULT_ENUM eMotor_CtrlStairStepOne( CtrlMotor_typedef *pCtrlMotor , uint8_t dir  )
{
    CTRL_RESULT_ENUM e_res;

    switch( actionStep )
    {
       case MOTOR_CHECKERROR:      //Check error
         e_res = eMotor_CtrlStatus( pCtrlMotor, true);
         if( e_res == CTRL_FAIL )
         {
             vMotor_CheckMotorControllerError();
             tim_SetTimIsr( TIMER2, vMotor_StatusError, 5);
             actionStep = MOTOR_STOPRUN;
         }
         else if( e_res == CTRL_OK )
         {
            actionStep = MOTOR_WRITESPEED;
         }
         break;
         
       case MOTOR_WRITESPEED:      //Write speed
         e_res = eMotor_WriteCmdStatus( pCtrlMotor, dir );
         if( e_res == CTRL_FAIL )
         {
             vMotor_CheckMotorControllerError();
             tim_SetTimIsr( TIMER2, vMotor_StatusError, 5);
             actionStep = MOTOR_STOPRUN;
         }
         else if( e_res == CTRL_OK )
         {
             if( dir != DIR_STOP )
             {
                  MotoRunWait = 0;
                  actionStep = MOTOR_READSTATUS;
                  return CTRL_IDLE;
             }
             return CTRL_OK;
         }     
         break;
         
       case MOTOR_READSTATUS:        //Read status;
         MotoRunWait++;
         if( MotoRunWait < WAIT_COUNT )
           return  CTRL_IDLE;
           
         MotoRunWait = WAIT_COUNT;
         e_res = eMotor_ReadStatus( pCtrlMotor );
         if( e_res == CTRL_FAIL )
         {
             vMotor_CheckMotorControllerError();
             tim_SetTimIsr( TIMER2, vMotor_StatusError, 5);
             actionStep = MOTOR_STOPRUN;
         } 
         else if( e_res == CTRL_OK )
         {
             e_res = eMotor_CheckMotorSpeed();
             if( e_res == CTRL_FAIL )
             {
                 vMotor_CheckMotorErrorBySpeed();
                 tim_SetTimIsr( TIMER2, vMotor_StatusError, 5);
                 actionStep = MOTOR_STOPRUN;
             }
         }          
         break;
         
       case MOTOR_STOPRUN:          //Stop
          e_res = eMotor_CtrlStatus( pCtrlMotor, false);
          if( e_res == CTRL_OK )
          {
              actionStep = MOTOR_RUNIDLE;
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

static void  vMotor_StatusError( void )
{
    uint8_t buff[3];

    buff[0] =  TV_TYPE;
    buff[1] =  DPID_YUN_ID_8;
    buff[2] =  st_Monitor.PingTaiDevFlags;
    apps_SendErrorCode( buff, 3);
}

static void vMotor_CheckMotorErrorBySpeed( void )
{
    st_Monitor.TVDevFlags_bit.Motor = st_MotorStatus.speed > 0 ? true : false;
}

static void vMotor_CheckMotorControllerError( void )
{
    st_Monitor.TVDevFlags_bit.Motor_Ctrl = st_MotorStatus.Onlive;
}

static CTRL_RESULT_ENUM eMotor_CheckMotorSpeed( void )
{
    if( st_MotorStatus.speed == 0 )
    {
          return CTRL_FAIL;
    }
    
    return  CTRL_OK;
}

static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res )
{
     CTRL_RESULT_ENUM e_res;
     
     pCtrlMotor->status = res;
     pCtrlMotor->pMotorStatus = &st_MotorStatus;
     e_res = vMotor_CtrlHandler( pCtrlMotor,  STAIR_MOTOR , DIR_STOP);
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
     e_res = vMotor_CtrlHandler( pCtrlMotor,  STAIR_MOTOR , DIR_STOP);
     if( e_res == CTRL_OK )
     {
          if( pCtrlMotor->pMotorStatus->speed == 0 )
          {
             return CTRL_FAIL;
          }
     }
     else if( e_res == CTRL_FAIL )
     {
          return CTRL_FAIL;
     }
            
     return CTRL_IDLE;
}

static CTRL_RESULT_ENUM eMotor_WriteCmdStatus( CtrlMotor_typedef *pCtrlMotor,  uint8_t dir )
{
     CTRL_RESULT_ENUM e_res;
     
     pCtrlMotor->status = false;
     pCtrlMotor->pMotorStatus = &st_MotorStatus;
     e_res = vMotor_CtrlHandler( pCtrlMotor,  STAIR_MOTOR , dir);
     if( e_res == CTRL_OK )
     {
          return CTRL_OK;
     }
     else if( e_res == CTRL_FAIL )
     {
          return CTRL_FAIL;
     }
               
     return CTRL_IDLE;
}


/* End of this file */

