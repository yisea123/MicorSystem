/*******************************************************************************
** File name:	 State.c
** Created by:	 Mingfei Tang		
** Created date: 2016/1/21		
** Version:	 V1.00			
** Descriptions:
**
**------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*******************************************************************************/
#include "includes.h"

STATE_FUNC pSt_State = State_SysActProcess;

void State_Machine( void )
{
    pSt_State((void *)pSt_State);
}

static void State_SysActProcess( void *ptr )
{
    while(1)
    {
      
    }
}

/* EOF */