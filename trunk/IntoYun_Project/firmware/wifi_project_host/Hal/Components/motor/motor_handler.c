/** \file

$Id: motor_handler.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

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
#include "motor_handler.h"

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/

CTRL_RESULT_ENUM vMotor_CtrlHandler( CtrlMotor_typedef *pCtrlMotor, uint8_t addr , uint8_t dir)
{
    MotorStatus_typedef *pMotorStatus;
    bool res = false;

    pMotorStatus = pCtrlMotor->pMotorStatus;
    if(pCtrlMotor->status)   
    {
        res = bMotor_ParserReadSpeedResp( pCtrlMotor );
    }
    else
    {
        res = bMotor_ParserWriteCmdResp( pCtrlMotor );
    }
    
    if(res)
    {
        pMotorStatus->SendCmdCnt = 0;
        //check address
        if( pMotorStatus->addres == addr )
        {
            pMotorStatus->Onlive = true;
            return CTRL_OK;
        }
    }
    else
    {
        if(pCtrlMotor->status)
        {
            vMotor_ReadSpeedCmd( pCtrlMotor, addr);       //Read speed
        }
        else
        {
            vMotor_WriteSpeed( pCtrlMotor, addr, dir);    //Write speed
        }

        pMotorStatus->SendCmdCnt++;
        if(  pMotorStatus->SendCmdCnt > MOTOR_RUNWRITE )
        {
            pMotorStatus->Onlive = false;
            pMotorStatus->SendCmdCnt = 0;
            return CTRL_FAIL;
        }
    }
          
    return CTRL_IDLE;
}

/* End of this file */