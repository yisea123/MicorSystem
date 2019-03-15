/**************************************************** **************************
* File Name          : user_IntoYun.c
* Author             : Mingfei Tang
* Version            : V1.0.0
* Date               : 2018/2/10
* Description        : for wifi project host
********************************************************************************
*/
#include "Includes.h"
#include "user_Action.h"
#include "platform_def.h"
#include "Interface_local.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t count;
static uint32_t timerID;
static uint32_t timerIDWat;
static uint32_t timer300msID;
static uint32_t timer100msID;
static uint32_t timerID_1S;
/*******************************************************************************
  for intoyun
*******************************************************************************/
static int  dpEnumLevelControl;

/* Private function prototypes -----------------------------------------------*/
static void system_event_callback(system_event_t event, int param, uint8_t *data, uint16_t datalen);
static void vCloud_ReadDataAndControl( void );
static void vCloud_CtrlDataUpload( void );
static void vCloud_CtrlRegister( void );

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
    timerIDWat = timerGetId();
    
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
        log_v("system work count: %d \r\n", count);
    }  

    if( timerIsEnd(timerID_1S, 1000))
    {
        timerID_1S = timerGetId();    
        LedBlink();                           
    }

    if( timerIsEnd(timerIDWat, 500))
    {
       timerIDWat = timerGetId();
    }

    if( timerIsEnd(timer100msID, 100))
    {
       timer100msID = timerGetId();
       mainCtrl.Motor_Handler();
    }   

    if( timerIsEnd(timer300msID, 300))
    {
       timer300msID = timerGetId();
       vApps_BlueToothActionHandler();  
       vApps_DebugPortActionHandler(); 
    }
}

void vCloud_RefreshCtrlStatus( uint8_t DevType, uint8_t *buff,  uint8_t length )
{
    switch( DevType )
    {
      case DPID_YUN_ID_1:
        dpEnumLevelControl = buff[0];
        DevType = LIVE_TYPE;
        break;
    }
}

/* Private functions ---------------------------------------------------------*/
static void vCloud_CtrlRegister( void )
{

    Cloud.defineDatapointEnum(DPID_YUN_ID_1, DP_PERMISSION_UP_DOWN, 0);   
}

static void vCloud_CtrlDataUpload( void )
{  
    Cloud.writeDatapointEnum(DPID_YUN_ID_1,  dpEnumLevelControl);   
}

static void vCloud_ReadDataAndControl( void )
{
     uint8_t buff[6];  
     

    if (RESULT_DATAPOINT_NEW == Cloud.readDatapointEnum(DPID_YUN_ID_1, &dpEnumLevelControl))
    {
        buff[0] =  dpEnumLevelControl;
        mainCtrl.Set_Handler( LIVE_TYPE, DPID_YUN_ID_1, buff, 1);          
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
              log_v("ep_network_status_disconnected \r\n");
          break;
          case ep_network_status_connected:
              log_v("ep_network_status_connected \r\n");
          break;
          case ep_cloud_status_disconnected:
              log_v("ep_cloud_status_disconnected \r\n");
          break;
          case ep_cloud_status_connected: 
              log_v("ep_cloud_status_connected \r\n");
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
              log_v("ep_mode_normal \r\n");
           break;
           case ep_mode_imlink_config:    
              log_v("ep_mode_imlink_config \r\n");
           break;
           case ep_mode_ap_config:
              log_v("ep_mode_ap_config \r\n");
           break;
           case ep_mode_binding: 
              log_v("ep_mode_binding \r\n");  
           break;
           default:
           break;
       }
    }
}

/* End of this file  */

