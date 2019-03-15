/** \file

$Id: interface_dev.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#include "motor_handler.h"
#include "usart.h"
#include "timer.h"
#include "apps_commHandler.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "Interface_dev.h"
#include "Interface_local.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define SNDCMD_MAXCNT             5
#define DELAY_MAXTIME             200

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static MotorStatus_typedef st_MotorStatus1;
static MotorStatus_typedef st_MotorStatus2;
static MotorStatus_typedef st_MotorStatus3;
static MotorStatus_typedef st_MotorStatus4;
static CtrlMotor_typedef st_CtrlMotor;

static uint8_t motorRunStep = MOTOR_1;
static uint8_t actionStep = MOTOR_RUNIDLE;
static uint8_t delayTime = 0;
static uint8_t dirRun;
static monitor_infor st_Monitor;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void vMotor_SetStatus( CtrlMotor_typedef *pCtrlMotor,  CTRL_RESULT_ENUM e_res );
static void vMotor_CheckMotorControllerError( void );
static void vMotor_CtrlActionLevelError( void );
static void vMotor_Reset( void );

static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res );
static CTRL_RESULT_ENUM eMotor_ReadStatus( CtrlMotor_typedef *pCtrlMotor );
static CTRL_RESULT_ENUM eMotor_WriteCmdStatus( CtrlMotor_typedef *pCtrlMotor,  uint8_t dir );
//static CTRL_RESULT_ENUM eMotor_CheckMotorSpeed( void );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vMotor_CtrlInit( void )
{
    CtrlMotor_typedef *pCtrlMotor = &st_CtrlMotor;
    UART *pUart = &st_Uart1;
    
    pCtrlMotor->pf_SendPut = HAL_485WriteSerial_Port1;
    pCtrlMotor->length = &(pUart->u16_RxHead);
    pCtrlMotor->datapacket = pUart->u8_RxBuf;
    actionStep = MOTOR_RUNIDLE;
    vMotor_Reset();
}

void vCtrl_MotorStart( uint8_t dir  )
{
    delayTime = 0;
    dirRun  = dir;
    actionStep = MOTOR_CHECKERROR;
    vMotor_Reset();
}

void vCtrl_MotorSetActStep( uint8_t step )
{
    actionStep = step;
    vMotor_Reset();
}

CTRL_RESULT_ENUM eCtrl_MotorInterface( void )
{
    CTRL_RESULT_ENUM e_res;
    CtrlMotor_typedef *pCtrlMotor = &st_CtrlMotor;
  
    switch( actionStep )
    {
        case MOTOR_CHECKERROR:   //Check motor controller status
            e_res = eMotor_CtrlStatus( pCtrlMotor, true);
            if( e_res != CTRL_IDLE )
            {
                vMotor_Reset();
                if( e_res == CTRL_FAIL )
                {
                    vMotor_CheckMotorControllerError();
                    tim_SetTimIsr( TIMER2, vMotor_CtrlActionLevelError, SNDCMD_MAXCNT);
                    actionStep = MOTOR_STOPRUN;
                }
                else if( e_res == CTRL_OK )
                {
                    actionStep = MOTOR_WRITESPEED;
                }
            }
        break;
         
        case MOTOR_WRITESPEED:   //Write speed
           e_res = eMotor_WriteCmdStatus( pCtrlMotor, dirRun );
           if( e_res != CTRL_IDLE )
           {
                vMotor_Reset();
                if( e_res == CTRL_FAIL )
                {
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
            }
        break;
         
        case MOTOR_DELAY:
            delayTime++;
            if( delayTime < DELAY_MAXTIME )
                return  CTRL_IDLE;
            delayTime = 0;
            actionStep = MOTOR_READSTATUS;
        break;
         
        case MOTOR_READSTATUS:            //Read status
            e_res = eMotor_ReadStatus( pCtrlMotor );
            if( e_res != CTRL_IDLE )
            {
                if( e_res == CTRL_FAIL )
                {   
                    vMotor_CheckMotorControllerError();
                    tim_SetTimIsr( TIMER2, vMotor_CtrlActionLevelError, SNDCMD_MAXCNT);
                    actionStep = MOTOR_STOPRUN;
                }
                else if( e_res == CTRL_OK )
                {
                    if( dirRun == DIR_DOWN )
                    {
                           e_res = eMotor_CheckMotorSqr2();
                    }
                    else if( dirRun == DIR_UP )
                    {
                          e_res = eMotor_CheckMotorSqr1();
                    }
                    if( e_res == CTRL_OK )
                    {
                        actionStep = MOTOR_STOPRUN;
                    }
                }
            }
        break;
         
        case MOTOR_STOPRUN:           //Stop
            e_res = eMotor_CtrlStatus( pCtrlMotor, false);
            if( e_res == CTRL_OK )
            {
                actionStep = MOTOR_RUNIDLE;
                return CTRL_OK;
            }
        break;
         
        case MOTOR_POWEROFF:     //Power off 
        break;
         
        default:
        break;
    }
   
    return CTRL_IDLE;
}

CTRL_RESULT_ENUM eMotor_CheckMotorSqr2( void )
{
    if( st_MotorStatus1.sqr_2 == 0 && st_MotorStatus2.sqr_2 == 0 &&
        st_MotorStatus3.sqr_2 == 0 && st_MotorStatus4.sqr_2 == 0)
    {
        return CTRL_OK;
    }
    
    return  CTRL_IDLE;
}

CTRL_RESULT_ENUM eMotor_CheckMotorSqr1( void )
{
    if( st_MotorStatus1.sqr_1 == 0 && st_MotorStatus2.sqr_1 == 0 &&
        st_MotorStatus3.sqr_1 == 0 && st_MotorStatus4.sqr_1 == 0)
    {
        return CTRL_OK;
    }
    
    return  CTRL_IDLE;
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void vMotor_Reset( void )
{
    motorRunStep = MOTOR_1;
    vMotor_ResetPara( &st_MotorStatus1 );
    vMotor_ResetPara( &st_MotorStatus2 );
    vMotor_ResetPara( &st_MotorStatus3 );
    vMotor_ResetPara( &st_MotorStatus4 );
}

static void  vMotor_CtrlActionLevelError( void )
{
    uint8_t buff[3];

    buff[0] =  LIVE_TYPE;
    buff[1] =  DPID_YUN_ID_7;
    buff[2] =  st_Monitor.PingTaiDevFlags;
    apps_SendErrorCode( buff, 3);
}

static void vMotor_CheckMotorControllerError( void )
{
    st_Monitor.PingTaiDevFlags_bit.Motor_1_Ctrl = st_MotorStatus1.Onlive;
    st_Monitor.PingTaiDevFlags_bit.Motor_2_Ctrl = st_MotorStatus2.Onlive;
    st_Monitor.PingTaiDevFlags_bit.Motor_3_Ctrl = st_MotorStatus3.Onlive;
    st_Monitor.PingTaiDevFlags_bit.Motor_4_Ctrl = st_MotorStatus4.Onlive;
}

#if 0
static CTRL_RESULT_ENUM eMotor_CheckMotorSpeed( void )
{
    if( st_MotorStatus1.speed == 0 && st_MotorStatus2.speed == 0 &&
        st_MotorStatus3.speed == 0 && st_MotorStatus4.speed == 0)
    {
        return CTRL_OK;
    }
    
    return  CTRL_IDLE;
}
#endif

static void vMotor_SetStatus( CtrlMotor_typedef *pCtrlMotor,  CTRL_RESULT_ENUM e_res )
{
    if( e_res == CTRL_OK )
    {
        pCtrlMotor->pMotorStatus->Onlive = true;
    }
    else if( e_res == CTRL_FAIL)
    {
        pCtrlMotor->pMotorStatus->Onlive = false;
    }
}

/*
  res = TRUE , read motor paramater
  res = false, send stop paramater
*/
static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res )
{
    CTRL_RESULT_ENUM e_res;

    pCtrlMotor->status = res;   /* read or write */
    switch( motorRunStep )
    {
        case MOTOR_1:
        default:
            pCtrlMotor->pMotorStatus = &st_MotorStatus1;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_1 , DIR_STOP);
            if( e_res == CTRL_OK || e_res == CTRL_FAIL)
            {
                motorRunStep = MOTOR_2;
                vMotor_SetStatus( pCtrlMotor, e_res);
            }
        break;
           
            case MOTOR_2:
            pCtrlMotor->pMotorStatus = &st_MotorStatus2;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_2 , DIR_STOP);
            if( e_res == CTRL_OK || e_res == CTRL_FAIL)
            {
                motorRunStep = MOTOR_3;
                vMotor_SetStatus( pCtrlMotor, e_res);
            }       
        break;
           
        case MOTOR_3:
            pCtrlMotor->pMotorStatus = &st_MotorStatus3;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_3 , DIR_STOP);
            if( e_res == CTRL_OK || e_res == CTRL_FAIL)
            {
                motorRunStep = MOTOR_4;
                vMotor_SetStatus( pCtrlMotor, e_res);
            }
        break;
           
        case MOTOR_4:
            pCtrlMotor->pMotorStatus = &st_MotorStatus4;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_4 , DIR_STOP);
            if( e_res == CTRL_OK || e_res == CTRL_FAIL)
            {
                vMotor_SetStatus( pCtrlMotor, e_res);
                 motorRunStep = MOTOR_1;
                return CTRL_OK;
            }
        break;
    }

    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM eMotor_ReadStatus( CtrlMotor_typedef *pCtrlMotor )
{
    CTRL_RESULT_ENUM e_res;

    pCtrlMotor->status = true;   /* read */
    switch( motorRunStep )
    {
        case MOTOR_1:
        default:
            pCtrlMotor->pMotorStatus = &st_MotorStatus1;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_1 , DIR_STOP);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_2;
            }
            else if( e_res == CTRL_FAIL )
            {
                return CTRL_FAIL;
            }
        break;
      
        case MOTOR_2:
            pCtrlMotor->pMotorStatus = &st_MotorStatus2;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_2 , DIR_STOP);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_3;
            }
            else if( e_res == CTRL_FAIL )
            {
                return CTRL_FAIL;
            }
        break;
       
        case MOTOR_3:
            pCtrlMotor->pMotorStatus = &st_MotorStatus3;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_3 , DIR_STOP);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_4;
            }
            else if( e_res == CTRL_FAIL )
            {
                return CTRL_FAIL;
            }
        break;
       
        case MOTOR_4:
            pCtrlMotor->pMotorStatus = &st_MotorStatus4;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_4 , DIR_STOP);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_1;
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

