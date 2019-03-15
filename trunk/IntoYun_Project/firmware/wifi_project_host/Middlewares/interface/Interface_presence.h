/** \file

$Id: interface_presence.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#ifndef _INTERFACE_PRESENCE_H
#define _INTERFACE_PRESENCE_H

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
#include "presence.h"
  
/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vPresence_Init( Presence_TypeDef *pPresence );  
CTRL_RESULT_ENUM vPresence_Interface( Presence_TypeDef *pPresence );
void vPresence_Reset( Presence_TypeDef *pPresence );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif  /* _INTERFACE_PRESENCE_H */ 