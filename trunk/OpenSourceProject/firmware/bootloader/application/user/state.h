/**
  ******************************************************************************
  *                     (c) Copyright 2018, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    state.h
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/10
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#ifndef __STATE_H
#define __STATE_H

typedef void (*STATE_FUNC)(void *);
extern STATE_FUNC pSt_State;

void State_Machine( void );
static void State_SysActProcess( void *ptr );

#endif /* __STATE_H */