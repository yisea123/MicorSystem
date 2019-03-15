/**
  ******************************************************************************
  * @file    Src/user/Ctrl_ModbusInterface.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @brief   485 ctrl interface for modbus 
  * @documents <<order2.pdf>>
  ******************************************************************************
  */
/* Includes -------------------------------------------------------------------*/
#include "platform_def.h"
#include "Ctrl_Motor.h"
#include "util.h"

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t leftstep = 0;
static uint8_t actionStep = 0xff;

static int runCount = 0;
static int motorNum = 0;


static MotorStatus_typedef st_Motor1Status;
static MotorStatus_typedef st_Motor2Status;
static MotorStatus_typedef st_Motor3Status;
static MotorStatus_typedef st_Motor4Status;
static MotorStatus_typedef st_MotorTVStatus;

/* Private function prototypes -----------------------------------------------*/
static bool bMotor_ParserReadSpeed( uint8_t *tarbuff, MotorModBus_typeDef *pCtr_Motor);
static bool bMotor_ParserReadSpeedCmd( CtrlMotor_typedef *pCtrlMotor, MotorModBus_typeDef *pCtr_Modbus);
static bool bMotor_RunAction(CtrlMotor_typedef *pCtrlMotor, int dir  );
static bool bMotor_ParserWriteCmd( uint8_t *tarbuff, MotorModBus_typeDef *pCtr_Motor );
static bool bMotor_ParserWriteSpeedCmd( CtrlMotor_typedef *pCtrlMotor, MotorModBus_typeDef *pCtr_Modbus);

static void vMotor_GetSpeed( uint8_t addr ,  uint16_t speed );
static void vMotor_ResetStatus( MotorStatus_typedef *pMotorStatus_typedef );

static CTRL_RESULT_ENUM eMotor_CheckWriteSpeed( CtrlMotor_typedef *pCtrlMotor );
static CTRL_RESULT_ENUM eMotor_CheckReadSpeed( CtrlMotor_typedef *pCtrlMotor );

static bool bMotor_RunTVAction( CtrlMotor_typedef *pCtrlMotor, int dir  );

static CTRL_RESULT_ENUM eMotor_CheckWriteTVSpeed( CtrlMotor_typedef *pCtrlMotor );
static CTRL_RESULT_ENUM vMotor_CheckTVSpeed( CtrlMotor_typedef *pCtrlMotor );
static CTRL_RESULT_ENUM vMotor_CheckTVError( CtrlMotor_typedef *pCtrlMotor );


/* Private functions implements -----------------------------------------------*/
static void vMotor_ResetStatus( MotorStatus_typedef *pMotorStatus_typedef )
{
    pMotorStatus_typedef->speed = 0;
}

static void vMotor_GetSpeed( uint8_t addr ,  uint16_t speed )
{
    switch( addr )
    {
        case 1:
          st_Motor1Status.speed = speed;
          break;
        case 2:
           st_Motor2Status.speed = speed;
          break;
        case 3:
           st_Motor3Status.speed = speed;
          break;
        case 4:
           st_Motor4Status.speed = speed;
          break;
        case 5:
          st_MotorTVStatus.speed = speed;
          break;
    }
}

static bool bMotor_RunAction( CtrlMotor_typedef *pCtrlMotor, int dir  )
{
    int speed;

    speed = iMotor_SpeedValue( dir );    
    vMotor_WriteSpeedCmd(pCtrlMotor, leftstep++, speed);
    if( leftstep > 4 )
    {
        leftstep = 1;
        return true;
    }

    return false;
}

static bool bMotor_ParserReadSpeed( uint8_t *tarbuff, MotorModBus_typeDef *pCtr_Motor)
{
    uint16_t crc, calCrc;
    
    //Check crc
    calCrc = tarbuff[26]<<8|tarbuff[25];
    crc = CRC16( tarbuff, 25);
    
    if( calCrc == crc )
    {
        pCtr_Motor->addres = tarbuff[0];
        pCtr_Motor->cmd = tarbuff[1];
        pCtr_Motor->elecValue = tarbuff[26]<<8|tarbuff[25];
        pCtr_Motor->speed = tarbuff[7]<<8|tarbuff[8];
        vMotor_GetSpeed( pCtr_Motor->addres, pCtr_Motor->speed);
        return true;
    }
    
    return false;
}

