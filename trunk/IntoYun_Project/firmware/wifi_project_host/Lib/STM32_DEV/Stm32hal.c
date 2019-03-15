/** \file

$Id: Stm32hal.c 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "includes.h"

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
#define UINT_MAX    0xFFFFFFFF

static __IO uint32_t uwTick;
static bool ledFlag = false;

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
uint32_t HAL_GetTick(void)
{
  return uwTick;
}

void LedBlink(void)
{
    ledFlag = !ledFlag;
    LED_SystemRun( ledFlag );
}

void HAL_IncTick(void)
{
    uwTick++;
}

void HAL_Delay(__IO uint32_t Delay)
{
    uint32_t tickstart = 0;
    tickstart = HAL_GetTick();
    while((HAL_GetTick() - tickstart) < Delay)
    {
    }
}

bool HAL_timerIsEnd(uint32_t timerID, uint32_t time)
{
    uint32_t elapsed_millis = 0;
    uint32_t current_millis = HAL_GetTick();

    //Check for wrapping
    if (current_millis < timerID)
    {
        elapsed_millis =  UINT_MAX-timerID + current_millis;
    } 
    else 
    {
        elapsed_millis = current_millis - timerID;
    }

    if (elapsed_millis >= time)
    {
        return true;
    }
    
    return false;
}

uint32_t HAL_timerGetId(void)
{
    return HAL_GetTick();
}

/* End of this file */
