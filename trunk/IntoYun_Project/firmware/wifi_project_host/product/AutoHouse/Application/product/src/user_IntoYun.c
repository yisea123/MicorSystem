/** \file

$Id: user_IntoYun.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of tangmingfei2013@126.com Holding B.V. and is confidential in nature.
Under no circumstances is this software to be combined with any
Open Source Software in any way or placed under an Open Source License
of any type without the express written permission of mingfei.tang Holding B.V.
*/
/*******************************************************************************
* LOCAL INCLUDE FILES
*******************************************************************************/
#include "Includes.h"
#include "user_Action.h"
#include "platform_def.h"
#include "Interface_local.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/

 /******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static uint32_t timerID;
static uint32_t timer300msID;
static uint32_t timerID_1S;
static uint8_t wifiMontiorStep = 0;
static uint8_t wifiMontiorCnt = 0;

/*******************************************************************************
  for intoyun
*******************************************************************************/
#if defined (PROJECT_AUTOHOUSE)  
static uint8_t dpBinaryLight_1[3];
static uint16_t dpBinaryLight_1Len = 3; 
static int dpEnumLevelControl;
static int dpEnumlLazyback_1;
static int dpEnumlLazyback_2;
static int dpEnumCorridor;
static int dpEnumDesk;
static int dpEnumStair;
#endif

#if (defined PROJECT_DINGTABLE) || (defined PROJECT_KITCHEN )
static int dpEnumDingTable;
#endif 

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen);
static void vCloud_ReadDataAndControl( void );
static void vCloud_CtrlDataUpload( void );
static void vCloud_CtrlRegister( void );
static void system_wifi_StatusMonitor( void );
static void system_wifi_MonitorReset( void );

/******************************************************************************
* EXPORTED FUNCTIONS
******************************************************************************/
void userInit(void)
{
    System.setEventCallback(system_event_callback);
#if 1
    ProtocolSetupJoinAP( (char*)st_systemConfig_struct.wifissid, 
                         (char*)st_systemConfig_struct.wifiPwd);

    System.setDeviceInfo((char*)st_systemConfig_struct.productID,      //Product ID
                         (char*)st_systemConfig_struct.productSecret,  //Product secret
                         HARDWARE_VERSION_DEF,                         //hardware version
                         SOFTWARE_VERSION_DEF);                        //software version
#else

    ProtocolSetupJoinAP( (char*)WIFI_USER, 
                         (char*)WIFI_PASSWORD);

    System.setDeviceInfo((char*)st_systemConfig_struct.productID,     //Product ID
                         (char*)st_systemConfig_struct.productSecret, //Product secret
                         HARDWARE_VERSION_DEF,                        //hardware version
                         SOFTWARE_VERSION_DEF);    
#endif
    Cloud.connect();
    vCloud_CtrlRegister();

    timerID = timerGetId();
    /* Init device */
    mainCtrl.vCtrlAction_Init();
}

void userHandle (void)
{
    if(timerIsEnd(timerID, 3000))
    {
        timerID = timerGetId();

        if (Cloud.connected())
        { 
            vCloud_CtrlDataUpload();
            system_wifi_MonitorReset();
        }
        else
        {
            //Wifi is offline
            system_wifi_StatusMonitor();
        }
    }  

    if( timerIsEnd(timerID_1S, 1000))
    {
        timerID_1S = timerGetId();    
        LedBlink();
    } 

    if( timerIsEnd(timer300msID, 300))
    {
       timer300msID = timerGetId();
       vApps_BlueToothActionHandler(); 
       vApps_DebugPortActionHandler();
       RTC_GetRTC( &st_Rtc );
    }
    
    mainCtrl.vCtrlAction_Handler();
}

void vCloud_RefreshCtrlStatus( uint8_t DevType, uint8_t *buff,  uint8_t length )
{
    switch( DevType )
    {
#if defined (PROJECT_AUTOHOUSE)
      case DPID_YUN_ID_1:
        if( length == 3 )
        {
           memcpy(dpBinaryLight_1 , buff, length);
        }
        break;
        
      case DPID_YUN_ID_7:
        dpEnumLevelControl = buff[0];
        break;
        
      case DPID_YUN_ID_3:
        dpEnumlLazyback_1 = buff[0];
        break;

      case DPID_YUN_ID_4:
        dpEnumlLazyback_2 = buff[0];
        break;
        
      case DPID_YUN_ID_5:
        dpEnumCorridor =  buff[0];
        break;
        
      case DPID_YUN_ID_6:
        dpEnumDesk = buff[0];
        break;
        
      case DPID_YUN_ID_8:
        dpEnumStair = buff[0];
        break;
#endif
        
#if (defined PROJECT_DINGTABLE) || (defined PROJECT_KITCHEN )
      case DPID_YUN_ID_1:
        dpEnumDingTable = buff[0];
        break;
#endif 
        
    default:
        break;
    }
}