static bool bMotor_ParserReadSpeedCmd( CtrlMotor_typedef *pCtrlMotor,
                                        MotorModBus_typeDef *pCtr_Modbus)
{
    bool res = false;
    
    if( *pCtrlMotor->length >= 9 )
    {
        res = bMotor_ParserReadSpeed( pCtrlMotor->datapacket, pCtr_Modbus );
    }
    *pCtrlMotor->length = 0;

    return res;
}

static bool bMotor_ParserWriteCmd( uint8_t *tarbuff, MotorModBus_typeDef *pCtr_Motor )
{
    uint16_t crc, calCrc;

    //Check crc
    calCrc = tarbuff[7]<<8|tarbuff[6];
    crc = CRC16( tarbuff, 6);

    if( calCrc == crc )
    {
       pCtr_Motor->addres = tarbuff[0];
       pCtr_Motor->cmd = tarbuff[1];
       pCtr_Motor->speed = tarbuff[5]<<8|tarbuff[4];
       vMotor_GetSpeed( pCtr_Motor->addres, pCtr_Motor->speed);
       return true;
    }

    return false;
}

static bool bMotor_ParserWriteSpeedCmd( CtrlMotor_typedef *pCtrlMotor,
                                        MotorModBus_typeDef *pCtr_Modbus)
{
    bool res = false;
    
    if( *pCtrlMotor->length >= 8 )
    {
        res = bMotor_ParserWriteCmd( pCtrlMotor->datapacket, pCtr_Modbus );
    }
    *pCtrlMotor->length = 0;

    return res;
}

CTRL_RESULT_ENUM eMotor_CheckError( CtrlMotor_typedef *pCtrlMotor )
{
    MotorModBus_typeDef st_CtrModbus;
    bool res = false;

    switch( motorNum )
    {
       default:
        case 0:
          res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 1 )
              {
                  motorNum = 1;
                  st_Motor1Status.SendCmdCnt = 0;
                  st_Motor1Status.Onlive = true;
                  vMotor_ReadSpeedCmd( pCtrlMotor, 2);
              }
          }
          else
          {
              vMotor_ReadSpeedCmd( pCtrlMotor, 1);
              st_Motor1Status.SendCmdCnt++;
              if( st_Motor1Status.SendCmdCnt > MOTOR_RUNWRITE )
              {
                  st_Motor1Status.SendCmdCnt = 0;
                  st_Motor1Status.Onlive = false;
                  motorNum = 1;
              }
          }
        break;

        case 1:
          res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 2)
              {
                  motorNum = 2;
                  st_Motor2Status.SendCmdCnt  = 0;
                  st_Motor2Status.Onlive = true;
                  vMotor_ReadSpeedCmd( pCtrlMotor, 3);
              }
          }
          else
          {
              vMotor_ReadSpeedCmd( pCtrlMotor, 2);
              st_Motor2Status.SendCmdCnt++;
              if( st_Motor2Status.SendCmdCnt > MOTOR_RUNWRITE )
              {
                  st_Motor2Status.SendCmdCnt  = 0;
                  st_Motor2Status.Onlive = false;
                  motorNum = 2;
              }
          }
        break;

     case 2:
        res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
        if(res)
        {
            //check address
            if( st_CtrModbus.addres == 3)
            {
                motorNum = 3;
                st_Motor3Status.SendCmdCnt =0;
                st_Motor3Status.Onlive = true;
                vMotor_ReadSpeedCmd( pCtrlMotor, 4);
            }
        }
        else
        {
            vMotor_ReadSpeedCmd( pCtrlMotor, 3);
            st_Motor3Status.SendCmdCnt++;
            if( st_Motor3Status.SendCmdCnt > MOTOR_RUNWRITE )
            {
                st_Motor3Status.SendCmdCnt =0;
                st_Motor3Status.Onlive = false;
                motorNum = 3;
            }
        }
    break;
    
    case 3:
      res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
      if(res)
      {
          //check address
          if( st_CtrModbus.addres == 4)
          {
              motorNum = 0;
              st_Motor4Status.SendCmdCnt =0;
              st_Motor4Status.Onlive = true;
              return CTRL_OK;
          }
      }
      else
      {
          vMotor_ReadSpeedCmd( pCtrlMotor, 4);
          st_Motor4Status.SendCmdCnt++;
          if( st_Motor4Status.SendCmdCnt > MOTOR_RUNWRITE )
          {
              st_Motor4Status.SendCmdCnt =0;
              st_Motor4Status.Onlive = false;
              motorNum = 0;
              return CTRL_OK;
          }
      }
      break;
   }

   return CTRL_IDLE;
}

