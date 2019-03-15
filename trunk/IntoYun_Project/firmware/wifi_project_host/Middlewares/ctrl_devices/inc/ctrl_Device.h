/**
  ******************************************************************************
  * @file    Src/user/Ctr_Device.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @brief   modbus ctrl interface 
  *
  ******************************************************************************
  */
#ifndef _CTRL_DEVICE_H
#define _CTRL_DEVICE_H

#include "platform_def.h"

typedef struct
{
  uint8_t cmdID;       /* devices add */
  uint8_t b_ctrlres;   /* control status */
}Ctr_Device;

typedef struct
{
  uint8_t addres;       /* devices add */
  uint8_t type;         /* device type */
  uint8_t cmd;          /* control cmd */
}Ctr_Modbus_TypeDef;

typedef struct
{
  uint16_t *length;
  uint8_t *datapacket;
  void (*pf_SendPut)(uint8_t*, uint8_t); 
  uint8_t retry;
  CtrL_typedef *pCtrL_typedef;
}CtrlJDev_typedef;

void Device_Send(  CtrlJDev_typedef *pCtrlDev );
CTRL_RESULT_ENUM Device_ActionProcess(  CtrlJDev_typedef *pCtrlDev );

#endif  /* _CTRL_MODBUSINTERFACE_H */ 


