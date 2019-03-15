/** \file

$Id: user_Ctrl.c 40486 2018-08-26 22:50:21Z tangmingfei2013@126.com $

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
#include "board.h"
#include "motor_handler.h"
#include "usart.h"
#include "timer.h"

#include "apps_commHandler.h"
#include "Interface_dev.h"
#include "Interface_presence.h"
#include "Interface_jdq.h"
#include "Interface_light.h"
#include "Interface_tv.h"
#include "Interface_local.h"
#include "Includes.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "user_house.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define STAIR_ADD                 JDQ_CH4_ADD        
#define DEVICE_ADD                JDQ_CH8_ADD
#define READDEV_ADD               JDQ_CH4_READADD

#define STAIR_CHANNEL_ID          JDQ_CH4_STAIR_ID

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
typedef struct
{
  uint8_t  address;       
  uint8_t  chanID;
  //CTRL_RESULT_ENUM     (*pf_SendPut)(CtrlJDQ_typedef*, uint8_t);
}dev_act;

static uint8_t Ctrl_DownLevelStep = 0;
static uint8_t step_Lev = 0;
static uint8_t step_DeviceCtrlLev = 0;
//static uint8_t readPresenceCnt = 0;
static uint8_t ctrlDir = 0;
static uint8_t yunID = DPID_YUN_ID_NULL;

static CtrlJDQ_typedef st_CtrlJDQ;
static CtrlJDQ_typedef st_CtrlReadJDQ;
static Presence_TypeDef st_Presence;

static const dev_act st_devAct[] = 
{
   /* address        channel    */
   DEVICE_ADD,       LAZYBACK_1_ID,
   DEVICE_ADD,       LAZYBACK_2_ID,
   DEVICE_ADD,       DESK_ID,
   STAIR_ADD,        STAIR_CHANNEL_ID,
};

const uint8_t ActCmdTotal = dim(st_devAct);

static uint8_t run_Index = 0;
static uint8_t CtrDevActionStep = 0;

static uint32_t timer500msID;
static uint32_t timer300msID;
static uint32_t timer100msID;

static bool b_levelStatus = false;
static bool b_run500Flag = false;
static bool b_run100Flag = false;

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void vAppsCtrl_Reset( void );
static void vAppsCtrl_Set( uint8_t id, uint8_t dir );
static void vAppsCtrl_PresenceError( void );
static void vAppsCtrl_SetLevelRunState( uint8_t dir );
static void vAppsCtrl_ReadJdqStatus( void );

static CTRL_RESULT_ENUM eAppsCtrl_LevelInterface( void );
static CTRL_RESULT_ENUM eAppsCtrl_DownLevel( void );
static CTRL_RESULT_ENUM eAppsCtrl_UpLevel( void );
static CTRL_RESULT_ENUM eAppsCtrl_StopLevel( void );

static CTRL_RESULT_ENUM eAppsCtrl_Device( void );
static CTRL_RESULT_ENUM eAppsCtrl_UpOrDowndevice( uint8_t dir );

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
void vAppsCtrl_Init( void )
{
    st_CtrlReadJDQ.st_JdqCtrlPara.SetAddress =  READDEV_ADD;
    st_CtrlReadJDQ.st_JdqCtrlPara.SetTotalChn   = 4;
    vJdq_CtrlInit( &st_CtrlJDQ );

    vJdq_CtrlInit( &st_CtrlReadJDQ );
    vAppsCtrl_Reset();
    timer100msID = timerGetId();
    timer300msID = timerGetId();
    timer500msID = timerGetId();
    vPresence_Init( &st_Presence );
}

void AppsCtrl_ReadStatus( void )
{
    vCtrl_MotorSetActStep( MOTOR_READSTATUS );
    step_DeviceCtrlLev = 0;
}

