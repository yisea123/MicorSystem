/** \file

$Id: IAP.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __IAP_H
#define __IAP_H

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "stm32f10x.h"
/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

void FLASH_If_Init(void);
uint8_t IAP_FlashProgram( uint32_t WriteAddr,uint8_t *pRbuff, uint32_t len );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
}
#endif

#endif /* __IAP_H */