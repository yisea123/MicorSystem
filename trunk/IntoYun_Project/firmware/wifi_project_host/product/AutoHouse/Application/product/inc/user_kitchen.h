/** \file

$Id: user_kichen.h 40486 2018-09-23 18:30:21Z tangmingfei2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#ifndef _USER_KITCHEN_H
#define _USER_KITCHEN_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  
#include "motor.h"
#include "Interface_local.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vUserKitchen_Init( void );
void vUserKitchen_SetDevicePara(uint8_t id, uint8_t type, uint8_t *dir );
void vUser_Kitchen_Process( void );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _USER_KITCHEN_H */ 