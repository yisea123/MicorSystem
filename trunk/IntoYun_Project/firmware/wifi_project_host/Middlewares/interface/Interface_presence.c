/** \file

$Id: interface_presence.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/

/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "board.h"
#include "usart.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "presence.h"
#include "Interface_presence.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/


/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/


/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vPresence_Init( Presence_TypeDef *pPresence )
{
    UART *pUart = &st_Uart2;
    
    pPresence->pf_SendPut = HAL_485WriteSerial_Port2;
    pPresence->length = &(pUart->u16_RxHead);
    pPresence->datapacket = pUart->u8_RxBuf;
    vPresence_Reset( pPresence );
}

void vPresence_Reset( Presence_TypeDef *pPresence )
{
    memset( pPresence->datapacket, 0, UART_RXBUFFSIZE);
    pPresence->step = PENSENCE_ID;
    pPresence->retry = 0;
}

CTRL_RESULT_ENUM vPresence_Interface( Presence_TypeDef *pPresence )
{
    CTRL_RESULT_ENUM e_res;
  
    e_res =   vPresence_ReadValue( pPresence );
    if( e_res == CTRL_OK || e_res == CTRL_FAIL  )
    {
           vPresence_Reset( pPresence );
    }
    
    return e_res;
}

/* End of files */

