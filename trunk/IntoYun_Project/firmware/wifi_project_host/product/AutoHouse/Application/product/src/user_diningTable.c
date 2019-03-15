/** \file

$Id: user_diningTable.c 40486 2018-09-15 13:50:21Z tangmingfei2013@126.com $

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
#include "usart.h"
#include "timer.h"
#include "Interface_jdq.h"
#include "Includes.h"
#include "log.h"

/******************************************************************************
* LOCAL INCLUDE FILES
******************************************************************************/
#include "user_diningTable.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define READDEV_ADD               JDQ_CH4_READADD
#define DEVICE_ADD                JDQ_CH8_ADD

#define DING_TAB_OPEN             JDQ_DOWN
#define DING_TAB_CLOSE            JDQ_UP
#define DING_TAB_STOP             JDQ_STOP

#define DING_DEBUGEN              1

#if  DING_DEBUGEN
#define   ding_debug              printf
#else
#define   ding_debug
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
char jdq_PkgId[] = " dingTable";

static CtrlJDQ_typedef st_CtrlJDQ;
static CtrlJDQ_typedef st_CtrlReadJDQ;
static uint8_t ctrlDir = 0;
static uint8_t yunID = DPID_YUN_ID_NULL;

static uint32_t timer300msID;
static uint32_t timer200msID;
static bool b_run1000Flag = false;
static bool b_run200Flag = false;

static uint8_t total_Cmd = 0;
static uint8_t step_Lev = 0;
static uint8_t delay_Time = 0;
static uint8_t run_Status = 0;
static uint8_t run_Index = 0;
static uint16_t cnt_Second = 0;

static const table_CtrlAction st_tablCtrlOpen[] = 
{ 
  /* id        delay time         status          debug infor       */
  DOOR_1_ID,   0,                 DING_TAB_OPEN, "CH1-CH2: 01,delay: 0s",
  DOOR_2_ID,   22,                DING_TAB_OPEN, "CH3-CH4: 01,delay: 30s",   /* Open the door */

  PUSH_1_ID,   46,                DING_TAB_CLOSE,"CH5-CH6: 10,delay: 45s",   /* down the table */
  
  DOOR_1_ID,   0,                 DING_TAB_CLOSE,"CH1-CH2: 10,delay: 0s",    /* Close the door */  
  DOOR_2_ID,   22,                DING_TAB_CLOSE,"CH3-CH4: 10,delay: 30s",
  
  PUSH_2_ID,   48,                DING_TAB_OPEN, "CH7-CH8: 01,delay: 20s",   /* pull the desk */
};

const uint8_t OpenCmdTotal = dim(st_tablCtrlOpen);


static const table_CtrlAction st_tablCtrlClose[] = 
{ 
  /* id        delay time         status          debug infor       */
  PUSH_2_ID,   48,                DING_TAB_CLOSE, "CH7-CH8: 10,delay: 45s", /* down the desk */

  DOOR_1_ID,   0,                 DING_TAB_OPEN,  "CH1-CH2: 01,delay: 0s",  /* open the door */
  DOOR_2_ID,   22,                DING_TAB_OPEN,  "CH3-CH4: 01,delay: 25s",
  
  PUSH_1_ID,   58,                DING_TAB_OPEN,  "CH5-CH6: 01,delay: 50s", /* pull the table */
  PUSH_1_ID,   0,                 DING_TAB_STOP,  "CH5-CH6: 00,delay: 0s",   /* stop the table */
  
  DOOR_1_ID,   0,                 DING_TAB_CLOSE, "CH1-CH2: 10,delay: 0s",  /* close the door */
  DOOR_2_ID,   22,                DING_TAB_CLOSE, "CH3-CH4: 10,delay: 25s",
};

const uint8_t CloseCmdTotal = dim(st_tablCtrlClose);


