/** \file

$Id: console.c 40486 2018-09-21 15:23:21Z tangmingfei2013@126.com $

Copyright (c) tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of tangmingfei2013@126.com Holding B.V.
*/
/******************************************************************************
* EXTENT INCLUDE FILES
******************************************************************************/
#include "usart.h"
#include "boarddiv.c"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "console.h"

static usart_t consoleUsart;
static const board_Usart_t *pBrdStruct = &s_com[1];
/******************************************************************************
* LOCAL MACROS AND CONSTANTS
******************************************************************************/
const char l_console_PkgId[] = "Console";

void console_Init( void )
{
    consoleUsart.pBrdStruct = pBrdStruct;
    uart_Init(115200,  &consoleUsart, pBrdStruct );
    uart_SendBuffer( &consoleUsart, "Console", sizeof("Console")); 
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the EVAL_COM1 and Loop until the end of transmission */
    //HAL_UART_Transmit(&UartHandle, (uint8_t *)&ch, 1, 0xFFFF); 
    usart_SendByte( &consoleUsart, ch);
    
    return ch;
}


/* End of this file */