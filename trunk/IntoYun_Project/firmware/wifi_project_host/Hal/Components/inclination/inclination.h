/** \file

$Id: inclination.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __INCLINATION_H
#define __INCLINATION_H

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/

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
 
typedef struct
{
  uint8_t address;
  uint8_t retry;
  uint8_t step;
  int x_value;
  int y_value;
  
  uint16_t *length;
  uint8_t *datapacket;
  void (*pf_SendPut)(uint8_t*, uint8_t); 
}Inclin_typedef;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
CTRL_RESULT_ENUM Inclin_ReadValue( Inclin_typedef *pCtrL );
void vInclin_Reset( Inclin_typedef *pCtrL );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __INCLINATION_H */  