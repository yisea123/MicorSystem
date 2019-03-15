/**
  ******************************************************************************
  * @file    Src/user/CtrModbusInterface.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @brief   modbus ctrl interface 
  *
  ******************************************************************************
  */
#ifndef _CTRL_MODBUSINTERFACE_H
#define _CTRL_MODBUSINTERFACE_H

#include "platform_def.h"
#include "motor.h"

typedef enum
{
  MOTOR_1 = 1,
  MOTOR_2 = 2,
  MOTOR_3 = 3,
  MOTOR_4 = 4,
}CTRL_MOTOR_ENUM;

typedef struct
{
    MotorStatus_typedef st_Motor1Status;
    MotorStatus_typedef st_Motor2Status;
    MotorStatus_typedef st_Motor3Status;
    MotorStatus_typedef st_Motor4Status;
}AllMotorStatus_typedef;

void vMotor_CtrInterface( CtrlMotor_typedef *pCtrlMotor );
void vMotor_CtrlReset( void );
void vMotor_GetStatus( AllMotorStatus_typedef *pAllMotorStatus);
CTRL_RESULT_ENUM eMotor_CheckError( CtrlMotor_typedef *pCtrlMotor );
void vMotor_CtrInterfaceTV( CtrlMotor_typedef *pCtrlMotor );

#endif  /* _CTRL_MODBUSINTERFACE_H */ 
