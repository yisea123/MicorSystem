/**
  ******************************************************************************
  * @file    Src/user/Ctrl_JdSensor.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/15
  * @brief   Jd Sensor ctrl interface 
  * @documents 
  ******************************************************************************
  */
/* Includes -------------------------------------------------------------------*/
#include "ctrl_Def.h"
#include "ctrl_jdSensor.h"
#include "Util.h"

/* Private typedef ------------------------------------------------------------*/
/* Private define -------------------------------------------------------------*/

#define JDRETRY                             5
#define ADDRESS                             3
/* Private macro --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/

/* Private function prototypes ------------------------------------------------*/
static bool JdSensor_ParserPacket(  CtrlJQSensor_typedef *pCtrL_typedef );
static void JdSensor_SendHeaderCmd( CtrlJQSensor_typedef *pCtrL_typedef );
static void JdSensor_ReadValueCmd( CtrlJQSensor_typedef *pCtrL_typedef );

CTRL_RESULT_ENUM JdSensor_ReadValue( CtrlJQSensor_typedef *pCtrL_typedef )
{
    bool b_ReadValueStart = false;
    switch( pCtrL_typedef->step )
    {
        case 0:
            JdSensor_SendHeaderCmd( pCtrL_typedef );
            if( pCtrL_typedef->retry < JDRETRY )
            {
                pCtrL_typedef->retry++;
            }
            else
            {
                pCtrL_typedef->step = 1;
                pCtrL_typedef->retry = 0;
            }
        break;

        case 1:
            b_ReadValueStart = true;
        break;

        default:
        return CTRL_FAIL;
    }
     
    if( b_ReadValueStart )
    {
        b_ReadValueStart = false;
        if( JdSensor_ParserPacket( pCtrL_typedef ))
        {
            pCtrL_typedef->retry = 0;
            pCtrL_typedef->step = 1;
            return CTRL_OK;
        }
        else
        {
            if( pCtrL_typedef->retry > JDRETRY)
            {
                pCtrL_typedef->step = 0xff;
                pCtrL_typedef->retry = 0;
                return CTRL_FAIL;
            }
            
            JdSensor_ReadValueCmd( pCtrL_typedef );
            pCtrL_typedef->retry++;
        }
    }

    return CTRL_IDLE;
}

void vJdSensor_CtrlInterfaceReset( CtrlJQSensor_typedef *pCtrL_typedef )
{
    pCtrL_typedef->step = 0;
    pCtrL_typedef->retry = 0;
    pCtrL_typedef->address = ADDRESS;
}

static void JdSensor_SendHeaderCmd( CtrlJQSensor_typedef *pCtrL_typedef )
{
    uint8_t Cmd[11] = { 0xC0, 0x65, 0x03, 0x04, 0, 0, 0, 0, 0, 0, 0xC0 };

    pCtrL_typedef->pf_SendPut( Cmd, sizeof(Cmd));
}

static void JdSensor_ReadValueCmd( CtrlJQSensor_typedef *pCtrL_typedef )
{
    uint8_t Cmd[8] = { 0x02, 0x03, 0, 0x5D, 0, 0x02, 0x55, 0xEA };
    uint16_t crc;

    Cmd[0] = pCtrL_typedef->address;       //485 address

    //calcrate crc16
    crc = UTL_ChkCrc16( Cmd, 6);
    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 

    pCtrL_typedef->pf_SendPut( Cmd, sizeof(Cmd));
}

static bool JdSensor_ParserPacket(  CtrlJQSensor_typedef *pCtrL_typedef )
{
    uint16_t crc, calCrc;

    if( *pCtrL_typedef->length >= 8 )
    {
        *pCtrL_typedef->length = 0;
        //Check crc
        calCrc = pCtrL_typedef->datapacket[7]<<8|pCtrL_typedef->datapacket[8];
        crc = UTL_ChkCrc16( pCtrL_typedef->datapacket, 7);
        if( calCrc == crc )
        {
          if( pCtrL_typedef->address == pCtrL_typedef->datapacket[0] )
          {
              pCtrL_typedef->x_value =  (int)(pCtrL_typedef->datapacket[3] << 8 | pCtrL_typedef->datapacket[4]);
              pCtrL_typedef->y_value =  (int)(pCtrL_typedef->datapacket[5] << 8 | pCtrL_typedef->datapacket[6]);
              return true;
          }
          else
            return false;
        }
    }

    return false;
}

/* End of this file */

