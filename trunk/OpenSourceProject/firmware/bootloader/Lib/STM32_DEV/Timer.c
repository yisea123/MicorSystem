/**
  ******************************************************************************
  *                     (c) Copyright 2015, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    timer.c
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
#include "includes.h"

void Timer_Init( INT8U u8_Timer_EN )
{
    TIM_TimeBaseInitTypeDef  tim_init;

    switch ( u8_Timer_EN  ){
    case TIMER1:
        break;
    case TIMER2: 
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
        tim_init.TIM_Period        = 0xFFFF;
        tim_init.TIM_Prescaler     = 0x00;
        tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
        tim_init.TIM_CounterMode   = TIM_CounterMode_Up;
    
        TIM_TimeBaseInit(TIM2, &tim_init);
        TIM_SetCounter(TIM2, 0);
        TIM_PrescalerConfig(TIM2, 10, TIM_PSCReloadMode_Immediate);
        TIM_Cmd(TIM2, ENABLE);
        TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
        break;
    case TIMER3:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
        tim_init.TIM_Period        = 0xFFFF;
        tim_init.TIM_Prescaler     = 0x00;
        tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
        tim_init.TIM_CounterMode   = TIM_CounterMode_Up;
    
        TIM_TimeBaseInit(TIM3, &tim_init);
        TIM_SetCounter(TIM3, 0);
        TIM_PrescalerConfig(TIM3, 100, TIM_PSCReloadMode_Immediate);
        TIM_Cmd(TIM3, ENABLE);
        TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
        break;
    case TIMER4:
    
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
        tim_init.TIM_Period        = 0xFFFF;
        tim_init.TIM_Prescaler     = 0x00;
        tim_init.TIM_ClockDivision = TIM_CKD_DIV1;
        tim_init.TIM_CounterMode   = TIM_CounterMode_Up;
    
        TIM_TimeBaseInit(TIM4, &tim_init);
        TIM_SetCounter(TIM4, 0);
        TIM_PrescalerConfig(TIM4, 0x2327, TIM_PSCReloadMode_Immediate);
        TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
        TIM_Cmd(TIM4, ENABLE);
        break;
    default:
      break;
  }
     
}


INT32U  Timer_TmrRd ( INT8U u8_TIMER_EN )
{
  //INT32U u32_count; 
  
  /*
  switch ( u8_TIMER_EN ){
  case TIMER1:
    break;
  case TIMER2:
    u32_count = ((INT32U)TIM_GetCounter(TIM2));
    break;
  case TIMER3:
    u32_count = ((INT32U)TIM_GetCounter(TIM3));
    break;
  case TIMER4:
    u32_count = ((INT32U)TIM_GetCounter(TIM4));
    break;
  default:
    break;
  }
  */
  return 0;
}

/* EOF */