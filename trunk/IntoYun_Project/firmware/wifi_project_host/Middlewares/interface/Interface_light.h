/** \file

$Id: interface_light.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#ifndef _INTERFACE_LIGHT_H
#define _INTERFACE_LIGHT_H

/******************************************************************************
* INCLUDE FILES
******************************************************************************/  

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
* INCLUDE FILES
******************************************************************************/ 
#include "light.h"
  
/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vLight_CtrlInit( void );
CTRL_RESULT_ENUM eLight_CtrlInterface( void );
void vLight_SetPara(uint8_t id, uint8_t status, uint8_t wLuminance, uint8_t yLuminance );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _INTERFACE_LIGHT_H */ 