void vMotor_CtrlReset( void )
{
    leftstep = 1;
    motorNum = 0;
    actionStep = 0;
    runCount = 0;
    
    vMotor_ResetStatus( &st_Motor1Status );
    vMotor_ResetStatus( &st_Motor2Status );
    vMotor_ResetStatus( &st_Motor3Status );
    vMotor_ResetStatus( &st_Motor4Status );
    vMotor_ResetStatus( &st_MotorTVStatus );
}

#if 0
void vMotor_CtrInterface( CtrlMotor_typedef *pCtrlMotor )
{
    CtrL_typedef *pCtrL_typedef = pCtrlMotor->pCtrL_typedef;
    bool res;

    switch( Motor_RunStep )
    {
       default:
        case 0:
            //Check motor error
            if( vMotor_CheckError( pCtrlMotor ) == CTRL_OK )
            {
                 if( st_Motor1Status.Onlive == false || st_Motor2Status.Onlive == false ||
                     st_Motor3Status.Onlive == false || st_Motor4Status.Onlive == false )
                 {
                      pCtrL_typedef->addres = NULL_ADDR;
                      vMotor_CtrlReset();
                      return;
                  }
                  Motor_RunStep = 1;
            }
        break;
        case 1:
        res = bMotor_RunAction(pCtrlMotor, pCtrL_typedef -> b_ctrlres[0] );
        if( res )
        {
            runCount++;
            if( runCount > MOTOR_RUNWRITE )
            {
                  pCtrL_typedef->addres = NULL_ADDR;
                  runCount =0;
                  vMotor_CtrlReset();
            }
        }
        break;
     }
}

#else

static CTRL_RESULT_ENUM eMotor_CheckWriteSpeed( CtrlMotor_typedef *pCtrlMotor )
{
    CtrL_typedef *pCtrL_typedef = pCtrlMotor->pCtrL_typedef;
    MotorModBus_typeDef st_CtrModbus;
    bool res = false;

    switch( motorNum )
    {
       default:
        case 0:
          res = bMotor_ParserWriteSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 1 )
              {
                  motorNum = 1;
                  st_Motor1Status.Onlive = true;
                  st_Motor1Status.SendCmdCnt  = 0;
                  st_Motor1Status.speed = st_CtrModbus.speed;
                  vMotor_WriteSpeed( pCtrlMotor, MOTOR_2, pCtrL_typedef -> b_ctrlres[0]);
              }
          }
          else
          {
              vMotor_WriteSpeed( pCtrlMotor, MOTOR_1, pCtrL_typedef -> b_ctrlres[0]);
              st_Motor1Status.SendCmdCnt++;
              if( st_Motor1Status.SendCmdCnt > MOTOR_RUNWRITE )
              {
                  st_Motor1Status.SendCmdCnt  = 0;
                  st_Motor1Status.Onlive = false;
                  return CTRL_FAIL;
              }
          }         
         break;
         
         case 1:
          res = bMotor_ParserWriteSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 2 )
              {
                  motorNum = 2;
                  st_Motor2Status.Onlive = true;
                  st_Motor2Status.SendCmdCnt  = 0;
                  st_Motor2Status.speed = st_CtrModbus.speed;
                  vMotor_WriteSpeed( pCtrlMotor, MOTOR_3, pCtrL_typedef -> b_ctrlres[0]);
              }
          }
          else
          {
              vMotor_WriteSpeed( pCtrlMotor, MOTOR_2, pCtrL_typedef -> b_ctrlres[0]);
              st_Motor2Status.SendCmdCnt++;
              if( st_Motor2Status.SendCmdCnt > MOTOR_RUNWRITE )
              {
                  st_Motor2Status.SendCmdCnt  = 0;
                  st_Motor2Status.Onlive = false;
                  return CTRL_FAIL;
              }
          }         
         break;
 
         case 2:
          res = bMotor_ParserWriteSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 3 )
              {
                  motorNum = 3;
                  st_Motor3Status.Onlive = true;
                  st_Motor3Status.SendCmdCnt  = 0;
                  st_Motor3Status.speed = st_CtrModbus.speed;
                  vMotor_WriteSpeed( pCtrlMotor, MOTOR_4, pCtrL_typedef -> b_ctrlres[0]);
              }
          }
          else
          {
              vMotor_WriteSpeed( pCtrlMotor, MOTOR_4, pCtrL_typedef -> b_ctrlres[0]);
              st_Motor3Status.SendCmdCnt++;
              if( st_Motor3Status.SendCmdCnt > MOTOR_RUNWRITE )
              {
                  st_Motor3Status.SendCmdCnt  = 0;
                  st_Motor3Status.Onlive = false;
                  return CTRL_FAIL;
              }
          }         
         break;
         
         case 3:
          res = bMotor_ParserWriteSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 4 )
              {
                  motorNum = 0;
                  st_Motor4Status.Onlive = true;
                  st_Motor4Status.SendCmdCnt  = 0;
                  st_Motor4Status.speed = st_CtrModbus.speed;
                  return CTRL_OK;
              }
          }
          else
          {
              vMotor_WriteSpeed( pCtrlMotor, MOTOR_4, pCtrL_typedef -> b_ctrlres[0]);
              st_Motor4Status.SendCmdCnt++;
              if( st_Motor4Status.SendCmdCnt > MOTOR_RUNWRITE )
              {
                  st_Motor4Status.SendCmdCnt  = 0;
                  st_Motor4Status.Onlive = false;
                  return CTRL_FAIL;
              }
          }         
         break;
    }
    
    return CTRL_IDLE;
}


