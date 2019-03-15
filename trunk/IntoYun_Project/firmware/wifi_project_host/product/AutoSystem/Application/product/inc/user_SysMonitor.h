/**
  ******************************************************************************
  * @file    user_SysMonitor.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/07/27
  * @brief   
  *
  ******************************************************************************
  */
#ifndef _USER_SYSMONITOR_H
#define _USER_SYSMONITOR_H

typedef struct {
    uint8_t Motor_1	        :1;
    uint8_t Motor_2	        :1;
    uint8_t Motor_3		:1;
    uint8_t Motor_4		:1;
    uint8_t Presence		:1;
    uint8_t JdSensor_1		:1;
    uint8_t JdSensor_2		:1;
    uint8_t 	                :1;
} __PingTaiDevFlag_bits;

typedef struct {
    uint8_t JDQ_Dev_1	        :1;
    uint8_t JDQ_Dev_2	        :1;
    uint8_t 		        :1;
    uint8_t 		        :1;
    uint8_t 		        :1;
    uint8_t 		        :1;
    uint8_t 		        :1;
    uint8_t 	                :1;
} __DeviceTypeFlag_bits;

typedef struct Monitor_msg
{
    INT8U_BIT(DeviceTypeFlags, __DeviceTypeFlag_bits);
    INT8U_BIT(PingTaiDevFlags, __PingTaiDevFlag_bits);
} MSG;

CTRL_RESULT_ENUM user_GetAllDeviceStatus( void );

#endif  /* _USER_SYSMONITOR_H */ 



