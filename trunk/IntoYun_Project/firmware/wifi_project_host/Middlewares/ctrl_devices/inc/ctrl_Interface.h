/**
  ******************************************************************************
  * @file    Src/user/Ctr_Interface.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/20
  * @brief   system control interface
  *
  ******************************************************************************
  */
#ifndef _CTRL_DEVINTERFACE_H
#define _CTRL_DEVINTERFACE_H

typedef struct
{
  void (*Ctrl_motorInit)( CtrlMotor_typedef *pCtrlMotor );
  void (*vMotor_Reset)( void );
  void (*vMotor_Handler)( CtrlMotor_typedef *pCtrlMotor );
  void (*vMotor_GetStatus)( AllMotorStatus_typedef *pAllMotorStatus);
  CTRL_RESULT_ENUM (*eMotor_CheckError)( CtrlMotor_typedef *pCtrlMotor );
  void (*vMotor_HandlerTV)( CtrlMotor_typedef *pCtrlMotor );
}vMotor_t; 

extern const vMotor_t motorCtrl;

typedef struct
{
  void (*Ctrl_jdSensorInit)( CtrlJQSensor_typedef *pCtrL_typedef );
  void (*vJdSensor_Reset)( CtrlJQSensor_typedef *pCtrL_typedef );
  CTRL_RESULT_ENUM (*JdSensor_ReadValue)( CtrlJQSensor_typedef *pCtrL_typedef );
}vJdSensor_t;

extern const vJdSensor_t jdSensorCtrl;


extern const vJDQ_t jdqCtrl;

typedef struct
{
  CTRL_RESULT_ENUM (*vPensence_ReadValue)( Presence_TypeDef *pCtr_Presence );
  void (*vPresenceInit)(Presence_TypeDef *pCtr_Presence);
}vPresence_t;

extern const vPresence_t presenceCtrl;

typedef struct
{
  void (*Ctrl_LightInit)( void );
  void (*vLight_TurnOn)( CtrlLight_typedef *pCtrlLight );
  void (*vLight_TurnOff)( CtrlLight_typedef *pCtrlLight );
  bool (*vLight_ScanUID)( void );
  CTRL_RESULT_ENUM (*vLight_Handler)( CtrL_typedef *pCtrL_typedef );
  void (*vLight_Reset)( CtrL_typedef *pCtrL_typedef );
}vlightCtrl_t;

extern const vlightCtrl_t lightCtrl;

#endif  /* _CTRL_DEVINTERFACE_H */ 