void vAppsCtrl_SetDevicePara(uint8_t id, uint8_t type, uint8_t *dir )
{ 
    CtrlJDQ_typedef *pJDQ_typedef = &st_CtrlJDQ;

    vJdq_ContrlReset( pJDQ_typedef );
    switch( id )
    {
       case DPID_YUN_ID_3:
         if( type != LAZYBACK_TYPE)
           return;
         pJDQ_typedef->st_JdqCtrlPara.SetAddress = DEVICE_ADD;
         pJDQ_typedef->st_JdqCtrlPara.SetChannel = LAZYBACK_1_ID; 
         AppsCtrl_ReadStatus();
         break;
         
       case DPID_YUN_ID_4:
         if( type != LAZYBACK_TYPE)
           return;
         pJDQ_typedef->st_JdqCtrlPara.SetAddress = DEVICE_ADD;
         pJDQ_typedef->st_JdqCtrlPara.SetChannel = LAZYBACK_2_ID;
         AppsCtrl_ReadStatus();
         break;
         
       case DPID_YUN_ID_6:
         if( type != DESK_TYPE)
           return;
         pJDQ_typedef->st_JdqCtrlPara.SetAddress = DEVICE_ADD;
         pJDQ_typedef->st_JdqCtrlPara.SetChannel = DESK_ID;
         AppsCtrl_ReadStatus();
         break;
         
       case DPID_YUN_ID_8:
         if( type != STAIR_TYPE)
           return;
         pJDQ_typedef->st_JdqCtrlPara.SetAddress = STAIR_ADD;
         pJDQ_typedef->st_JdqCtrlPara.SetChannel = STAIR_CHANNEL_ID;
         AppsCtrl_ReadStatus();
         break;
         
       case DPID_YUN_ID_7:
         if( type != LIVE_TYPE)
           return;           
         vAppsCtrl_Reset();
         vPresence_Reset( &st_Presence );
         vCtrl_MotorStart( dir[0] );
         vAppsCtrl_SetLevelRunState( dir[0] );
         break;
         
      case DPID_YUN_ID_5:
         if( type != TV_TYPE)
           return;
         vCtrl_MotorTVStart( dir[0] ); 
         break;

      case DPID_YUN_ID_1: 
         if( type != LED_TYPE)
           return;   
         vLight_SetPara( LED_ID_1, dir[0], dir[1], dir[2]);
         break;
         
      case DPID_YUN_ID_ALLDEV:
         vAppsCtrl_Reset();
         break;

      default:
         break;
    }

    if( !b_levelStatus )
    {
        vAppsCtrl_Set( id, dir[0]);
    }
}

void vAppsCtrl_Process( void )
{
    CTRL_RESULT_ENUM e_res;
     
    if( yunID == DPID_YUN_ID_NULL )
    {
        if( timerIsEnd(timer300msID, 300))
        {
            vAppsCtrl_ReadJdqStatus();
            timer300msID = timerGetId();
        }
        return;
    }

    /*
         Enable timer
    */
    if( timerIsEnd(timer500msID, 500))
    {
        timer500msID = timerGetId();
        b_run500Flag = true;
    }
    else if( timerIsEnd(timer100msID, 100))
    {
        timer100msID = timerGetId();
        b_run100Flag = true;
    }

    switch(  yunID ) 
    {
        /*
             level control
        */
        case DPID_YUN_ID_7:
              b_levelStatus = true;                    //Level run is enable
              e_res = eAppsCtrl_LevelInterface();
              if( e_res == CTRL_OK || e_res == CTRL_FAIL )
              { 
                   b_levelStatus = false;
                   yunID = NULL_ID;
              }
          break;

        /*
             tv control
        */
        case DPID_YUN_ID_5:
             if( b_run100Flag )
             {
                  b_run100Flag = false;
                  e_res = eCtrl_MotorTVInterface();
                  if( e_res == CTRL_OK || e_res == CTRL_FAIL )
                  { 
                       yunID = NULL_ID;
                  }
             }
          break;

        /*
             device control 
        */
        case DPID_YUN_ID_3:
        case DPID_YUN_ID_4:
        case DPID_YUN_ID_6:
        case DPID_YUN_ID_8:
             if( !b_levelStatus )
             {
                e_res = eAppsCtrl_Device();
                if( e_res == CTRL_OK || e_res == CTRL_FAIL )
                { 
                     yunID = NULL_ID;
                }
             }
          break;

        /*
             light control 
        */
        case DPID_YUN_ID_1:
              if( b_run500Flag )
              {
                  b_run500Flag = false;
                  e_res = eLight_CtrlInterface();
                  if( e_res == CTRL_OK || e_res == CTRL_FAIL )
                  {
                      yunID = NULL_ID;
                  }
              }
          break;
          
       /*
           All device ctrol
       */
        case  DPID_YUN_ID_ALLDEV:
              if( b_run500Flag )
              {
                  b_run500Flag = false;
                  e_res = eAppsCtrl_UpOrDowndevice( ctrlDir );
                  if( e_res == CTRL_OK || e_res == CTRL_FAIL )
                  {
                      yunID = NULL_ID;
                  }
              }
          break;

        default:
          yunID = NULL_ID;
          break;
    }
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static void vAppsCtrl_ReadJdqStatus( void )
{
    CTRL_RESULT_ENUM e_res;
    uint8_t value_level,value_device, buff[1];

    e_res = jdq_ReadBoolValueHandler( &st_CtrlReadJDQ );
    if( e_res == CTRL_OK )
    {
        //Level
        value_level = st_CtrlReadJDQ.st_JdqCtrlPara.boolValue&0x03;
        if( value_level == 0x01 )      // level up
        {
           buff[0]= DIR_UP;
           vAppsCtrl_SetDevicePara( DPID_YUN_ID_7, LIVE_TYPE, buff );
        }
        else if( value_level == 0x02) // level down
        {
           buff[0]= DIR_DOWN;
           vAppsCtrl_SetDevicePara( DPID_YUN_ID_7, LIVE_TYPE, buff );
        } 
      
        //Device
        value_device = (st_CtrlReadJDQ.st_JdqCtrlPara.boolValue>>2)&0x03;
        if( value_device == 0x01 )     // Device up
        {
           buff[0]= DIR_UP;
           vAppsCtrl_SetDevicePara( DPID_YUN_ID_ALLDEV, LIVE_TYPE, buff );
        }
        else if( value_device == 0x02)   // Device down
        {
           buff[0]= DIR_DOWN;
           vAppsCtrl_SetDevicePara( DPID_YUN_ID_ALLDEV, LIVE_TYPE, buff );
        }
    }
}

static CTRL_RESULT_ENUM eAppsCtrl_Device( void )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    CtrlJDQ_typedef *pJDQ = &st_CtrlJDQ;
    
    switch( step_DeviceCtrlLev )
    {
        case 0:    // check level posion
           if( b_run100Flag )
           {
                b_run100Flag = false;
                e_res = eCtrl_MotorInterface();
                if( e_res == CTRL_OK )
                { 
                    if( eMotor_CheckMotorSqr2() == CTRL_OK )
                    {
                        step_DeviceCtrlLev = 1;
                    }
                    else
                        return  CTRL_FAIL;
                }
                else if(  e_res == CTRL_FAIL  )
                {
                    return  CTRL_FAIL;
                }
           }      
          break;
          
        case 1:
          if( b_run500Flag )
          {
              b_run500Flag = false;          
              return eJDQ_CtrlInterface( pJDQ, ctrlDir);
          }
          break;
    }
  
    return   CTRL_IDLE;
}