static const table_CtrlAction st_tablCtrlStop[] = 
{ 
  /* id        delay time         status         debug infor       */
  PUSH_2_ID,   0,                 DING_TAB_STOP, "CH7-CH8: 00,delay: 0s",
  PUSH_1_ID,   0,                 DING_TAB_STOP, "CH5-CH6: 00,delay: 0s", 
  DOOR_1_ID,   0,                 DING_TAB_STOP, "CH1-CH2: 00,delay: 0s",
  DOOR_2_ID,   0,                 DING_TAB_STOP, "CH3-CH4: 00,delay: 0s",
};

const uint8_t StopCmdTotal = dim(st_tablCtrlStop);

/******************************************************************************
* LOCAL FUNCTION DECLARATIONS
******************************************************************************/
static void vUser_diningTable_Set(  uint8_t id, uint8_t dir  );
static void vUser_diningTable_Reset( void );
static void vAppsCtrl_ReadJdqStatus( void );
static void vAppsCtr_Debug( void );
static void vAppsCtr_Debug_Reset( void );

static CTRL_RESULT_ENUM eUser_diningTable_interface( void );
static CTRL_RESULT_ENUM eUser_diningTableCtrl( uint8_t type );

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
void vUser_diningTableInit( void )
{
    st_CtrlReadJDQ.st_JdqCtrlPara.SetAddress =  READDEV_ADD;
    st_CtrlReadJDQ.st_JdqCtrlPara.SetTotalChn   = 4;
    vJdq_CtrlInit( &st_CtrlReadJDQ );
   
    vJdq_CtrlInit( &st_CtrlJDQ );
    timer300msID = timerGetId();
    timer200msID = timerGetId();
}

void vUser_diningTableSetDevicePara(uint8_t id, uint8_t type, uint8_t *dir )
{ 
    CtrlJDQ_typedef *pJDQ_typedef = &st_CtrlJDQ;

    vJdq_ContrlReset( pJDQ_typedef );
    switch( id )
    {
      case DPID_YUN_ID_1: 
         if( type != DING_TABLE_TYPE)
           return;
         break;
         
      default:
         break;
    }

    if(yunID == DPID_YUN_ID_NULL ||  dir[0] == DING_TAB_STOP )
    {
       vUser_diningTable_Set( id, dir[0]);
    }
}

