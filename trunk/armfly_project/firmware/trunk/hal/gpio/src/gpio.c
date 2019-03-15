/** \file

$Id: gpio.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "gpio.h"

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/
#include "platform_type.h"

const char l_gpio_PkgId[] = "gpio";
/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void gpio_ConfigPin(const gpio_Pin_t *pPin)
{
#if defined (HAL_STM32F1)  
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = pPin->opMode.Mode;
    GPIO_InitStruct.GPIO_Speed = pPin->opMode.Speed;
    GPIO_InitStruct.GPIO_Pin = (uint32_t)pPin->pin;
    
    GPIO_Init(pPin->pBlock, &GPIO_InitStruct);
#endif
    
#if defined ( HAL_STM32F4 )
    GPIO_InitTypeDef  GPIO_InitStruct;
    
    GPIO_InitStruct.Pin =  pPin->pin;
    GPIO_InitStruct.Mode = pPin->opMode.Mode;
    GPIO_InitStruct.Pull =  pPin->opMode.Pull;
    GPIO_InitStruct.Speed =  pPin->opMode.Speed;
    GPIO_InitStruct.Alternate = pPin->opMode.Alternate;
    
    HAL_GPIO_Init(pPin->pBlock, &GPIO_InitStruct);
#endif  
}

void gpio_SetPin(const gpio_Pin_t *pPin, bool state)
{
#if defined ( HAL_STM32F4 )    
  if (pPin->polarity == state)
  {
      HAL_GPIO_WritePin(pPin->pBlock, pPin->pin, GPIO_PIN_SET);
  }
  else
  {
      HAL_GPIO_WritePin(pPin->pBlock, pPin->pin, GPIO_PIN_RESET);
  }
#endif   
}

void gpio_TogglePin(const gpio_Pin_t *pPin)
{
#ifdef ASSERT
  assert(s_initDone);
#endif
  
#if defined ( HAL_STM32F4 )  
  HAL_GPIO_TogglePin(pPin->pBlock, pPin->pin);
#endif    
}

bool gpio_GetPin(const gpio_Pin_t *pPin)
{
  bool pinStatus;
#ifdef ASSERT
  assert(s_initDone);
#endif
  
#if defined ( HAL_STM32F4 )  
  pinStatus = MAKE_BOOL(HAL_GPIO_ReadPin(pPin->pBlock, pPin->pin));
#endif
  
  return MAKE_BOOL(pinStatus == pPin->polarity);
}

bool gpio_GetInputPin(const gpio_Pin_t *pPin)
{
  bool pinStatus;

#ifdef ASSERT
  assert(s_initDone);
#endif
  
#if defined ( HAL_STM32F4 )  
  pinStatus = MAKE_BOOL(HAL_GPIO_ReadPin(pPin->pBlock, pPin->pin));
#endif
  
  return MAKE_BOOL(pinStatus == pPin->polarity);
}

/* End of this file */