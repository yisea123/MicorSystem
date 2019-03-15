/** \file

$Id: tim.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013  Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __PLATFORM_DEF_H
#define __PLATFORM_DEF_H

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "typedef.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/


/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

  
/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/  
#define DPID_YUN_ID_1                              1 
#define DPID_YUN_ID_2                              2

#define DPID_YUN_ID_3                              3
#define DPID_YUN_ID_4                              4

#define DPID_YUN_ID_5                              5
#define DPID_YUN_ID_6                              6

#define DPID_YUN_ID_7                              7
#define DPID_YUN_ID_8                              8

#define DPID_YUN_ID_ALLDEV                         0XFE  
#define DPID_YUN_ID_NULL                           0XFF    
 
typedef enum
{
  DIR_DOWN = 0,
  DIR_UP = 1,
  DIR_STOP = 2,
}CTRL_DIR_STATUS; 
  
typedef enum
{
    LED_ID_1 = 0,
    LED_NULL_ID,
}led_ID_enum; 
  
typedef enum
{
    JDQ_CH4_ID = 0,
    JDQ_CH4_STAIR_ID = 2,
}JDQ_CH4_TypeID_enum;  

typedef enum
{
    LAZYBACK_1_ID = 0,
    LAZYBACK_2_ID = 2,
    DESK_ID = 6,
    NULL_ID = 0xff,
}JDQ_CH8_TypeID_enum;  
  
typedef enum
{
    MOROT_LEVEL_ADD = 1,   // MOTOR: 1~4
    MOROT_TV_ADD = 5,      // MOTOR
    JDQ_CH8_ADD = 10,      // JDQ: 8 channel
    JDQ_CH4_ADD = 11,      // JDQ: 4 channel
    JDQ_CH4_READADD = 12,      // JDQ: 4 channel
    INCLIN_ADD = 30,
    NULL_ADDR = 0XFF
}device_addr_enum;

typedef struct {
    uint8_t Level           :1;
    uint8_t TV              :1;
    uint8_t Light_1         :1;
    uint8_t Light_2         :1;
    uint8_t Desk            :1;
    uint8_t Lazy_1          :1;
    uint8_t Lazy_2          :1;
    uint8_t stair           :1;
} __DevEnableFlag_bits;

typedef struct {
    uint16_t closeAllDev     :1;  /* shut off all devices */
    uint16_t                 :2;
    uint16_t                 :2;
    uint16_t                 :1;
    uint16_t                 :1;
    uint16_t                 :1;
    uint16_t                 :1;
    uint16_t                 :1;
} __DevLevelFlag_bits;

typedef struct
{
    uint8_t addres; 
    uint8_t dev_type;
    uint8_t b_ctrlres[6];
    uint8_t YunID;
    INT8U_BIT(DevEnableFlags, __DevEnableFlag_bits);
    INT16U_BIT(DevLevelFlags, __DevLevelFlag_bits);
}CtrL_typedef;

typedef enum
{
    LIVE_TYPE = 1,
    STAIR_TYPE = 2,
    LAZYBACK_TYPE = 3,
    DESK_TYPE = 4,
    LED_TYPE = 5,
    TV_TYPE = 6,
    PRESENCE_TYPE = 7,
    KITCHEN_TYPE = 8,
    DING_TABLE_TYPE = 9,
    NULL_TYPE = 0xff,
}Device_Type;

/*
  device type 
*/
typedef enum
{
    JDQ_DEVICEPORT_LAZYBACKEXT = 0,
    JDQ_DEVICEPORT_LAZYBACK = 2,
    JDQ_DEVICEPORT_CORROR = 4,
    JDQ_DEVICEPORT_DESK = 6,
    JDQ_NULL_CMD = 0xff,
}JDQ_DeviceCtrlID_enum;

typedef enum
{
    CTRL_FAIL = 0,
    CTRL_OK = 1,
    CTRL_IDLE = 2,
}CTRL_RESULT_ENUM;

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_DEF_H */
