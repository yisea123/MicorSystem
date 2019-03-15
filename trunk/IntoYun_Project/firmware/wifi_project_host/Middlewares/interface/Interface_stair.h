/** \file

$Id: interface_stair.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#ifndef _INTERFACE_STAIR_H
#define _INTERFACE_STAIR_H

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
  STAIR_OPEN = 0,
  STAIR_CLOSE = 1,
  STAIR_STOP = 2,
  STAIR_NULL = 0xff,
}STAIR_STATUS_ENUM;


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vStair_Init( CtrlMotor_typedef *pCtrlMotor );
void vStair_CtrlStart( void );
CTRL_RESULT_ENUM eStair_CtrlInterface( CtrlMotor_typedef *pCtrlMotor,
                                       CtrlJDQ_typedef *pJDQ_typedef,
                                       CtrL_typedef *pCtrL_typedef);
                                     
/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _INTERFACE_STAIR_H */ 