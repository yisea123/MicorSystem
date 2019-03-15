/** \file

$Id: user_SysMonitor.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef _USER_SYSMONITOR_H
#define _USER_SYSMONITOR_H

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
typedef struct {
    uint8_t Motor_1        :1;
    uint8_t Motor_2        :1;
    uint8_t Motor_3        :1;
    uint8_t Motor_4        :1;
    uint8_t Presence       :1;
    uint8_t JdSensor_1     :1;
    uint8_t JdSensor_2     :1;
    uint8_t                :1;
} __PingTaiDevFlag_bits;

typedef struct {
    uint8_t JDQ_Dev_1      :1;
    uint8_t JDQ_Dev_2      :1;
    uint8_t                :1;
    uint8_t                :1;
    uint8_t                :1;
    uint8_t                :1;
    uint8_t                :1;
    uint8_t                :1;
} __DeviceTypeFlag_bits;

typedef struct Monitor_msg
{
    INT8U_BIT(DeviceTypeFlags, __DeviceTypeFlag_bits);
    INT8U_BIT(PingTaiDevFlags, __PingTaiDevFlag_bits);
} MSG;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/ 
CTRL_RESULT_ENUM user_GetAllDeviceStatus( void );

#endif  /* _USER_SYSMONITOR_H */ 



