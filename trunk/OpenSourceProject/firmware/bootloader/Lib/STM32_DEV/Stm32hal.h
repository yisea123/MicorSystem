/**
  ******************************************************************************
  *                     (c) Copyright 2015, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    stm32hal.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2015/01/10
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#ifndef __STM32HAL_H
#define __STM32HAL_H

void HAL_IncTick(void);
uint32_t HAL_GetTick(void);
void HAL_Delay(__IO uint32_t Delay);
uint32_t timerGetId(void);
bool timerIsEnd(uint32_t timerID, uint32_t time);

#endif /* __STM32HAL_H */