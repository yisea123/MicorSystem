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
#ifndef _INTERFACE_DEV_H
#define _INTERFACE_DEV_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  
#include "motor.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
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
void vMotor_CtrlInit( void );
void vCtrl_MotorStart( uint8_t dir  );
void vCtrl_MotorSetActStep( uint8_t step );
CTRL_RESULT_ENUM eCtrl_MotorInterface( void );
CTRL_RESULT_ENUM eMotor_CheckMotorSqr2( void );
CTRL_RESULT_ENUM eMotor_CheckMotorSqr1( void );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _INTERFACE_DEV_H */ 

