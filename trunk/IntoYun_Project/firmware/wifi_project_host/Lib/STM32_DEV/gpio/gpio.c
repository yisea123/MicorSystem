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

/******************************************************************************
* EXTERNAL INCLUDE FILES
******************************************************************************/
#include "gpio.h"

/*!
 * @pre For STM32, PC13, PC14 and PC15 shall be driven at 2Mhz only.
 */
void gpio_ConfigPin(const gpio_Pin_t *pPin)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = pPin->opMode.Mode;
    GPIO_InitStruct.GPIO_Speed = pPin->opMode.Speed;
    GPIO_InitStruct.GPIO_Pin = (uint32_t)pPin->pin;
    GPIO_Init(pPin->pBlock, &GPIO_InitStruct);
}

/* End of this file */