static CTRL_RESULT_ENUM eMotor_WriteCmdStatus( CtrlMotor_typedef *pCtrlMotor,  uint8_t dir )
{
    CTRL_RESULT_ENUM e_res; 
     
    pCtrlMotor->status = false;/* write */
    switch( motorRunStep )
    {
        case MOTOR_1:
        default:
            pCtrlMotor->pMotorStatus = &st_MotorStatus1;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_1 , dir);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_2;
            }
            else if( e_res == CTRL_FAIL )
            {
                return CTRL_FAIL;
            }
        break;
           
        case MOTOR_2:
            pCtrlMotor->pMotorStatus = &st_MotorStatus2;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_2 , dir);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_3;
            }
            else if( e_res == CTRL_FAIL )
            {
                return CTRL_FAIL;
            }
        break;
     
        case MOTOR_3:
            pCtrlMotor->pMotorStatus = &st_MotorStatus3;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_3 , dir);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_4;
            }
            else if( e_res == CTRL_FAIL )
            {
                return CTRL_FAIL;
            }
        break;
           
        case MOTOR_4:
            pCtrlMotor->pMotorStatus = &st_MotorStatus4;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_4 , dir);
            vMotor_SetStatus( pCtrlMotor, e_res);
            if( e_res == CTRL_OK )
            {
                motorRunStep = MOTOR_1;
                return CTRL_OK;
            }
            else if( e_res == CTRL_FAIL )
            {
                return CTRL_FAIL;
            }            
        return e_res;
    }

    return CTRL_IDLE;
}

/* End of this file */
