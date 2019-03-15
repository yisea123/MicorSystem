/**
  ******************************************************************************
  *                     (c) Copyright 2018, tangmingfei2013@126.com
  *                           All Rights Reserved
  * @file    mian.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/10
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
#include "Includes.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/

static uint32_t timer100msID;
static uint32_t timer1000msID;


static void userHandle (void)
{ 
   if( timerIsEnd(timer100msID, 100))
   {
      timer100msID = timerGetId();
      Board_LedBlink();
   }
   
   if( timerIsEnd(timer1000msID, 1000))
   {
      timer1000msID = timerGetId();
   }
}
   
int main(void)
{
    Init_System();
    AppFwUpdate_Action();
    while (1)
    {
        userHandle();
    }
}

/* end of this file  */