static void vAppsCtrl_SetLevelRunState(  uint8_t dir  )
{
    switch( dir )
    {
        case DIR_DOWN:
        case DIR_STOP:
          step_Lev = 2;
          break;
          
        case DIR_UP:
          step_Lev = 0;
          break;
          
        default:
          break;
    }
}

static CTRL_RESULT_ENUM eAppsCtrl_LevelInterface( void )
{  
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
       
    switch( step_Lev )
    {
        case 0:    //check presence : 500 ms task 
            if( b_run500Flag )
            {
                b_run500Flag = false;
                e_res = vPresence_Interface( &st_Presence );
                if( e_res == CTRL_OK )
                {
                    if( st_Presence.res )
                    {
                        //send warning alarm
                        tim_SetTimIsr( TIMER2, vAppsCtrl_PresenceError, 3);
                        step_Lev = 0;
                        return CTRL_FAIL;
                    } 
                    else 
                    {
                        step_Lev = 1;
                    }
                }
                else if( e_res == CTRL_FAIL )
                {
#if 0
                    step_Lev = 0;
                    return CTRL_FAIL;
#else
                    step_Lev = 1;
#endif
                }
            }
        break;
            
        case 1:  /* down all devices : 500 ms task */ 
            if( b_run500Flag )
            {     
                b_run500Flag = false;
                e_res = eAppsCtrl_UpOrDowndevice( DIR_DOWN );
                if( e_res == CTRL_OK )
                {
                    step_Lev = 2;
                }
                else if( e_res == CTRL_FAIL )
                {
                    return CTRL_FAIL;
                }
            }
        break;
        
        case 2:   /* control  level : 100 ms task */ 
            if( ctrlDir == DIR_UP )
            {
                e_res = eAppsCtrl_UpLevel();   
            }
            else if(  ctrlDir == DIR_DOWN )
            {
                e_res = eAppsCtrl_DownLevel();
            }
            else if( ctrlDir == DIR_STOP )
            {
                e_res = eAppsCtrl_StopLevel();
            }

            if( e_res == CTRL_OK )
            {
                return CTRL_OK;
            }
            else if( e_res == CTRL_FAIL )
            {
                vAppsCtrl_Reset();
                return CTRL_FAIL;
            }
        break;
        
        default:
        break;
    }
    
    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM eAppsCtrl_DownLevel( void )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    CtrlJDQ_typedef *pJDQ_typedef = &st_CtrlJDQ;
    
    if( yunID == DPID_YUN_ID_7  && ctrlDir == DIR_DOWN )
    {
        switch( Ctrl_DownLevelStep )
        {
            case 0: /* turn down the level :  100 ms task */
                if( b_run100Flag )
                {
                    b_run100Flag = false;
                    e_res = eCtrl_MotorInterface();
                    if( e_res == CTRL_OK )
                    {
                         /* set the parameter for open stair  */
                        Ctrl_DownLevelStep = 1;
                        pJDQ_typedef->st_JdqCtrlPara.SetAddress = STAIR_ADD;
                        pJDQ_typedef->st_JdqCtrlPara.SetChannel = STAIR_CHANNEL_ID;
                    }
                    else if( e_res == CTRL_FAIL )
                    {
                        vAppsCtrl_Reset();
                        return CTRL_FAIL;
                    }
                }
                break;
              
            case 1:   /* Open the stair:  500 ms task-- channel 4:   */
                if( b_run500Flag )
                {
                    b_run500Flag = false;
                    e_res = eJDQ_CtrlInterface( pJDQ_typedef, JDQ_UP );
                    if( e_res == CTRL_OK || e_res == CTRL_FAIL )
                    {
                        vAppsCtrl_Reset();
                        return e_res;
                    }
                }
                break;
              
            default:
                break;
        }
    }
    
    return CTRL_IDLE;   
}

