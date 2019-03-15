/**
  ******************************************************************************
  * @file    Src/user/Ctr_Interface.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/20
  * @brief   system control interface
  * @documents 
  ******************************************************************************
  */
/* Includes -------------------------------------------------------------------*/
#include "board.h"
#include "ctrl_Def.h"
#include "ctrl_Presence.h"
#include "ctrl_Light.h"
#include "ctrl_jdSensor.h"
#include "ctrl_jdq.h"
#include "ctrl_Motor.h"
#include "ctrl_Interface.h"
#include "usart.h" 

/* Private typedef ------------------------------------------------------------*/
/*
  Ctrol action interface
*/

/* Private define -------------------------------------------------------------*/
/* Private macro --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------*/
/*
   presence sensor
*/
void Ctrl_PresenceInit(Presence_TypeDef *pPre_typedef)
{
    UART *pUart = &st_Uart2;
    
    pPre_typedef->pf_SendPut = HAL_485WriteSerial_Port2;
    pPre_typedef->length = &(pUart->u16_RxHead);
    pPre_typedef->datapacket = pUart->u8_RxBuf;
}

/*
  light sensor
*/
void Ctrl_LightInit( void )
{
    UART *pUart = &st_Uart2;
    
    st_CtrlLight_lib.pf_SendPut = HAL_485WriteSerial_Port2;
    st_CtrlLight_lib.length = &(pUart->u16_RxHead);
    st_CtrlLight_lib.datapacket = pUart->u8_RxBuf;
    
    vLight_Init();
}

void Ctrl_jdSensorInit( CtrlJQSensor_typedef *pJd_typedef )
{
    UART *pUart = &st_Uart2;
    
    pJd_typedef->pf_SendPut = HAL_485WriteSerial_Port2;
    pJd_typedef->length = &(pUart->u16_RxHead);
    pJd_typedef->datapacket = pUart->u8_RxBuf;
}

void Ctrl_jdqInit( CtrlJDQ_typedef *pJDQ_typedef )
{
    UART *pUart = &st_Uart2;
    
    pJDQ_typedef->pf_SendPut = HAL_485WriteSerial_Port2;
    pJDQ_typedef->length = &(pUart->u16_RxHead);
    pJDQ_typedef->datapacket = pUart->u8_RxBuf;
}

void Ctrl_motorInit( CtrlMotor_typedef *pCtrlMotor )
{
    UART *pUart = &st_Uart1;
    
    pCtrlMotor->pf_SendPut = HAL_485WriteSerial_Port1;
    pCtrlMotor->length = &(pUart->u16_RxHead);
    pCtrlMotor->datapacket = pUart->u8_RxBuf;
    
    vMotor_CtrlReset();
}
/*******************************************************************************
*                     interface for device
********************************************************************************/
/*
   电机控制
*/
const vMotor_t motorCtrl = 
{
    Ctrl_motorInit,
    vMotor_CtrlReset,
    vMotor_CtrInterface,
    vMotor_GetStatus,
    eMotor_CheckError,
    vMotor_CtrInterfaceTV,
};
/*
   倾角 Sensor
*/
const vJdSensor_t jdSensorCtrl = 
{
    Ctrl_jdSensorInit,
    vJdSensor_CtrlInterfaceReset,
    JdSensor_ReadValue,
};

/*
   继电器控制
*/
const vJDQ_t jdqCtrl =
{
    Ctrl_jdqInit,
    eJDQ_CtrlInterface,
    vJDQ_ContrlReset,
};

/*
   人体感应sensor
*/
const vPresence_t presenceCtrl =
{
    vPresence_ActionProcess,
    Ctrl_PresenceInit,
};

/*
   灯控制
*/
const vlightCtrl_t lightCtrl =
{
    Ctrl_LightInit,
    vLight_ContrlTurnOn,
    vLight_ContrlTurnOff,
    vLight_ScanUID,
    eLight_CtrlInterface,
    vLight_CtrlReset,
};

/*End of this file */