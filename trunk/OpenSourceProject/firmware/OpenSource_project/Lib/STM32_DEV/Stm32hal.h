/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    stm32hal.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
*/
#ifndef __STM32HAL_H
#define __STM32HAL_H

#define   INSTR_DBG_EN		   1
#define   DEBUG_UART               USART3
#define   DbgPrint(...)

#if  INSTR_DBG_EN
#define   Debug_Printf             UART3_Put
#else
#define   Debug_Printf             DbgPrint
#endif


void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
void HAL_Delay(__IO uint32_t Delay);
uint32_t timerGetId(void);
bool timerIsEnd(uint32_t timerID, uint32_t time);

#endif /* __STM32HAL_H */