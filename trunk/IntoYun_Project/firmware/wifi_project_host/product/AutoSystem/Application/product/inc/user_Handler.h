/** \file

$Id: user_Handler.h 40486 2018-08-26 22:50:21Z tangmingfei2013@126.com $

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
#ifndef _APPS_CTRL_H
#define _APPS_CTRL_H

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

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vAppsCtrl_Init( void );
void vAppsCtrl_SetDevicePara(uint8_t id, uint8_t type, uint8_t *dir );
void vAppsCtrl_Process( void );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _APPS_CTRL_H */ 
