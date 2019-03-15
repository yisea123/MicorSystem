/**************************************************** **************************
* File Name          : user_SysMOnitor.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 2018/7/27
* Description        : system status monitor
********************************************************************************
*/
#include "Includes.h"
#include "ctrl_Def.h"
#include "ctrl_Motor.h"
#include "ctrl_Device.h"
#include "ctrl_Presence.h"
#include "ctrl_JDQ.h"
#include "ctrl_Light.h"
#include "ctrl_JdSensor.h"
#include "ctrl_Interface.h"
#include "user_Action.h"
#include "user_SysMonitor.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static MSG st_MonitorMsg;
static Presence_TypeDef st_Presence;
static CtrL_typedef st_CtrlTypdef;

static uint8_t step = 0;
static uint8_t deviceCnt = 0;

static CtrlMotor_typedef st_CtrlMotor;
static AllMotorStatus_typedef st_AllMotorStatus;

/* Private function prototypes -----------------------------------------------*/
static CTRL_RESULT_ENUM user_ShutOffDevice( uint8_t DevType );

static CTRL_RESULT_ENUM user_ShutOffDevice( uint8_t DevType )
{
    CTRL_RESULT_ENUM e_res= CTRL_IDLE;
    st_CtrlJDQ.pCtrL_typedef = &st_CtrlTypdef;
    
    switch( step )
    {
    case 0:
    default:
      st_CtrlTypdef.deviceID = DevType;
      st_CtrlTypdef.addres = JDQ_CH8_ADD; 
      st_CtrlTypdef.b_ctrlres[0] = JDQ_DOWN;
      step = 1;
      break;
    case 1:
      /* control devices  */
      e_res = jdqCtrl.eJDQ_Handler( &st_CtrlJDQ );
      if( e_res == CTRL_OK  || e_res == CTRL_FAIL )
      {
          step = 0; 
          jdqCtrl.vJDQ_Reset( &st_CtrlJDQ );
      }      
      break;
    }
    
    return e_res;
}


CTRL_RESULT_ENUM user_GetAllDeviceStatus( void )
{
    CTRL_RESULT_ENUM e_res= CTRL_IDLE;

    switch( deviceCnt )
    {
    case 0:
    default:
        e_res = user_ShutOffDevice( LAZYBACK_1_ID );
        if( e_res == CTRL_OK  || e_res == CTRL_FAIL )
        {
              deviceCnt = 1;
              st_MonitorMsg.DeviceTypeFlags_bit.JDQ_Dev_1 = e_res;
        }
        break;
    case 1:
        e_res = user_ShutOffDevice( LAZYBACK_2_ID );
        if( e_res == CTRL_OK  || e_res == CTRL_FAIL )
        {
              deviceCnt = 2;
              st_MonitorMsg.DeviceTypeFlags_bit.JDQ_Dev_1 = e_res;
        }
        break;
    case 2:
        e_res = user_ShutOffDevice( STAIR_ID );
        if( e_res == CTRL_OK  || e_res == CTRL_FAIL )
        {
              deviceCnt = 3;
              st_MonitorMsg.DeviceTypeFlags_bit.JDQ_Dev_1 = e_res;
        }
        break;
    case 3:
        e_res = user_ShutOffDevice( DESK_ID );
        if( e_res == CTRL_OK  || e_res == CTRL_FAIL )
        {
              deviceCnt = 4;
              st_MonitorMsg.DeviceTypeFlags_bit.JDQ_Dev_1 = e_res;
        }
        break;
    case 4:
        e_res = presenceCtrl.vPensence_ReadValue( &st_Presence );
         if( e_res == CTRL_OK  || e_res == CTRL_FAIL )
         {
              st_MonitorMsg.PingTaiDevFlags_bit.Presence = e_res;
              deviceCnt = 5;
         }
         break;
    case 5:     /* Check motor status */
         e_res = motorCtrl.eMotor_CheckError( &st_CtrlMotor );
         if( e_res == CTRL_OK )
         {
              motorCtrl.vMotor_GetStatus( &st_AllMotorStatus );
              st_MonitorMsg.PingTaiDevFlags_bit.Motor_1 = st_AllMotorStatus.st_Motor1Status.Onlive;
              st_MonitorMsg.PingTaiDevFlags_bit.Motor_2 = st_AllMotorStatus.st_Motor2Status.Onlive;
              st_MonitorMsg.PingTaiDevFlags_bit.Motor_3 = st_AllMotorStatus.st_Motor3Status.Onlive;
              st_MonitorMsg.PingTaiDevFlags_bit.Motor_4 = st_AllMotorStatus.st_Motor4Status.Onlive;
              deviceCnt = 0;
              return CTRL_OK;
         }
         break;
    }

    return  CTRL_IDLE;
}

/* End of this file */

