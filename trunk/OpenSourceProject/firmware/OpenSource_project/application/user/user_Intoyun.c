/**
  ******************************************************************************
  *                              (c) Copyright 2018, tangmignfei2013@126.com
  *                                      All Rights Reserved
  * @file    user_Intoyun.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/07/17
  * @brief   McsParser ctrl interface
  * @description:
    This source code and any compilation or derivative thereof is the proprietary
    information of mingfei.tang and is confidential in nature.
    Under no circumstances is this software to be combined with any
    Open Source Software in any way or placed under an Open Source License
    of any type without the express written permission of mingfei.tang
  ******************************************************************************
**/
/* Includes -------------------------------------------------------------------*/
#include "Includes.h"
#include "user_Intoyun.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define    LED_TYPE                           1

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static bool dpBoolLED_1;
static bool dpBoolLED_2;
static double dpDoubleTemperature;                       // 温度值
static double dpDoubleHuminity;                          // 湿度值

static uint32_t count;
static uint32_t timerID;
static uint32_t timerIDWat;
static uint32_t timer50msID;
static uint32_t timer300msID;
static uint32_t timer100msID;
static uint32_t timerID_1S;
/*******************************************************************************
  for intoyun
*******************************************************************************/

/* Private function prototypes -----------------------------------------------*/
static void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen);
static void vCloud_ReadDataAndControl( void );
static void vCloud_CtrlDataUpload( void );
static void vCloud_CtrlRegister( void );

void userInit(void)
{
    /* 定义事件回调 */
    System.setEventCallback(system_event_callback);

    /* 配置wifi 账号和密码 */
    ProtocolSetupJoinAP( (char*)WIFI_USER, 
                         (char*)WIFI_PASSWORD);
    /* 关联设备信息 */
    System.setDeviceInfo(PRODUCT_ID_DEF,     //Product ID
                         PRODUCT_SECRET_DEF, //Product secret
                         HARDWARE_VERSION_DEF,                        //hardware version
                         SOFTWARE_VERSION_DEF);
    Cloud.connect();
    vCloud_CtrlRegister();

    /* 定义系统定时器 */
    timerID = timerGetId();
    timerIDWat = timerGetId();
    
}

void IntoYunuserHandle (void)
{
    static int32_t s_TempData; 
    static int32_t s_RhData; 

   if( timerIsEnd(timer50msID, 50))
   {
      timer50msID = timerGetId();
      vApps_DebugPortActionHandler();
   }  
  
    /* 处理间隔，用户可自行更改 */
    if(timerIsEnd(timerID, 3000))
    {
        timerID = timerGetId();

        /* 更新数据点数据（数据点具备上送属性） */
        if (Cloud.connected())
        { 
           vCloud_CtrlDataUpload();
        }
        log_v("system work count: %d \r\n", count);
    }  

    if( timerIsEnd(timerID_1S, 1000))
    {
        timerID_1S = timerGetId();
       
        Board_LedBlink();
        AppFwUpdate_Finish();
        UploadSht20_Action( count );
        if( count > 65535)
          count = 0;
        else
          count++;
        
        sht2xdrv_GetTemp( &s_TempData );
        sht2xdrv_GetRH( &s_RhData );
        
        dpDoubleTemperature = s_TempData*0.01;
        dpDoubleHuminity = s_RhData*0.01;
    }

    if( timerIsEnd(timerIDWat, 500))
    {
       timerIDWat = timerGetId();
    }

    if( timerIsEnd(timer100msID, 100))
    {
       timer100msID = timerGetId();
    }   

    if( timerIsEnd(timer300msID, 300))
    {
       timer300msID = timerGetId();
    }
}

/* Private functions ---------------------------------------------------------*/
static void vCloud_CtrlRegister( void )
{
    /* 定义产品数据点 */
    Cloud.defineDatapointBool(DPID_BOOL_LIGHT_1, DP_PERMISSION_UP_DOWN, false);        /* 1号灯*/
    Cloud.defineDatapointBool(DPID_BOOL_LIGHT_2, DP_PERMISSION_UP_DOWN, false);        /* 2号灯*/

    Cloud.defineDatapointNumber(DPID_DOUBLE_TEMPERATURE, DP_PERMISSION_UP_ONLY, 0, 100, 1, 0); //温度值
    Cloud.defineDatapointNumber(DPID_DOUBLE_HUMINITY, DP_PERMISSION_UP_ONLY, 0, 100, 1, 0); //湿度值
}

static void vCloud_CtrlDataUpload( void )
{ 
    Cloud.writeDatapointBool(DPID_BOOL_LIGHT_1,  dpBoolLED_1);          /* 1号灯*/
    Cloud.writeDatapointBool(DPID_BOOL_LIGHT_2,  dpBoolLED_2);          /* 2号灯*/

    Cloud.writeDatapointNumberDouble(DPID_DOUBLE_TEMPERATURE, dpDoubleTemperature);
    Cloud.writeDatapointNumberDouble(DPID_DOUBLE_HUMINITY, dpDoubleHuminity);    
}

static void vCloud_ReadDataAndControl( void )
{   
     /* 1 号灯控制 */
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointBool(DPID_BOOL_LIGHT_1, &dpBoolLED_1))
    {
        if( dpBoolLED_1 )
        {
            LED_SystemRun( 0 );
        }
        else
        {
            LED_SystemRun( 1 );
        }
    }
    
     /* 2 号灯控制 */
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointBool(DPID_BOOL_LIGHT_2, &dpBoolLED_2))
    {
      
    }
}

static void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen)
{
    if (event == event_cloud_data)
    {
      switch (param)
      {
          case ep_cloud_data_datapoint:
          vCloud_ReadDataAndControl();
          break;
          case ep_cloud_data_custom:
          break;
          default:
          break;
      }
    }
    else if (event == event_network_status)
    {
      switch (param)
      {
          case ep_network_status_disconnected:
              log_v("模组已断开路由器 \r\n");
          break;
          case ep_network_status_connected:
              log_v("模组已连接路由器 \r\n");
          break;
          case ep_cloud_status_disconnected:
              log_v("模组已断开平台 \r\n");
          break;
          case ep_cloud_status_connected: 
              log_v("模组已连接平台 \r\n");
          break;
          default:
          break;
       }
    }
    else if (event == event_mode_changed)
    {
       switch (param)
       {
           case ep_mode_normal:  
              log_v("模组已处于正常工作模式 \r\n");
           break;
           case ep_mode_imlink_config:    
              log_v("模组已处于imlink配置模式 \r\n");
           break;
           case ep_mode_ap_config:
              log_v("模组已处于ap配置模式 \r\n");
           break;
           case ep_mode_binding: 
              log_v("模组已处于绑定模式 \r\n");  
           break;
           default:
           break;
       }
    }
}
/* End of this file */



