/** \file

$Id: presence.h 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __PRESENCE_H
#define __PRESENCE_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/

#include "platform_def.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
typedef struct
{
   uint8_t step;
   uint8_t retry;
   uint8_t  id[16];
   bool res;
   
   uint16_t *length;
   uint8_t *datapacket;
   void (*pf_SendPut)(uint8_t*, uint8_t);
}Presence_TypeDef;

typedef enum
{
  PENSENCE_ID = 0x00,
  PENSENCE_VALUE = 0x01,
}Presence_STEP_ENUM;


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
CTRL_RESULT_ENUM vPresence_ReadValue( Presence_TypeDef *pCtr_Presence );
CTRL_RESULT_ENUM ePresence_OnlyReadValue( Presence_TypeDef *pCtr_Presence );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __PRESENCE_H */  