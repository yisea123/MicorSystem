/** \file

$Id: Interface_jdq.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

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
#include "Interface_jdq.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
static uint8_t status;
static uint8_t stopEnable;
static uint8_t otherStatus;

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void vJdq_CtrlInit( CtrlJDQ_typedef *pCtrlJdq )
{
    UART *pUart = NULL;

    pUart = &st_Uart2;   
    pCtrlJdq->pf_SendPut = HAL_485WriteSerial_Port2;

    pCtrlJdq->length = &(pUart->u16_RxHead);
    pCtrlJdq->datapacket = pUart->u8_RxBuf;  
}

void vJdq_ContrlReset( CtrlJDQ_typedef *pCtrlJdq  )
{ 
    pCtrlJdq->st_JdqCtrlPara.SendCmdCnt = 0;
    pCtrlJdq->st_JdqCtrlPara.step = 0;
    stopEnable = false;
    otherStatus = JDQ_L;
    status = JDQ_L;
}

/*
Comments: JDQ_DOWN-------01, DIR = 0
          JDQ_UP---------10, DIR = 1
          JDQ_STOP-------00, DIR = 2
*/
CTRL_RESULT_ENUM eJDQ_CtrlInterface( CtrlJDQ_typedef *pJDQ, uint8_t dir)
{
    CTRL_RESULT_ENUM result = CTRL_IDLE;
    CTRL_RESULT_ENUM res;

    if( dir == JDQ_UP )
    {
        status = JDQ_H;
    }
    else if( dir == JDQ_DOWN )
    {
        status = JDQ_L;
    }
    else
    {
        status = JDQ_L;
        stopEnable = true;
    }    
    
    switch( pJDQ->st_JdqCtrlPara.step )
    {
        case 0:
         if(stopEnable)
         {
             status = JDQ_L;
         }
         
         // refresh status   
         pJDQ->st_JdqCtrlPara.SetStatus = status;
         res = jdq_Handler( pJDQ );
         if( res == CTRL_OK)
         {
             pJDQ->st_JdqCtrlPara.step = 1;
             pJDQ->st_JdqCtrlPara.SetChannel += 1;
         }
         else if( res == CTRL_FAIL )
         {
             vJdq_ContrlReset( pJDQ );
             result = CTRL_FAIL;
         }
         break;

        case 1:
         if( status == JDQ_L && (!stopEnable))
            otherStatus = JDQ_H;
         else
            otherStatus = JDQ_L;
         
          // refresh status   
         pJDQ->st_JdqCtrlPara.SetStatus = otherStatus;
         res = jdq_Handler( pJDQ );
         if( res == CTRL_OK || res == CTRL_FAIL)
         {
            vJdq_ContrlReset( pJDQ );
            return res;
         }
         break;
    }

    return result;
}

/* End of this file */
                                     