/* Private functions ---------------------------------------------------------*/
static void vCloud_CtrlRegister( void )
{
#if defined (PROJECT_AUTOHOUSE)  
  
    Cloud.defineDatapointBinary(DPID_YUN_ID_1, DP_PERMISSION_UP_DOWN, dpBinaryLight_1, 3);

    Cloud.defineDatapointEnum(DPID_YUN_ID_3, DP_PERMISSION_UP_DOWN, false);
    Cloud.defineDatapointEnum(DPID_YUN_ID_4, DP_PERMISSION_UP_DOWN, false);

    Cloud.defineDatapointEnum(DPID_YUN_ID_7, DP_PERMISSION_UP_DOWN, 0);

    Cloud.defineDatapointEnum(DPID_YUN_ID_5, DP_PERMISSION_UP_DOWN, false);
    Cloud.defineDatapointEnum(DPID_YUN_ID_6, DP_PERMISSION_UP_DOWN, false);

    Cloud.defineDatapointEnum(DPID_YUN_ID_8, DP_PERMISSION_UP_DOWN, false);
#endif

#if (defined PROJECT_DINGTABLE) || (defined PROJECT_DINGTABLE )   
    Cloud.defineDatapointEnum(DPID_YUN_ID_1, DP_PERMISSION_UP_DOWN, false);
#endif     
}

static void vCloud_CtrlDataUpload( void )
{
#if defined (PROJECT_AUTOHOUSE)    
    Cloud.writeDatapointBinary(DPID_YUN_ID_1, dpBinaryLight_1, 3);
    
    Cloud.writeDatapointEnum(DPID_YUN_ID_7,  dpEnumLevelControl);
    Cloud.writeDatapointEnum(DPID_YUN_ID_3,  dpEnumlLazyback_1); 
    Cloud.writeDatapointEnum(DPID_YUN_ID_4,  dpEnumlLazyback_2);

    Cloud.writeDatapointEnum(DPID_YUN_ID_5,  dpEnumCorridor); 
    Cloud.writeDatapointEnum(DPID_YUN_ID_6,  dpEnumDesk); 

    Cloud.writeDatapointEnum(DPID_YUN_ID_8,  dpEnumStair);
#endif 
 
#if (defined PROJECT_DINGTABLE) || (defined PROJECT_KITCHEN )    
    Cloud.writeDatapointEnum(DPID_YUN_ID_1,  dpEnumDingTable);
#endif     
}

static void vCloud_ReadDataAndControl( void )
{
     uint8_t buff[6];

#if defined (PROJECT_AUTOHOUSE)         
    /* light -1*/
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointBinary(DPID_YUN_ID_1, dpBinaryLight_1, &dpBinaryLight_1Len))
    {
        mainCtrl.Set_Handler( LED_TYPE, DPID_YUN_ID_1, dpBinaryLight_1, dpBinaryLight_1Len);
    }

     /*  lazyback -1 */
    else if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_3, &dpEnumlLazyback_1))
    {
        buff[0] = dpEnumlLazyback_1;
        mainCtrl.Set_Handler( LAZYBACK_TYPE, DPID_YUN_ID_3, buff, 1);
    }

     /* lazyback -2 */
    else if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_4, &dpEnumlLazyback_2))
    {
        buff[0] = dpEnumlLazyback_2;
        mainCtrl.Set_Handler( LAZYBACK_TYPE, DPID_YUN_ID_4, buff, 1);
    }

     /* TV set  */
    else if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_5, &dpEnumCorridor))
    {
        buff[0] = dpEnumCorridor;
        mainCtrl.Set_Handler( TV_TYPE, DPID_YUN_ID_5, buff, 1);
    }

     /* desk  */
    else if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_6, &dpEnumDesk))
    {
        buff[0] = dpEnumDesk;
        mainCtrl.Set_Handler( DESK_TYPE, DPID_YUN_ID_6, buff, 1);
    }
    /* bed level  */
    else if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_7, &dpEnumLevelControl))
    {
        buff[0] = dpEnumLevelControl;
        mainCtrl.Set_Handler( LIVE_TYPE, DPID_YUN_ID_7, buff, 1);
    }

    /* stair */
    else if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_8, &dpEnumStair))
    {
        buff[0] = dpEnumStair;
        mainCtrl.Set_Handler( STAIR_TYPE, DPID_YUN_ID_8, buff, 1);
    }
#endif 

#if (defined PROJECT_DINGTABLE) || (defined PROJECT_KITCHEN )
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_1, &dpEnumDingTable))
    {
        buff[0] = dpEnumDingTable;
        mainCtrl.Set_Handler( DING_TABLE_TYPE, DPID_YUN_ID_1, buff, 1);
    }
#endif

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
          break;
          case ep_network_status_connected:
          break;
          case ep_cloud_status_disconnected:
          break;
          case ep_cloud_status_connected:
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
           break;
           case ep_mode_imlink_config:
           break;
           case ep_mode_ap_config:
           break;
           case ep_mode_binding: 
           break;
           default:
           break;
       }
    }
}

static void system_wifi_StatusMonitor( void )
{
    switch( wifiMontiorStep )
    { 
      case 0:
          System.init();
          userInit(); 
          wifiMontiorStep = 1;
      break;
      
      case 1:
          wifiMontiorCnt++;
          if( wifiMontiorCnt > 20 )
          {
            wifiMontiorCnt = 0;
            wifiMontiorStep = 0;
          }
      break;
    }
}

static void system_wifi_MonitorReset( void )
{
    wifiMontiorCnt = 0;
    wifiMontiorStep = 0;   
}

/* End of this file  */

