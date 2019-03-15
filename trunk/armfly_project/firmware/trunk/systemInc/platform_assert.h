/** \file

$Id: gpio.c 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c) 2018 tangmingfei2013@126.com
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
#ifndef __PLATFORM_ASSERT_H
#define __PLATFORM_ASSERT_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "gpio_local.h"
/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void assert_failed(uint8_t* file, uint32_t line);

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __PLATFORM_ASSERT_H */