static CTRL_RESULT_ENUM eMotor_CheckReadSpeed( CtrlMotor_typedef *pCtrlMotor )
{
    MotorModBus_typeDef st_CtrModbus;
    bool res = false;

    switch( motorNum )
    {
       default:
        case 0:
          res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 1 )
              {
                  motorNum = 1;
                  st_Motor1Status.Onlive = true;
                  st_Motor1Status.SendCmdCnt  = 0;
                  st_Motor1Status.speed = st_CtrModbus.speed;
                  vMotor_ReadSpeedCmd( pCtrlMotor, 2);
              }
          }
          else
          {
              vMotor_ReadSpeedCmd( pCtrlMotor, 1);
              st_Motor1Status.SendCmdCnt++;
              if( st_Motor1Status.SendCmdCnt > MOTOR_RUNWRITE )
              {
                  st_Motor1Status.SendCmdCnt  = 0;
                  st_Motor1Status.Onlive = false;
                  return CTRL_FAIL;
              }
          }
        break;

        case 1:
          res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
          if(res)
          {
              //check address
              if( st_CtrModbus.addres == 2)
              {
                  motorNum = 2;
                  st_Motor2Status.Onlive = true;
                  st_Motor2Status.SendCmdCnt = 0;
                  st_Motor2Status.speed = st_CtrModbus.speed;
                  vMotor_ReadSpeedCmd( pCtrlMotor, 3);
              }
          }
          else
          {
              vMotor_ReadSpeedCmd( pCtrlMotor, 2);
              st_Motor2Status.SendCmdCnt++;
              if( st_Motor2Status.SendCmdCnt > MOTOR_RUNWRITE )
              { 
                  st_Motor2Status.SendCmdCnt = 0;
                  st_Motor2Status.Onlive = false;
                  return CTRL_FAIL;
              }
          }
        break;

     case 2:
        res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
        if(res)
        {
            //check address
            if( st_CtrModbus.addres == 3)
            {
                motorNum = 3;
                st_Motor3Status.Onlive = true;
                st_Motor3Status.SendCmdCnt = 0;
                st_Motor3Status.speed = st_CtrModbus.speed;
                vMotor_ReadSpeedCmd( pCtrlMotor, 4);
            }
        }
        else
        {
            vMotor_ReadSpeedCmd( pCtrlMotor, 3);
            st_Motor3Status.SendCmdCnt++;
            if( st_Motor3Status.SendCmdCnt > MOTOR_RUNWRITE )
            {
                st_Motor3Status.SendCmdCnt = 0;
                st_Motor3Status.Onlive = false;
                return CTRL_FAIL;
            }
        }
    break;
    
    case 3:
      res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
      if(res)
      {
          //check address
          if( st_CtrModbus.addres == 4)
          {
              motorNum = 0;
              st_Motor4Status.SendCmdCnt = 0;
              st_Motor4Status.Onlive = true;
              st_Motor4Status.speed = st_CtrModbus.speed;
              return CTRL_OK;
          }
      }
      else
      {
          vMotor_ReadSpeedCmd( pCtrlMotor, 4);
          st_Motor4Status.SendCmdCnt++;
          if( st_Motor4Status.SendCmdCnt > MOTOR_RUNWRITE )
          {
              st_Motor4Status.SendCmdCnt = 0;
              st_Motor4Status.Onlive = false;
              return CTRL_FAIL;
          }
      }
      break;
   }

   return CTRL_IDLE;
}

