/**
  ******************************************************************************
  * @file    Src/user/Ctrl_JdSensor.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/15
  * @brief   JQ Sensor ctrl interface 
  *
  ******************************************************************************
  */
#ifndef _CTRL_JQSENSOR_H
#define _CTRL_JQSENSOR_H

#include "platform_def.h"

typedef struct
{
  uint8_t address;
  uint8_t retry;
  uint8_t step;
  int x_value;
  int y_value;
  
  uint16_t *length;
  uint8_t *datapacket;
  void (*pf_SendPut)(uint8_t*, uint8_t); 
}CtrlJQSensor_typedef;

void vJdSensor_CtrlInterfaceReset( CtrlJQSensor_typedef *pCtrL_typedef );
CTRL_RESULT_ENUM JdSensor_ReadValue( CtrlJQSensor_typedef *pCtrL_typedef );

#endif  /* _CTRL_MODBUSINTERFACE_H */ 