void vUser_diningTable_Process( void )
{
    static uint8_t rtc_second = 0;
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
    if( timerIsEnd(timer200msID, 200))
    {
        timer200msID = timerGetId();
        b_run200Flag = true;
    } 
 
    if( rtc_second != st_Rtc.u8_Second )
    {
        cnt_Second++;
        rtc_second = st_Rtc.u8_Second;
        vAppsCtr_Debug();
        b_run1000Flag = true;
    }

    switch( yunID ) 
    {
        /*
             ding table control
        */
        case DPID_YUN_ID_1:
          e_res = eUser_diningTable_interface();
          if( e_res == CTRL_OK || e_res == CTRL_FAIL )
          { 
               yunID = DPID_YUN_ID_NULL;
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
static void vAppsCtr_Debug( void )
{
    ding_debug("cnt_Second: %d \r\n ", cnt_Second);
    ding_debug("delay_Time: %d \r\n ", delay_Time);
}

static void vAppsCtr_Debug_Reset( void )
{
    cnt_Second = 0;
}

static void vAppsCtrl_ReadJdqStatus( void )
{
    CTRL_RESULT_ENUM e_res;
    uint8_t value_level, buff[1];
    
    e_res = jdq_ReadBoolValueHandler( &st_CtrlReadJDQ );
    if( e_res == CTRL_OK )
    {
         //table
         value_level = st_CtrlReadJDQ.st_JdqCtrlPara.boolValue&0x03;
         if( value_level == 0x01 )     // table extent
         {
             buff[0]= DIR_UP;
             vUser_diningTableSetDevicePara( DPID_YUN_ID_1, DING_TABLE_TYPE, buff );
         }                        
         else if( value_level == 0x02) // table close
         {
             buff[0]= DIR_DOWN;
             vUser_diningTableSetDevicePara( DPID_YUN_ID_1, DING_TABLE_TYPE, buff );
         }
    }
}

static CTRL_RESULT_ENUM eUser_diningTable_interface( void )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    
    if( ctrlDir == DIR_DOWN )
    {
       e_res = eUser_diningTableCtrl( TYPE_OPEN );
    }
    else if( ctrlDir == DIR_UP)
    {
       e_res = eUser_diningTableCtrl( TYPE_CLOSE );
    }
    else
    {
       //Stop mode
       e_res = eUser_diningTableCtrl( TYPE_STOP );
    }
    
    return e_res;
}

static CTRL_RESULT_ENUM eUser_diningTableCtrl( uint8_t type )
{
    CTRL_RESULT_ENUM e_res = CTRL_IDLE;
    CtrlJDQ_typedef *pJDQ_typedef = &st_CtrlJDQ;

    switch( step_Lev )
    {
    case 0:
        pJDQ_typedef->st_JdqCtrlPara.SetAddress =  DEVICE_ADD;
        if( type == TYPE_OPEN )
        {
            pJDQ_typedef->st_JdqCtrlPara.SetChannel = st_tablCtrlOpen[run_Index].id;
            run_Status = st_tablCtrlOpen[run_Index].status;
            delay_Time = st_tablCtrlOpen[run_Index].delayTime;
            ding_debug( jdq_PkgId,  st_tablCtrlOpen[run_Index].str);
            total_Cmd = OpenCmdTotal;
        }
        else if( type == TYPE_CLOSE )
        {
            pJDQ_typedef->st_JdqCtrlPara.SetChannel = st_tablCtrlClose[run_Index].id;
            run_Status = st_tablCtrlClose[run_Index].status;
            delay_Time = st_tablCtrlClose[run_Index].delayTime;
            ding_debug( jdq_PkgId,  st_tablCtrlClose[run_Index].str);
            total_Cmd = CloseCmdTotal;
        }
        else if( type == TYPE_STOP )
        {
            pJDQ_typedef->st_JdqCtrlPara.SetChannel = st_tablCtrlStop[run_Index].id;
            run_Status = st_tablCtrlStop[run_Index].status;
            delay_Time = st_tablCtrlStop[run_Index].delayTime;
            ding_debug( jdq_PkgId,  st_tablCtrlStop[run_Index].str);
            total_Cmd = StopCmdTotal;
        }
        step_Lev = 1;
        run_Index++;
       break;

    case 1:
      vAppsCtr_Debug_Reset();
      if( b_run200Flag )
      {
           b_run200Flag = false; 
           e_res = eJDQ_CtrlInterface( pJDQ_typedef,run_Status);
           if( e_res == CTRL_OK )
           {
                if( delay_Time > 0 )
                {
                     step_Lev = 2;  //jump to delay time 
                }
                else
                {
                     if( run_Index == total_Cmd )
                     {
                         vUser_diningTable_Reset();
                         return CTRL_OK;
                     }
                     else
                     {
                         step_Lev = 0;
                     } 
                }
           }
           else if( e_res == CTRL_FAIL )
           {
               vUser_diningTable_Reset();
               return CTRL_FAIL;
           }
      }       
      break;

     case 2:
       if( b_run1000Flag )
       {
             b_run1000Flag = false;
             if( delay_Time > 0 )
             {
                 delay_Time--;
                 return CTRL_IDLE;
             }
             if( run_Index == total_Cmd )
             {
                 vUser_diningTable_Reset();
                 return CTRL_OK;
             }
             else
             {
                 step_Lev = 0;
              }
       }     
       break;
    }

    return CTRL_IDLE;
}

static void vUser_diningTable_Set( uint8_t id, uint8_t dir )
{
    ctrlDir = dir;
    yunID = id;
    step_Lev = 0;
    delay_Time = 0;
    run_Index = 0;
    cnt_Second = 0;
    total_Cmd = 0;
}

static void vUser_diningTable_Reset( void )
{
    run_Index = 0;
    step_Lev = 0;
    b_run1000Flag = 0;
    cnt_Second = 0;
    total_Cmd = 0;
}

/* End of this file */

