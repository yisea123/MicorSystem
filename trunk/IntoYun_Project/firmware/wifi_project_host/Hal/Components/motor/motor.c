/** \file

$Id: motor.c 40486 2018-08-08 13:50:21Z mingfei.tang2013@126.com $

Copyright (c)mingfei.tang2013@126.com Holding B.V.
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
#include "motor.h"

/*******************************************************************************
* EXPORT INCLUDE FILES
*******************************************************************************/
#include "util.h"
#include "log.h"

/******************************************************************************
* LOCAL MACROS AND DEFINITIONS
******************************************************************************/
#define MOTOR_DEBUGEN           1

#if  MOTOR_DEBUGEN
#define   motor_debug          log_printf       
#else
#define   motor_debug         
#endif

/******************************************************************************
* LOCAL VARIABLES
******************************************************************************/
static char motor_PkgId[] = " motor";

/******************************************************************************
* EXTERN FUNCTION IMPLEMENTS
******************************************************************************/
void vMotor_WriteSpeedCmd( CtrlMotor_typedef *pCtrlMotor, uint8_t addr, int speed )
{
    uint8_t Cmd[] =  { 0x01 ,0x06 ,0x00 ,0x40 ,0x00 ,0xFA ,0x08 ,0x5D};
    uint8_t pkt_len;
    uint16_t crc;

    pkt_len = sizeof( Cmd );
    
    Cmd[0] = addr;      //485 address 
    
    Cmd[4] = speed>>8;  //speed
    Cmd[5] = speed;

    //calcrate crc16
    crc = UTL_ChkCrc16( Cmd, 6);

    //refresh CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 
    
    pCtrlMotor->pf_SendPut( Cmd, pkt_len);   
    motor_debug( motor_PkgId, Cmd, pkt_len);
}

void vMotor_ReadSpeedCmd(CtrlMotor_typedef *pCtrlMotor, uint8_t addr )
{
    uint8_t Cmd[] =  { 0x04 ,0x03 ,0x00 ,0x10 ,0 ,0x0b ,0x94 ,0x5B};
    uint8_t pkt_len;
    uint16_t crc;

    pkt_len = sizeof( Cmd );

    Cmd[0] = addr;     //485 address 
    
    //calcrate crc16
    crc = UTL_ChkCrc16( Cmd, 6);
    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 
    
    pCtrlMotor->pf_SendPut( Cmd, pkt_len);
    motor_debug( motor_PkgId, Cmd, pkt_len);
}

void vMotor_ResetPara( MotorStatus_typedef *pMotorStatus )
{
    pMotorStatus->SendCmdCnt = 0;
    pMotorStatus->speed = 0;
    pMotorStatus->sqr_1 = 0;
    pMotorStatus->sqr_2 = 0;
    pMotorStatus->elecValue = 0;
}

int iMotor_SpeedValue( int dir )
{
    int speed;

    switch( dir )
    {
        case DIR_DOWN:
        speed = -MOTOR_SPEED;    //Down
        break;
        
        case DIR_UP:
        speed = MOTOR_SPEED;     //Up
        break;
        
        default:
        case DIR_STOP:
        speed = 0;              //Stop
        break;
    }
    
    return speed;
}

void vMotor_WriteSpeed(CtrlMotor_typedef *pCtrlMotor,uint8_t address, int dir  )
{
    int speed;
   
    speed = iMotor_SpeedValue( dir );
    vMotor_WriteSpeedCmd(pCtrlMotor, address, speed);
}

bool bMotor_ParserReadSpeedResp( CtrlMotor_typedef *pCtrlMotor )
{
    uint8_t *tarbuff;
    uint16_t crc, calCrc;
    MotorStatus_typedef *pMotorStatus;
    bool res = false;
    
    tarbuff = pCtrlMotor->datapacket;
    pMotorStatus = pCtrlMotor->pMotorStatus;
    if( *pCtrlMotor->length >= 9 )
    {
        //Check crc
        calCrc = tarbuff[26]<<8|tarbuff[25];
        crc = CRC16( tarbuff, 25);
        
        if( calCrc == crc )
        {
            pMotorStatus->addres = tarbuff[0];
            pMotorStatus->cmd = tarbuff[1];
            pMotorStatus->elecValue = tarbuff[5]<<8|tarbuff[6];
            pMotorStatus->speed = tarbuff[7]<<8|tarbuff[8];
            pMotorStatus->sqr_2 = tarbuff[21]<<8|tarbuff[22];
            pMotorStatus->sqr_1 = tarbuff[19]<<8|tarbuff[20];  //down and stop: sq1 = 1, sq2 = 0
            res = true;
            motor_debug( motor_PkgId, tarbuff, *pCtrlMotor->length);
        }
    }
    *pCtrlMotor->length = 0;
   
   return res;
}

bool bMotor_ParserWriteCmdResp( CtrlMotor_typedef *pCtrlMotor)
{
    uint8_t *tarbuff;
    MotorStatus_typedef *pMotorStatus;
    bool res = false;
    uint16_t crc, calCrc;

    tarbuff = pCtrlMotor->datapacket;
    pMotorStatus = pCtrlMotor->pMotorStatus;
    if( *pCtrlMotor->length >= 8 )
    {
        //Check crc
        calCrc = tarbuff[7]<<8|tarbuff[6];
        crc = CRC16( tarbuff, 6);

        if( calCrc == crc )
        {
           pMotorStatus->addres = tarbuff[0];
           pMotorStatus->cmd = tarbuff[1];
           pMotorStatus->speed = tarbuff[5]<<8|tarbuff[4];
           res = true;
           motor_debug( motor_PkgId, tarbuff, *pCtrlMotor->length);
        }
    }
    *pCtrlMotor->length = 0;
    
    return res;
}

/* End of this file */