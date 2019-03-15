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
#ifndef __GPIO_LOCAL_H
#define __GPIO_LOCAL_H

typedef struct stm32Flib_gpioOpMode_t
{
  GPIOMode_TypeDef Mode;                  
  GPIOSpeed_TypeDef Speed;
  uint32_t Pull;
  uint32_t Alternate; 
} stm32Flib_gpioOpMode_t;  
 
typedef stm32Flib_gpioOpMode_t gpio_OpMode_t;


#endif /* __GPIO_LOCAL_H */