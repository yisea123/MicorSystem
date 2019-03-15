/** \file

$Id: user_diningTable.h 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef _USER_DININGTABLE_H
#define _USER_DININGTABLE_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  
#include "jdq.h"

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
    TYPE_OPEN = 0,
    TYPE_CLOSE = 1,
    TYPE_STOP = 2,
}TYPE_enum;  

typedef enum
{
    DOOR_1_ID = 0,
    DOOR_2_ID = 2,
    PUSH_1_ID = 4,   
    PUSH_2_ID = 6,
    DING_NULL_ID = 0xff,
}JDQ_CH8_DingTable_enum;  

typedef struct{
    uint8_t id;
    uint8_t delayTime;
    uint8_t status;
    uint8_t str[32];
}table_CtrlAction;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vUser_diningTableInit( void );
void vUser_diningTableSetDevicePara(uint8_t id, uint8_t type, uint8_t *dir );
void vUser_diningTable_Process( void );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _USER_DININGTABLE_H */ 