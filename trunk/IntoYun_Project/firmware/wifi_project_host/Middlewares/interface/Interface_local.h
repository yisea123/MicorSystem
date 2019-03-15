/** \file

$Id: interface_dev.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
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
#ifndef _INTERFACE_LOCAL_H
#define _INTERFACE_LOCAL_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  
#include "motor.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "typedef.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
  
typedef enum
{
  MOTOR_1 = 1,
  MOTOR_2 = 2,
  MOTOR_3 = 3,
  MOTOR_4 = 4,
  MOTOR_5 = 5,
  MOTOR_6 = 6,
}CTRL_MOTOR_ENUM;  
  
typedef enum
{
  MOTOR_CHECKERROR = 1,
  MOTOR_WRITESPEED = 2,
  MOTOR_READSTATUS = 3,
  MOTOR_STOPRUN = 4,
  MOTOR_POWEROFF = 5,
  MOTOR_RUNIDLE = 6,
  MOTOR_DELAY = 7,
}CTRL_MOTOR_RUN_ENUM;  


typedef struct {
    uint8_t Motor_4_Ctrl        :1;
    uint8_t Motor_3_Ctrl        :1;
    uint8_t Motor_2_Ctrl        :1;
    uint8_t Motor_1_Ctrl        :1;
    uint8_t Motor_4             :1;
    uint8_t Motor_3             :1;
    uint8_t Motor_2             :1;
    uint8_t Motor_1             :1;
} __PingTaiDevFlag_bits;

typedef struct {
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t JDQ_Dev_2           :1;
    uint8_t JDQ_Dev_1           :1;
} __DeviceTypeFlag_bits;

typedef struct {
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t Motor_Ctrl          :1;
    uint8_t Motor               :1;
} __TVTypeFlag_bits;

typedef struct {
    uint8_t Motor_2_Ctrl        :1;
    uint8_t Motor_1_Ctrl        :1;
    uint8_t                     :1;
    uint8_t                     :1;
    uint8_t Motor_2             :1;
    uint8_t Motor_1             :1;
    uint8_t                     :1;
    uint8_t                     :1;
} __KitchenDevFlag_bits;

typedef struct monitor_infor
{
    INT8U_BIT(DeviceTypeFlags, __DeviceTypeFlag_bits);
    INT8U_BIT(PingTaiDevFlags, __PingTaiDevFlag_bits);
    INT8U_BIT(KitchenDevFlags, __KitchenDevFlag_bits);
    INT8U_BIT(TVDevFlags, __TVTypeFlag_bits);
} monitor_infor;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _INTERFACE_DEV_H */ 