/** \file

$Id: state.h 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
#ifndef __STATE_H
#define __STATE_H

/******************************************************************************
* EXPORTED MACROS AND DEFINITIONS
******************************************************************************/ 
typedef void (*STATE_FUNC)(void *);
extern STATE_FUNC pSt_State;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void State_Machine( void );
static void State_SysActProcess( void *ptr );

#endif /* __STATE_H */