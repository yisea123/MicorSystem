/** \file

$Id: spi.h 40486 2018-09-21 13:50:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
#ifndef __SPI_H
#define __SPI_H

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

void spi_Impl_Init( void );
uint8_t spif_Impl_SendByte( uint8_t Data );

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __SPI_H */