static CTRL_RESULT_ENUM eAppsCtrl_UpLevel( void )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    
    if( yunID == DPID_YUN_ID_7 && ctrlDir == DIR_UP )
    {
        /*  
            turn up the level :  100 ms task 
        */
        if( b_run100Flag )
        {
            b_run100Flag = false;
            e_res = eCtrl_MotorInterface();
            if( e_res == CTRL_OK || e_res == CTRL_FAIL )
            {
                vAppsCtrl_Reset();
                return CTRL_FAIL;
            }
        }
 
#if 0       
        /*
            read presence value
        */
        if( b_run500Flag && (readPresenceCnt < 30))
        {
            b_run500Flag = false;
            if( ePresence_OnlyReadValue( &st_Presence ) == CTRL_OK )
            {
                readPresenceCnt++;
                if( st_Presence.res )
                {
                    vCtrl_MotorSetActStep( MOTOR_STOPRUN );   // Stop to run
                }
            }
        } 
#endif
        
    }
    
    return CTRL_IDLE;   
}

static CTRL_RESULT_ENUM eAppsCtrl_StopLevel( void )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    
    if( yunID == DPID_YUN_ID_7  && ctrlDir == DIR_STOP )
    {
        /* 
            stop the level to run :  100 ms task 
        */
        if( b_run100Flag )
        {
            b_run100Flag = false;
            e_res = eCtrl_MotorInterface();
            if( e_res == CTRL_OK )
            {
                return CTRL_OK;
            }
            else if( e_res == CTRL_FAIL )
            {
                vAppsCtrl_Reset();
                return CTRL_FAIL;
            }
        }
    }
    
    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM eAppsCtrl_UpOrDowndevice( uint8_t dir )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    CtrlJDQ_typedef *pJDQ_typedef = &st_CtrlJDQ;
    
    switch( CtrDevActionStep )
    {
      case 0:
        pJDQ_typedef->st_JdqCtrlPara.SetAddress = st_devAct[run_Index].address;
        pJDQ_typedef->st_JdqCtrlPara.SetChannel = st_devAct[run_Index].chanID;
        CtrDevActionStep = 1;
        run_Index++;
        break;
      case 1:
        e_res = eJDQ_CtrlInterface( pJDQ_typedef, dir);
        if( e_res == CTRL_OK )
        {
             if( run_Index == ActCmdTotal )
             {
                 vAppsCtrl_Reset();
                 return CTRL_OK;
             }
             else
             {
                 CtrDevActionStep = 0;
             }
        }
        else if( e_res == CTRL_FAIL )
        {
           vAppsCtrl_Reset();
           return CTRL_FAIL;
        }
        break;
    }
    
    return CTRL_IDLE;
}

static void vAppsCtrl_Set(  uint8_t id, uint8_t dir  )
{
    ctrlDir = dir;
    yunID = id;
}

static void vAppsCtrl_Reset( void )
{
    CtrDevActionStep = 0; 
    Ctrl_DownLevelStep = 0;
    step_Lev = 0;
    run_Index = 0;
    b_run500Flag = false;
    b_run100Flag = false;
    //readPresenceCnt = 0;
}

static void vAppsCtrl_PresenceError( void )
{
    uint8_t buff[3];

    buff[0] = PRESENCE_TYPE;
    buff[1] = DPID_YUN_ID_7;
    buff[2] = 1;
    apps_SendErrorCode( buff, 3);
}

/* End of this file */
