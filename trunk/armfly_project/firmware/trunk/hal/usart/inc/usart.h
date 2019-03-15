/** \file

$Id: usart.h 40486 2018-09-20 13:50:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
#ifndef __USART_H
#define __USART_H

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "gpio_local.h"
#include "uart_local.h"

/******************************************************************************
* C++ DECLARATION WRAPPER
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

void uart_Init( uint32_t BaudRate, 
                 usart_t *pUsart,
                 const board_Usart_t *const pBrdStruct);
  
void uart_SendBuffer(usart_t *pUsart, uint8_t *aTxBuffer, uint16_t nBytes );
void usart_SendByte(usart_t *pUsart, uint8_t byte);

/******************************************************************************
* END OF C++ DECLARATION WRAPPER
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __USART_H */