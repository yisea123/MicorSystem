/** \file

$Id: jdq.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __JDQ_H
#define __JDQ_H

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

#define JDQ_RUNWRITE          5 
  
typedef struct
{
  //for control 
   bool Onlive;
   uint8_t SendCmdCnt;
   uint8_t step;         /* ctrl step */
   
   //for send 
   uint8_t SetChannel;      /* channel*/ 
   uint8_t SetAddress;      /* devices add */
   uint8_t SetStatus;       /* control paramater */
   uint8_t SetTotalChn;     /* total channel */
   
   //for response
   uint8_t GetChannel;     /* channel*/ 
   uint8_t GetStatus;      /* get status */
   uint8_t GetAddress;     /* devices add */
   
   uint16_t analValue;
   uint16_t boolValue;
}JdqStatus_typedef;

typedef struct
{
  uint16_t *length;
  uint8_t *datapacket;
  void (*pf_SendPut)(uint8_t*, uint8_t);
  JdqStatus_typedef st_JdqCtrlPara;
}CtrlJDQ_typedef;  

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/  
CTRL_RESULT_ENUM jdq_ReadAnalValueHandler( CtrlJDQ_typedef *pJdq );
CTRL_RESULT_ENUM jdq_Handler( CtrlJDQ_typedef *pJdq );
CTRL_RESULT_ENUM jdq_ReadBoolValueHandler( CtrlJDQ_typedef *pJdq );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __JDQ_H */  