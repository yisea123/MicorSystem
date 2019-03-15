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
#include "Interface_kitchen.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define  DELAY_MAXTIME                        100
#define SNDCMD_MAXCNT                         5

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static CtrlMotor_typedef st_CtrlMotor;

static MotorStatus_typedef st_MotorStatus1;
static MotorStatus_typedef st_MotorStatus2;

static uint8_t motorRunStep = MOTOR_1;
static uint8_t actionStep = MOTOR_RUNIDLE;
static uint8_t MotorunWait;
static uint8_t dirRun;
static monitor_infor st_Monitor;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res );
static CTRL_RESULT_ENUM eMotor_ReadStatus( CtrlMotor_typedef *pCtrlMotor );
static CTRL_RESULT_ENUM eMotor_WriteCmdStatus( CtrlMotor_typedef *pCtrlMotor,  uint8_t dir );
static CTRL_RESULT_ENUM eMotor_CheckMotorSqr2( void );

static void vMotor_CtrlActionKitchenError( void );
static void vMotor_CheckMotorControllerError( void );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void Ctrl_MotorKitchenInit( void )
{
    CtrlMotor_typedef *pCtrlMotor = &st_CtrlMotor;
    UART *pUart = &st_Uart1;
    
    pCtrlMotor->pf_SendPut = HAL_485WriteSerial_Port1;
    pCtrlMotor->length = &(pUart->u16_RxHead);
    pCtrlMotor->datapacket = pUart->u8_RxBuf;
    actionStep = MOTOR_RUNIDLE;
    vCtrl_ResetKitchenMotor();
}

void Ctrl_MotorKitchenStart( uint8_t dir )
{
    actionStep = MOTOR_CHECKERROR;
    dirRun  = dir;
    vCtrl_ResetKitchenMotor();
    MotorunWait = 0;
}

void vCtrl_ResetKitchenMotor( void )
{
    motorRunStep = MOTOR_1;
    vMotor_ResetPara( &st_MotorStatus1 );
    vMotor_ResetPara( &st_MotorStatus2 );
    MotorunWait = 0;
}

CTRL_RESULT_ENUM Ctrl_MotorKitchenInterface( void )
{
    CtrlMotor_typedef *pCtrlMotor = &st_CtrlMotor;
    CTRL_RESULT_ENUM e_res;

    switch( actionStep )
    {
        case MOTOR_CHECKERROR:   //Check error
            e_res = eMotor_CtrlStatus( pCtrlMotor, true);
            if( e_res != CTRL_IDLE )
            {
                vCtrl_ResetKitchenMotor();
                if( e_res == CTRL_FAIL )
                {
                    actionStep = MOTOR_STOPRUN;
                }
                if( e_res == CTRL_OK )
                {
                    actionStep = MOTOR_WRITESPEED;
                }
             }
        break;
     
        case MOTOR_WRITESPEED:   //Write speed
            e_res = eMotor_WriteCmdStatus( pCtrlMotor, dirRun );
            if( e_res != CTRL_IDLE )
            {
                vCtrl_ResetKitchenMotor();
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
            MotorunWait++;
            if( MotorunWait < DELAY_MAXTIME )
                return  CTRL_IDLE;
            MotorunWait = 0;
            actionStep = MOTOR_READSTATUS;
        break;        
     
        case MOTOR_READSTATUS:    //Read status;
            e_res = eMotor_ReadStatus( pCtrlMotor );
            if( e_res != CTRL_IDLE )
            {
                if( e_res == CTRL_FAIL )
                {   
                    vMotor_CheckMotorControllerError();
                    tim_SetTimIsr( TIMER2, vMotor_CtrlActionKitchenError, SNDCMD_MAXCNT);
                    actionStep = MOTOR_STOPRUN;
                }
                else if( e_res == CTRL_OK )
                {
                    e_res = eMotor_CheckMotorSqr2();
                    if( e_res == CTRL_OK )
                    {
                        actionStep = MOTOR_STOPRUN;
                    }
                }
                
                if( actionStep ==MOTOR_STOPRUN )
                {
                    vCtrl_ResetKitchenMotor();
                }                
            }
        break;
     
        case MOTOR_STOPRUN:      //Stop
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

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void  vMotor_CtrlActionKitchenError( void )
{
    uint8_t buff[3];

    buff[0] =  KITCHEN_TYPE;
    buff[1] =  DPID_YUN_ID_1;
    buff[2] =  st_Monitor.KitchenDevFlags;
    apps_SendErrorCode( buff, 3);
}

static void vMotor_CheckMotorControllerError( void )
{
    st_Monitor.KitchenDevFlags_bit.Motor_1_Ctrl = st_MotorStatus1.Onlive;
    st_Monitor.KitchenDevFlags_bit.Motor_2_Ctrl = st_MotorStatus2.Onlive;
}

static CTRL_RESULT_ENUM eMotor_CheckMotorSqr2( void )
{
    if( st_MotorStatus1.sqr_2 == 0 && st_MotorStatus2.sqr_2 == 0 )
    {
        return CTRL_OK;
    }
    
    return  CTRL_IDLE;
}

static CTRL_RESULT_ENUM eMotor_CtrlStatus( CtrlMotor_typedef *pCtrlMotor, bool res )
{
    CTRL_RESULT_ENUM e_res;

    pCtrlMotor->status = res;
    switch( motorRunStep )
    {
        case MOTOR_1:
        default:
            pCtrlMotor->pMotorStatus = &st_MotorStatus1;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_1, DIR_STOP);
            if( e_res == CTRL_OK || e_res == CTRL_FAIL)
            {
                motorRunStep = MOTOR_2;
            }
        break;

        case MOTOR_2:
            pCtrlMotor->pMotorStatus = &st_MotorStatus2;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_2, DIR_STOP);
            if( e_res == CTRL_OK || e_res == CTRL_FAIL)
            {
                return CTRL_OK;
            }       
        break;
    }

    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM eMotor_ReadStatus( CtrlMotor_typedef *pCtrlMotor )
{
    CTRL_RESULT_ENUM e_res;

    pCtrlMotor->status = true;
    switch( motorRunStep )
    {
        case MOTOR_1:
        default:
            pCtrlMotor->pMotorStatus = &st_MotorStatus1;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_1 , DIR_STOP);
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
            if( e_res == CTRL_OK )
            {                
                e_res = eMotor_CheckMotorSqr2();
                if( e_res == CTRL_OK )
                {
                    return CTRL_OK;
                }
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

    pCtrlMotor->status = false;
    switch( motorRunStep )
    {
        case MOTOR_1:
        default:
            pCtrlMotor->pMotorStatus = &st_MotorStatus1;
            e_res = vMotor_CtrlHandler( pCtrlMotor,  MOTOR_1 , dir);
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


/* End of this file */
