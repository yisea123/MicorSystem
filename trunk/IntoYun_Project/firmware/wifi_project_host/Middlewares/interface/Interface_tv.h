/** \file

$Id: interface_tv.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#ifndef _INTERFACE_TV_H
#define _INTERFACE_TV_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  
#include "motor.h"

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
void vMotorTV_CtrlInit( void);
void vCtrl_MotorTVStart( uint8_t dir  );
CTRL_RESULT_ENUM eCtrl_MotorTVInterface( void );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _INTERFACE_TV_H */ 