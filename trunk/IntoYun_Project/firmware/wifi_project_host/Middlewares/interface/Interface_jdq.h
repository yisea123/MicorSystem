/** \file

$Id: interface_jdq.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#ifndef _INTERFACE_JDQ_H
#define _INTERFACE_JDQ_H

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
  JDQ_H = 0xFF,
  JDQ_L = 0,
}JDQ_CTRL_ENUM;

typedef enum
{
  JDQ_DOWN = 0,
  JDQ_UP = 1,
  JDQ_STOP = 2,
}JDQ_STATUS_ENUM;


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vJdq_CtrlInit( CtrlJDQ_typedef *pCtrlJdq );
void vJdq_ContrlReset( CtrlJDQ_typedef *pCtrlJdq );
CTRL_RESULT_ENUM eJDQ_CtrlInterface( CtrlJDQ_typedef *pJDQ_typedef, uint8_t dir );


/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _INTERFACE_JDQ_H */ 
