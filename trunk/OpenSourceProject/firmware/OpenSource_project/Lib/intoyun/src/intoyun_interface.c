/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/
#include "intoyun_interface.h"
#include "intoyun_hal.h"


const system_t System =
{
    intoyunInit,
    intoyunLoop,
    intoyunSetEventCallback,
    intoyunSetMode,
    intoyunGetMode,
    intoyunDatapointControl,
    intoyunSetDevice,
    intoyunGetDevice,
    intoyunGetInfo,
    intoyunExecuteRestart,
    intoyunExecuteRestore,
    intoyunPutPipe,
    intoyunGetNetTime,
    intoyunGetStatus,
};

const cloud_t Cloud =
{
    intoyunConnect,
    intoyunConnected,
    intoyunDisconnect,
    intoyunDisconnected,

    #ifdef CONFIG_INTOYUN_DATAPOINT
    intoyunDefineDatapointBool,
    intoyunDefineDatapointNumber,
    intoyunDefineDatapointEnum,
    intoyunDefineDatapointString,
    intoyunDefineDatapointBinary,

    intoyunReadDatapointBool,
    intoyunReadDatapointNumberInt32,
    intoyunReadDatapointNumberDouble,
    intoyunReadDatapointEnum,
    intoyunReadDatapointString,
    intoyunReadDatapointBinary,

    intoyunWriteDatapointBool,
    intoyunWriteDatapointNumberInt32,
    intoyunWriteDatapointNumberDouble,
    intoyunWriteDatapointEnum,
    intoyunWriteDatapointString,
    intoyunWriteDatapointBinary,

    intoyunSendDatapointBool,
    intoyunSendDatapointNumberInt32,
    intoyunSendDatapointNumberDouble,
    intoyunSendDatapointEnum,
    intoyunSendDatapointString,
    intoyunSendDatapointBinary,

    intoyunSendAllDatapointManual,
    #endif
    intoyunSendCustomData,
};

#ifdef CONFIG_INTOYUN_KEY
const keys_t Key = {
    intoyunKeyInit,
    intoyunKeySetParams,
    intoyunKeyRegister,
    intoyunKeyClickCb,
    intoyunKeyDoubleClickCb,
    intoyunKeyPressStartCb,
    intoyunKeyPressStopCb,
    intoyunKeyPressDuringCb,
    intoyunKeyLoop,
};
#endif

#ifdef CONFIG_INTOYUN_TIMER
const timers_t Timer = {
    intoyunTimerRegister,
    intoyunTimerChangePeriod,
    intoyunTimerStart,
    intoyunTimerStop,
    intoyunTimerReset,
    intoyunTimerLoop,
};
#endif

void delay(uint32_t ms)
{
    uint32_t start_millis = HAL_Millis();
    uint32_t current_millis = 0;
    uint32_t elapsed_millis = 0;

    if (ms == 0) 
      return;
    
    while (1) 
    {
        current_millis = HAL_Millis();
        if (current_millis < start_millis)
        {
            elapsed_millis =  UINT_MAX - start_millis + current_millis;
        } 
        else 
        {
            elapsed_millis = current_millis - start_millis;
        }

        if (elapsed_millis > ms) 
        {
            break;
        }
        intoyunLoop();
    }
}

uint32_t millis(void)
{
    return HAL_Millis();
}