void vMotor_CtrInterface( CtrlMotor_typedef *pCtrlMotor )
{
    CTRL_RESULT_ENUM e_Res = CTRL_IDLE;
    CtrL_typedef *pCtrL_typedef = pCtrlMotor->pCtrL_typedef;
    bool res;

    switch( actionStep )
    {
       default:
        case 0:              //Check motor error
          if( eMotor_CheckError( pCtrlMotor ) == CTRL_OK )
          {
               if( st_Motor1Status.Onlive == false || st_Motor2Status.Onlive == false ||
                   st_Motor3Status.Onlive == false || st_Motor4Status.Onlive == false )
               {
                    vMotor_CtrlReset();
                    pCtrL_typedef->addres = NULL_ADDR;
                    return;
                }
                actionStep = 1;
          }
        break;

        case 1:             //write speed 
          e_Res = eMotor_CheckWriteSpeed( pCtrlMotor );
          if( e_Res == CTRL_OK )
          {
              vMotor_CtrlReset();
              actionStep = 2;    /* read the speed of motor */
          }
          if( e_Res ==  CTRL_FAIL)
          {
              vMotor_CtrlReset();
              actionStep = 3;    /* send stop the motor command */
          }
        break;

        case 2:             //read speed
          e_Res = eMotor_CheckReadSpeed( pCtrlMotor );
          if( e_Res ==  CTRL_FAIL)
          {
              vMotor_CtrlReset();
              actionStep = 3;
          }
          else
          {    
              if( e_Res ==  CTRL_OK )
              {
                  /* Check the speed, if speed = 0; stop to send command */
                  if( st_Motor1Status.speed == 0 && st_Motor2Status.speed  == 0 &&
                      st_Motor3Status.speed == 0 && st_Motor4Status.speed  == 0)
                  {
                      vMotor_CtrlReset();
                      actionStep = 3;
                  }
              }
          }
        break;
          
        case 3:      //Stop run
          res = bMotor_RunAction(pCtrlMotor, CTRL_STOP );
          if( res )
          {
              runCount++;
              if( runCount > MOTOR_RUNWRITE )
              {
                    vMotor_CtrlReset();
                    pCtrL_typedef->addres = NULL_ADDR;
              }
          }        
        break;
    }
}
#endif

void vMotor_GetStatus( AllMotorStatus_typedef *pAllMotorStatus)
{
    pAllMotorStatus->st_Motor1Status = st_Motor1Status;
    pAllMotorStatus->st_Motor2Status = st_Motor2Status;
    pAllMotorStatus->st_Motor3Status = st_Motor3Status;
    pAllMotorStatus->st_Motor4Status = st_Motor4Status;
}

/*
*******************************************************************************
        for TV control 
*******************************************************************************
*/
static bool bMotor_RunTVAction( CtrlMotor_typedef *pCtrlMotor, int dir  )
{
    int speed;

    switch( dir )
    {
        case STATUS_DOWN:
        speed = -MOTOR_SPEED;    //Down
        break;
        
        case STATUS_UP:
        speed = MOTOR_SPEED;     //Up
        break;
        
        case CTRL_STOP:
        speed = 0;              //Stop
        break;
        
        default:
        return true;            //IDLE state
    }
    vMotor_WriteSpeedCmd(pCtrlMotor, MOROT_TV_ADD, speed);
    
    return true;
}

