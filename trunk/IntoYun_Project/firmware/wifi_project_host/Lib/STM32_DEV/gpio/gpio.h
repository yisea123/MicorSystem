/** \file

$Id: tim.c 40486 2018-08-08 13:50:21Z mingfei.tang @philips.com $

Copyright (c) 2016 Philips Lighting Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of Philips Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of Philips Lighting Holding B.V.
*/
#ifndef __GPIO_H
#define __GPIO_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "stm32f10x.h"
#include <stdbool.h>

#include "gpio_local.h"
/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

typedef struct gpio_Pin_t
{
    GPIO_TypeDef*   pBlock;   //!< The GPIO block
    uint8_t         pin;          //!< The pin number
    gpio_OpMode_t   opMode;
    bool          polarity;    //!< The pin polarity
} gpio_Pin_t;  
  
/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */
