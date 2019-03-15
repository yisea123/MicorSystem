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
#ifndef __GPIO_H
#define __GPIO_H

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

typedef struct gpio_Pin_t
{
#if defined (HAL_STM32F1)
    GPIO_InitTypeDef*   pBlock;   //!< The GPIO block
#endif
    
#if defined ( HAL_STM32F4 )
    GPIO_TypeDef*  pBlock;
#endif  
    uint16_t            pin;      //!< The pin number
    gpio_OpMode_t       opMode;
    bool                polarity; //!< The pin polarity
} gpio_Pin_t;  
 
/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void gpio_ConfigPin(const gpio_Pin_t *pPin);
void gpio_SetPin(const gpio_Pin_t *pPin, bool state);
void gpio_TogglePin(const gpio_Pin_t *pPin);
bool gpio_GetPin(const gpio_Pin_t *pPin);
bool gpio_GetInputPin(const gpio_Pin_t *pPin);

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H */