static CTRL_RESULT_ENUM eMotor_CheckWriteTVSpeed( CtrlMotor_typedef *pCtrlMotor )
{
    CtrL_typedef *pCtrL_typedef = pCtrlMotor->pCtrL_typedef;
    MotorModBus_typeDef st_CtrModbus;
    bool res = false;

    res = bMotor_ParserWriteSpeedCmd( pCtrlMotor, &st_CtrModbus );
    if(res)
    {
        //check address
        if( st_CtrModbus.addres == MOROT_TV_ADD )
        {
            st_MotorTVStatus.Onlive = true;
            st_MotorTVStatus.SendCmdCnt = 0;
            st_MotorTVStatus.speed = st_CtrModbus.speed;
            return CTRL_OK;
        }
    }
    else
    {
        vMotor_WriteSpeed( pCtrlMotor, MOROT_TV_ADD, pCtrL_typedef -> b_ctrlres[0]);
        st_MotorTVStatus.SendCmdCnt++;
        if( st_MotorTVStatus.SendCmdCnt > MOTOR_RUNWRITE )
        {
            st_MotorTVStatus.SendCmdCnt = 0;
            st_MotorTVStatus.Onlive = false;
            return CTRL_FAIL;
        }
    }         
          
    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM vMotor_CheckTVError( CtrlMotor_typedef *pCtrlMotor )
{
    MotorModBus_typeDef st_CtrModbus;
    bool res = false;

    res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
    if(res)
    {
        //check address
        if( st_CtrModbus.addres == MOROT_TV_ADD )
        {
            st_MotorTVStatus.Onlive = true;
            st_MotorTVStatus.SendCmdCnt = 0;
            return CTRL_OK;
        }
    }
    else
    {
        vMotor_ReadSpeedCmd( pCtrlMotor, MOROT_TV_ADD);
        st_MotorTVStatus.SendCmdCnt++;
        if( st_MotorTVStatus.SendCmdCnt > MOTOR_RUNWRITE )
        {
            st_MotorTVStatus.Onlive = false;
            st_MotorTVStatus.SendCmdCnt = 0;
            return CTRL_FAIL;
        }
    }
          
    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM vMotor_CheckTVSpeed( CtrlMotor_typedef *pCtrlMotor )
{
    MotorModBus_typeDef st_CtrModbus;
    bool res = false;

    res = bMotor_ParserReadSpeedCmd( pCtrlMotor, &st_CtrModbus );
    if(res)
    {
        //check address
        if( st_CtrModbus.addres == MOROT_TV_ADD )
        {
            st_MotorTVStatus.Onlive = true;
            st_MotorTVStatus.SendCmdCnt  = 0;
            return CTRL_OK;
        }
    }
    else
    {
        vMotor_ReadSpeedCmd( pCtrlMotor, MOROT_TV_ADD);
        st_MotorTVStatus.SendCmdCnt++;
        if( st_MotorTVStatus.SendCmdCnt > MOTOR_RUNWRITE )
        {
            st_MotorTVStatus.SendCmdCnt  = 0;
            st_MotorTVStatus.Onlive = false;
            return CTRL_FAIL;
        }
    }

    return CTRL_IDLE;
}

void vMotor_CtrInterfaceTV( CtrlMotor_typedef *pCtrlMotor )
{
    CTRL_RESULT_ENUM e_Res = CTRL_IDLE;
    CtrL_typedef *pCtrL_typedef = pCtrlMotor->pCtrL_typedef;
    bool res;

    switch( actionStep )
    {
       default:
        case 0:              //Check motor error
          if( vMotor_CheckTVError( pCtrlMotor ) == CTRL_OK )
          {
               if( st_MotorTVStatus.Onlive == false )
               {
                    pCtrL_typedef->addres = NULL_ADDR;
                    vMotor_CtrlReset();
                    return;
                }
                actionStep = 1;
          }
        break;

        case 1:             //write speed        
          e_Res = eMotor_CheckWriteTVSpeed( pCtrlMotor );
          if( e_Res == CTRL_OK )
          {   
              vMotor_CtrlReset();
              actionStep = 2;    /* read the speed of motor */
          }
          if( e_Res ==  CTRL_FAIL)
          {
              vMotor_CtrlReset();
              actionStep = 3;    /* send stop the motor command */
          }          
          
        break;

        case 2:      //read speed
          runCount++;              
          if( runCount < DELAY_TIME )
            return;
          
          runCount = DELAY_TIME;
          e_Res = vMotor_CheckTVSpeed( pCtrlMotor );
          if( e_Res ==  CTRL_FAIL)
          {
              vMotor_CtrlReset();
              actionStep = 3;
          }
          else
          {
              if( e_Res ==  CTRL_OK )
              {
                  /* Check the speed, if speed = 0; stop to send command */
                  if( st_MotorTVStatus.speed == 0 )
                  {
                      vMotor_CtrlReset();
                      actionStep = 3;
                  }
              }          
          }
        break;
          
        case 3:      //Stop run
          res = bMotor_RunTVAction(pCtrlMotor, CTRL_STOP );
          if( res )
          {
              runCount++;
              if( runCount > MOTOR_RUNWRITE )
              {
                    vMotor_CtrlReset();
                    pCtrL_typedef->addres = NULL_ADDR;
                    runCount =0;
              }
          }        
        break;
    }
}

/* End of this file */

