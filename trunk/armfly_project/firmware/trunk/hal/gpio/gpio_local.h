/** \file

$Id: gpio_local.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c) 2018 tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/
#ifndef __GPIO_LOCAL_H
#define __GPIO_LOCAL_H

#if defined (HAL_STM32F1)
#include "stm32f10x.h"
#endif

#if defined ( HAL_STM32F4 )
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal.h"
#endif

#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct stm32Flib_gpioOpMode_t
{
#if defined ( HAL_STM32F1 )
  GPIOMode_TypeDef Mode;                  
  GPIOSpeed_TypeDef Speed;
  uint32_t Pull;
  uint32_t Alternate; 
#endif

#if defined ( HAL_STM32F4 )
  uint32_t Mode; 
  uint32_t Pull; 
  uint32_t Speed;
  uint32_t Alternate;
#endif

}stm32Flib_gpioOpMode_t;  
 
typedef stm32Flib_gpioOpMode_t gpio_OpMode_t;

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_LOCAL_H */