/** \file

$Id: user_Handler.c 40486 2018-08-26 22:50:21Z tangmingfei2013@126.com $

Copyright (c)tangmingfei2013@126.com Holding B.V.
All Rights Reserved.

This source code and any compilation or derivative thereof is the proprietary
information of mingfei.tang Holding B.V. and is confidential in nature.
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

#include "apps_commHandler.h"
#include "Interface_dev.h"
#include "Interface_presence.h"
#include "Interface_jdq.h"
#include "Interface_light.h"
#include "Interface_tv.h"
#include "Interface_local.h"
#include "Includes.h"
#include "log.h"

//for rtos
#include "FreeRTOS.h"
#include "timers.h"
#include "task.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "user_Handler.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define STAIR_ADD                 JDQ_CH4_ADD        
#define DEVICE_ADD                JDQ_CH8_ADD

#define STAIR_CHANNEL_ID          JDQ_CH4_STAIR_ID

// for rtos time ID
#define TIMER_ID                  0

#define USERHANDLER_DEBUGEN       1

#if  USERHANDLER_DEBUGEN
#define   userHandler_debug       log_printstring
#else
#define   userHandler_debug         
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static char userHandler_PkgId[] = " useHandler";

static uint8_t closeDevActionStep = 0;
static uint8_t Ctrl_DownLevelStep = 0;
static uint8_t step_Lev = 0;

static CtrlJDQ_typedef st_CtrlJDQ;
static uint8_t ctrlDir = 0;
static uint8_t yunID = DPID_YUN_ID_NULL;
static Presence_TypeDef st_Presence;

static uint32_t timer500msID;
static uint32_t timer100msID;
static bool b_run500Flag = false;
static bool b_run100Flag = false;

static xTimerHandle xTimers;
/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void vAppsCtrl_Reset( void );
static void vAppsCtrl_Set(  uint8_t id, uint8_t dir  );
static void vAppsCtrl_PresenceError( void );
static void vAppsCtrl_SetLevelRunState(  uint8_t dir  );

static CTRL_RESULT_ENUM eAppsCtrl_LevelInterface( void );
static CTRL_RESULT_ENUM eAppsCtrl_DownLevel( void );
static CTRL_RESULT_ENUM eAppsCtrl_UpLevel( void );
static CTRL_RESULT_ENUM eAppsCtrl_StopLevel( void );

static CTRL_RESULT_ENUM eAppsCtrl_Device( void );
static CTRL_RESULT_ENUM eAppsCtrl_Close( void );

// interface for rtos timer 
static void AppTask_CreateTimer (void);
static void AppTask_StartTimer( void );
static void AppTask_StopTimer( void );
static void vTimerCallback( xTimerHandle pxTimer );

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
void vAppsCtrl_Init( void )
{
    vJdq_CtrlInit( &st_CtrlJDQ );
    vAppsCtrl_Reset();
    timer100msID = timerGetId();
    timer500msID = timerGetId();
    vPresence_Init( &st_Presence );
    
    AppTask_CreateTimer();   //Create timer for presence
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
         break;
         
       case DPID_YUN_ID_4:
         if( type != LAZYBACK_TYPE)
           return;        
         pJDQ_typedef->st_JdqCtrlPara.SetAddress = DEVICE_ADD;
         pJDQ_typedef->st_JdqCtrlPara.SetChannel = LAZYBACK_2_ID;
         break;
         
       case DPID_YUN_ID_6:
         if( type != DESK_TYPE)
           return;          
         pJDQ_typedef->st_JdqCtrlPara.SetAddress = DEVICE_ADD;
         pJDQ_typedef->st_JdqCtrlPara.SetChannel = DESK_ID;
         break;
         
       case DPID_YUN_ID_8:
         if( type != STAIR_TYPE)
           return;         
         pJDQ_typedef->st_JdqCtrlPara.SetAddress = STAIR_ADD;
         pJDQ_typedef->st_JdqCtrlPara.SetChannel = STAIR_CHANNEL_ID;
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
         
      default:
         break;
   }
   
   vAppsCtrl_Set( id, dir[0]);
}

void vAppsCtrl_Process( void )
{
    CTRL_RESULT_ENUM e_res;

    if( yunID == DPID_YUN_ID_NULL )
        return;

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
              e_res = eAppsCtrl_LevelInterface();
              if( e_res == CTRL_OK || e_res == CTRL_FAIL )
              { 
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
             if( b_run500Flag )
             {
                b_run500Flag = false;
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
          
        default:
          yunID = NULL_ID;
          break;
    }
}

/******************************************************************************
* LOCAL FUNCTIONS
******************************************************************************/
static CTRL_RESULT_ENUM eAppsCtrl_Device( void )
{
    CtrlJDQ_typedef *pJDQ = &st_CtrlJDQ;

    return eJDQ_CtrlInterface( pJDQ, ctrlDir);
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
    CTRL_RESULT_ENUM e_res;
       
    switch( step_Lev )
    {
        case 0:    /* check presence : 500 ms task */ 
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
                    step_Lev = 0;
                    return CTRL_FAIL;
                }
            }
        break;
            
        case 1:  /* close all devices : 500 ms task */ 
            if( b_run500Flag )
            {     
                b_run500Flag = false;     
                e_res = eAppsCtrl_Close();
                if( e_res == CTRL_OK )
                {
                    step_Lev = 2;
                    // Open rtos time for montior presence 
                    AppTask_StartTimer();
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
                 if(st_Presence.res)
                 {
                     AppTask_StopTimer();
                     ctrlDir = DIR_STOP;
                 }
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
                    if( e_res == CTRL_FAIL )
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
    
    if( yunID == DPID_YUN_ID_7  && ctrlDir == DIR_UP )
    {
        /* turn up the level :  100 ms task */
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
    }
    
    return CTRL_IDLE;   
}

static CTRL_RESULT_ENUM eAppsCtrl_StopLevel( void )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    
    if( yunID == DPID_YUN_ID_7  && ctrlDir == DIR_STOP )
    {
        /* stop the level to run :  100 ms task */
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

static CTRL_RESULT_ENUM eAppsCtrl_Close( void )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    CtrlJDQ_typedef *pJDQ_typedef = &st_CtrlJDQ;
    
    switch( closeDevActionStep )
    {
        case 0:
           pJDQ_typedef->st_JdqCtrlPara.SetAddress = DEVICE_ADD;
           pJDQ_typedef->st_JdqCtrlPara.SetChannel = LAZYBACK_1_ID;
           closeDevActionStep = 1;
        break;

        case 1: /* close lazyback - 1 */
           e_res = eJDQ_CtrlInterface( pJDQ_typedef,  JDQ_DOWN);
           if( e_res == CTRL_OK )
           {
                closeDevActionStep = 2;
                pJDQ_typedef->st_JdqCtrlPara.SetChannel = LAZYBACK_2_ID;
           }
           else if( e_res == CTRL_FAIL )
           {
               vAppsCtrl_Reset();
               return CTRL_FAIL;
           }
       break;

       case 2: /* close lazyback - 2 */
           e_res = eJDQ_CtrlInterface( pJDQ_typedef, JDQ_DOWN );
           if( e_res == CTRL_OK )
           {
                closeDevActionStep = 3;
                pJDQ_typedef->st_JdqCtrlPara.SetChannel = DESK_ID;
           }
           else if( e_res == CTRL_FAIL )
           {
               vAppsCtrl_Reset();
               return CTRL_FAIL;
           }
        break;

       case 3:   /* close desk */
           e_res = eJDQ_CtrlInterface( pJDQ_typedef, JDQ_DOWN );
           if(  e_res == CTRL_OK )
           { 
                pJDQ_typedef->st_JdqCtrlPara.SetAddress = STAIR_ADD;
                pJDQ_typedef->st_JdqCtrlPara.SetChannel = STAIR_CHANNEL_ID;
                closeDevActionStep = 4;
           }
           else if( e_res == CTRL_FAIL )
           {
               vAppsCtrl_Reset();
               return CTRL_FAIL;
           }
        break;
          
      case 4:     /* close stair  */
          e_res = eJDQ_CtrlInterface( pJDQ_typedef, JDQ_DOWN );
          if( e_res == CTRL_OK || e_res == CTRL_FAIL )
          {
             vAppsCtrl_Reset();
             return e_res;
          }
         break;
         
     default:
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
   closeDevActionStep = 0; 
   Ctrl_DownLevelStep = 0;
   step_Lev = 0;
   b_run500Flag = false;
   b_run100Flag = false;
}

static void vAppsCtrl_PresenceError( void )
{
    uint8_t buff[3];

    buff[0] = PRESENCE_TYPE;
    buff[1] = DPID_YUN_ID_7;
    buff[2] = 1;
    apps_SendErrorCode( buff, 3);
}

/* 
    for RTOS TIMER handler 
*/
static void AppTask_CreateTimer (void)
{
    const TickType_t xTimerPeriodInTicks = 1000;
  

     xTimers = xTimerCreate(  "Timer",             
                              xTimerPeriodInTicks,
                              pdTRUE, 
                              ( void * ) TIMER_ID,
                              vTimerCallback
                           );


     if( xTimers == NULL )
     {
       log_printstring( userHandler_PkgId, "create timer: fail \r\n");
     }
}

static void AppTask_StartTimer( void )
{
    if( xTimerStart( xTimers, 0 ) != pdPASS )
    {
        log_printstring( userHandler_PkgId, "start time: fail \r\n");
    }    
}

static void AppTask_StopTimer( void )
{
    if( xTimerStop( xTimers, 0 ) != pdPASS )
    {
        log_printstring( userHandler_PkgId, "stop time: fail \r\n");
    }    
}

static void vTimerCallback( xTimerHandle pxTimer )
{
    long lArrayIndex;
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;

    configASSERT( pxTimer );

    /* get timer ID  */
    lArrayIndex = ( long ) pvTimerGetTimerID( pxTimer );
    if( lArrayIndex == TIMER_ID )
    {
       //Read presence sensor value
       e_res = ePresence_OnlyReadValue( &st_Presence );
       if( e_res == CTRL_OK )
       {
            if( st_Presence.res )
            {
            
            }
       }
    }    
}
/* End of this file */
