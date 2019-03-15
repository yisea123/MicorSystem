/** \file

$Id: Timer.h 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __TIMER_H
#define __TIMER_H

#ifdef __cplusplus
extern "C" {
#endif
  
/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
#define TIM_INDEX_COUNT    5

typedef enum {
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3,
    TIMER4,
}TIMER_ENUM;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/ 
void tim_SetTimIsr( const uint8_t timer, void (*isr)(void), uint32_t param );
void stim_Stop( uint8_t timer );

#ifdef __cplusplus
}
#endif

#endif   /* __TIMER_H */