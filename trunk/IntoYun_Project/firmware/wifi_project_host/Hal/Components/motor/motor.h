/** \file

$Id: motor.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __MOTOR_H
#define __MOTOR_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/

#include "platform_def.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

#define MOTOR_RUNWRITE          10
#define MOTOR_SPEED             150
#define DELAY_TIME              5  
 
  
typedef struct
{
   bool Onlive;
   uint8_t SendCmdCnt;  
   uint8_t cmd;          /* response cmd */
   uint8_t addres;       /* devices add */
   uint8_t sqr_1;
   uint8_t sqr_2;
   uint16_t speed;
   uint16_t elecValue;   /* control cmd */
}MotorStatus_typedef;

typedef struct
{
    uint16_t *length;
    uint8_t *datapacket;
    void (*pf_SendPut)(uint8_t*, uint8_t); 
    bool status;
    MotorStatus_typedef *pMotorStatus;
}CtrlMotor_typedef;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
void vMotor_WriteSpeedCmd(  CtrlMotor_typedef *pCtrlMotor, 
                            uint8_t addr, 
                            int speed );

void vMotor_ReadSpeedCmd( CtrlMotor_typedef *pCtrlMotor, 
                          uint8_t addr );

void vMotor_WriteSpeed ( CtrlMotor_typedef *pCtrlMotor,
                         uint8_t MotorNum, 
                         int dir  );

void vMotor_ResetPara( MotorStatus_typedef *pMotorStatus );
bool bMotor_ParserReadSpeedResp( CtrlMotor_typedef *pCtrlMotor);
bool bMotor_ParserWriteCmdResp( CtrlMotor_typedef *pCtrlMotor);

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __MOTOR_H */  
  
  