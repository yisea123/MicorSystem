/** \file

$Id: i2c_Init.h 52068 2018-05-15 03:50:28Z yong.huang@lighting.com $

Copyright (c) 2016 Philips Lighting Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of Philips Lighting Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of Philips Lighting Holding B.V.
*/

#ifndef __I2C_INIT_H
#define __I2C_INIT_H

/*******************************************************************************
* EXTENT INCLUDE FILES
*******************************************************************************/
#include "gpio_local.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* EXPORTED TYPES
******************************************************************************/
typedef DMA_Stream_TypeDef DMA_Channel_t;

typedef struct i2c_peripheral_t
{
  uint8_t     id;
  I2C_TypeDef *pI2C;
  int8_t    i2cIrqId;
  DMA_Channel_t *const dmaTxChannel;
  DMA_Channel_t *const dmaRxChannel;
  int8_t    dmaTxIrqId;
  uint32_t  dmaTxRequest;
  int8_t    dmaRxIrqId;
  uint32_t  dmaRxRequest;
} i2c_peripheral_t;

/******************************************************************************
* EXPORTED MACROS AND CONSTANTS
******************************************************************************/

/*!
 * @brief
 */

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/

/*!
 * @brief Initializes the package
 */

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // __I2C_INIT_H
