/** \file

$Id: user_IntoYun.c 40486 2018-08-08 13:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Lighting Holding B.V. and is confidential in nature.
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
#define LED_TYPE                           0

 /******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static uint32_t timerID;
static uint32_t timer300msID;
static uint32_t timerID_1S;

/*******************************************************************************
  for intoyun
*******************************************************************************/
#if LED_TYPE
bool dpBoolLED_1;
//bool dpBoolLED_2;
#else
static uint8_t dpBinaryLight_1[3];
static uint16_t dpBinaryLight_1Len = 3; 

//static uint8_t dpBinaryLight_2[3]; 
//static uint16_t dpBinaryLight_2Len = 3;
#endif

static int dpEnumLevelControl;

static int dpEnumlLazyback_1;
static int dpEnumlLazyback_2;
static int dpEnumCorridor;
static int dpEnumDesk;
static int dpEnumStair;


/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen);
static void vCloud_ReadDataAndControl( void );
static void vCloud_CtrlDataUpload( void );
static void vCloud_CtrlRegister( void );

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
    }
    
    mainCtrl.vCtrlAction_Handler();
}

void vCloud_RefreshCtrlStatus( uint8_t DevType, uint8_t *buff,  uint8_t length )
{
    switch( DevType )
    {
      case DPID_YUN_ID_1:
        if( length == 3 )
        {
           memcpy(dpBinaryLight_1 , buff, length);
        }
        break;
      /*
      case DPID_YUN_ID_2:
        if( length == 3 )
        {
           memcpy(dpBinaryLight_2 , buff, length);
        }
        break;
      */
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
    }
}

/* Private functions ---------------------------------------------------------*/
static void vCloud_CtrlRegister( void )
{
#if LED_TYPE
    Cloud.defineDatapointBool(DPID_YUN_ID_1, DP_PERMISSION_UP_DOWN, false);
    //Cloud.defineDatapointBool(DPID_YUN_ID_2, DP_PERMISSION_UP_DOWN, false);
#else    
    Cloud.defineDatapointBinary(DPID_YUN_ID_1, DP_PERMISSION_UP_DOWN, dpBinaryLight_1, 3);
   // Cloud.defineDatapointBinary(DPID_YUN_ID_2, DP_PERMISSION_UP_DOWN, dpBinaryLight_2, 3);
#endif 

    Cloud.defineDatapointEnum(DPID_YUN_ID_3, DP_PERMISSION_UP_DOWN, false);
    Cloud.defineDatapointEnum(DPID_YUN_ID_4, DP_PERMISSION_UP_DOWN, false);

    Cloud.defineDatapointEnum(DPID_YUN_ID_7, DP_PERMISSION_UP_DOWN, 0);

    Cloud.defineDatapointEnum(DPID_YUN_ID_5, DP_PERMISSION_UP_DOWN, false);
    Cloud.defineDatapointEnum(DPID_YUN_ID_6, DP_PERMISSION_UP_DOWN, false);

    Cloud.defineDatapointEnum(DPID_YUN_ID_8, DP_PERMISSION_UP_DOWN, false);
}

static void vCloud_CtrlDataUpload( void )
{ 
  
#if LED_TYPE
    Cloud.writeDatapointBool(DPID_YUN_ID_1,  dpBoolLED_1);
    //Cloud.writeDatapointBool(DPID_YUN_ID_2,  dpBoolLED_2);
#else    
    Cloud.writeDatapointBinary(DPID_YUN_ID_1, dpBinaryLight_1, 3);
    //Cloud.writeDatapointBinary(DPID_YUN_ID_2, dpBinaryLight_2, 3); 
#endif
    
    Cloud.writeDatapointEnum(DPID_YUN_ID_7,  dpEnumLevelControl);
    Cloud.writeDatapointEnum(DPID_YUN_ID_3,  dpEnumlLazyback_1); 
    Cloud.writeDatapointEnum(DPID_YUN_ID_4,  dpEnumlLazyback_2);

    Cloud.writeDatapointEnum(DPID_YUN_ID_5,  dpEnumCorridor); 
    Cloud.writeDatapointEnum(DPID_YUN_ID_6,  dpEnumDesk); 

    Cloud.writeDatapointEnum(DPID_YUN_ID_8,  dpEnumStair);
}

static void vCloud_ReadDataAndControl( void )
{
     uint8_t buff[6];
#if LED_TYPE
    /* light -1*/
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointBool(DPID_YUN_ID_1, &dpBoolLED_1))
    {
        buff[0] = dpBoolLED_1;
        mainCtrl.Set_Handler( LED_TYPE, DPID_YUN_ID_1, buff, 1);
    }
    
    /* light -2 */
    /*
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointBool(DPID_YUN_ID_2, &dpBoolLED_2))
    {
        buff[0] = dpBoolLED_2;
        mainCtrl.Set_Handler( LED_TYPE, DPID_YUN_ID_2, buff, 1);
    }
    */
#else
    /* light -1*/
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointBinary(DPID_YUN_ID_1, dpBinaryLight_1, &dpBinaryLight_1Len))
    {
        mainCtrl.Set_Handler( LED_TYPE, DPID_YUN_ID_1, dpBinaryLight_1, dpBinaryLight_1Len);
    }
    
    /* light -2 */
    /*
    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointBinary(DPID_YUN_ID_2, dpBinaryLight_2, &dpBinaryLight_2Len))
    {
        mainCtrl.Set_Handler( LED_TYPE, DPID_YUN_ID_2, dpBinaryLight_2, dpBinaryLight_2Len);
    }
    */
#endif
    
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

/* End of this file  */

