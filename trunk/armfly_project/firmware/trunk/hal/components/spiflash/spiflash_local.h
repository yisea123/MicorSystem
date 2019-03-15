/** \file

$Id: spiflash_local.h 40486 2018-09-21 13:50:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
#ifndef __SPIFLASH_LOCAL_H
#define __SPIFLASH_LOCAL_H
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
* EXPORTED TYPES
******************************************************************************/
typedef struct {
    uint8_t prodVer;
    uint8_t staRegByte;
    uint16_t ID;
    uint16_t res;
    uint16_t pageSize;
    uint32_t pageTotal;
    uint32_t memSize;
} Flash_Info;

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif // __SPIFLASH_LOCAL_H

