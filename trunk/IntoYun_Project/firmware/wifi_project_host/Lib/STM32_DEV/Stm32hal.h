/** \file

$Id: Stm32hal.h 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#ifndef __STM32HAL_H
#define __STM32HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define   INSTR_DBG_EN		   0
#define   DEBUG_UART               USART3
#define   DbgPrint(...)

#if  INSTR_DBG_EN
#define   Debug_Printf             UART3_Put
#else
#define   Debug_Printf             DbgPrint
#endif

void HAL_IncTick(void);
uint32_t HAL_GetTick(void);


bool HAL_timerIsEnd(uint32_t timerID, uint32_t time);
uint32_t HAL_timerGetId(void);


void HAL_Delay(__IO uint32_t Delay);
void LedBlink(void);

#ifdef __cplusplus
}
#endif

#endif /* __STM32HAL_H */