/** \file

$Id: Interface_inclin.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#include "Interface_inclin.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vClin_Init( Inclin_typedef *pCtrl )
{
    UART *pUart = &st_Uart2;

    pCtrl->pf_SendPut = HAL_485WriteSerial_Port2;
    pCtrl->length = &(pUart->u16_RxHead);
    pCtrl->datapacket = pUart->u8_RxBuf; 
    pCtrl->address = INCLIN_ADD;
}

void vClin_InterfaceReset( Inclin_typedef *pCtrl  )
{
    vInclin_Reset( pCtrl );
}

CTRL_RESULT_ENUM eClin_Interface( Inclin_typedef *pCtrl )
{
    return Inclin_ReadValue( pCtrl );
}


/* End of this file */