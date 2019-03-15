/** \file

$Id: Timer.c 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

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
#include "includes.h"

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static uint32_t runCount[TIM_INDEX_COUNT];
static uint32_t s_param[TIM_INDEX_COUNT];
typedef void (*cb_t)(void);
/*!
 * @brief The actually installed interrupt handlers
 */
static cb_t s_timIsr[] =
{
    NULL
  , NULL
  , NULL
  , NULL
  , NULL
};

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
void Timer_Init( INT8U u8_Timer_EN )
{
    NVIC_InitTypeDef NVIC_InitStructure;
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
        
        // Enable the TIM2 global Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 6;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);
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
        
        // Enable the TIM3 global Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);          
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
        
        // Enable the TIM4 global Interrupt 
        NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 8;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
        NVIC_Init(&NVIC_InitStructure);         
        break;
    default:
      break;
  } 
}

void tim_SetTimIsr( const INT8U timer, void (*isr)(void), uint32_t param )
{
    switch ( timer  )
    {
      case TIMER1:
          return;
      case TIMER2: 
          TIM_Cmd(TIM2, ENABLE);
          TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
          break;
      case TIMER3:
          TIM_Cmd(TIM3, ENABLE);
          TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
          break;
      case TIMER4:
          TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
          TIM_Cmd(TIM4, ENABLE);
          break;
      default:
        return;
  }
  
  runCount[timer]  = 0;
  s_param[timer] = param;
  s_timIsr[timer] = isr; 
  Timer_Init( timer );
}

void stim_Stop( INT8U timer )
{
    switch ( timer  )
    {
        case TIMER1:
            break;
        case TIMER2: 
            TIM_Cmd(TIM2, DISABLE);
            TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
            break;
        case TIMER3:
            TIM_Cmd(TIM3, DISABLE);
            TIM_ITConfig(TIM3, TIM_IT_Update, DISABLE);
            break;
        case TIMER4:
            TIM_ITConfig(TIM4, TIM_IT_Update, DISABLE);
            TIM_Cmd(TIM4, DISABLE);
            break;
        default:
          break;
    }
    runCount[timer]  = 0;
}

void TIM2_IRQHandler(void)
{
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    TIM_Cmd(TIM2,ENABLE);
    
    runCount[TIMER2]++;
    if( runCount[TIMER2] > s_param[TIMER2])
    {
         TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
         TIM_Cmd(TIM2,DISABLE);    
    }
    else
    {
        if ( s_timIsr[TIMER2] != NULL )
        {
            s_timIsr[TIMER2]();
        }
    }
} 

/* End of this file  */