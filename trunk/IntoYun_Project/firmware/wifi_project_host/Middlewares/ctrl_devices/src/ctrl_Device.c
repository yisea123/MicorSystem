/**
  ******************************************************************************
  * @file    Src/user/Ctrl_Device.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/01/25
  * @brief   485 ctrl interface for modbus 
  * @documents 
  ***********************i*******************************************************
  */
/* Includes --------------------------------------------------------------------*/
#include "ctrl_Def.h"
#include "ctrl_device.h"
#include "Util.h"
 
/* Private typedef -------------------------------------------------------------*/
/* Private define --------------------------------------------------------------*/
#define  JDRETRY                                   3                                       

/* Private macro ---------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------*/
static bool Device_ParserDataPacket( uint8_t *tarbuff, Ctr_Modbus_TypeDef *pCtr_Modbus);

void Device_Send( CtrlJDev_typedef *pCtrlDev ) 
{
    CtrL_typedef *pCtrlTypdef;

    uint8_t Cmd[9] = {0x01,  0x05,  0,  0,  0,  0,  0,  0, 0};
    uint8_t pkt_len;
    uint16_t crc;

    pCtrlTypdef = pCtrlDev->pCtrL_typedef;
    pkt_len = sizeof( Cmd );
    Cmd[0] = pCtrlTypdef->addres;

    Cmd[4] = pCtrlTypdef->dev_type;
    //value
    Cmd[5] = pCtrlTypdef->b_ctrlres[0];

    //calcrate crc16
    crc = UTL_ChkCrc16( Cmd, 6);

    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 
    pCtrlDev->pf_SendPut( Cmd, pkt_len);
}

static bool Device_ParserDataPacket( uint8_t *tarbuff, Ctr_Modbus_TypeDef *pCtr_Modbus)
{
    uint16_t crc, calCrc;

    //Check crc
    calCrc = tarbuff[6]<<8|tarbuff[7];
    crc = UTL_ChkCrc16( tarbuff, 6);
    if( calCrc == crc )
    {
        pCtr_Modbus->addres = tarbuff[0];
        pCtr_Modbus->type = tarbuff[4];
        pCtr_Modbus->cmd = tarbuff[5];

        return true;
    }

    return false;
}

CTRL_RESULT_ENUM Device_ActionProcess( CtrlJDev_typedef *pCtrlDev )
{
    bool res = false;
    Ctr_Modbus_TypeDef st_Ctr_Modbus;
    CtrL_typedef *pCtrlTypdef;
     
    pCtrlTypdef = pCtrlDev->pCtrL_typedef;
    if( *pCtrlDev->length >= 8 )
    {
        *pCtrlDev->length = 0; 
        res = Device_ParserDataPacket( pCtrlDev->datapacket, &st_Ctr_Modbus );
        if( res == true )
        {
            if(st_Ctr_Modbus.addres == pCtrlTypdef->addres &&
               st_Ctr_Modbus.type == pCtrlTypdef->dev_type)
            {
                pCtrlDev->retry = 0;
                return CTRL_OK;
            }
        } 
    }
    else
    {
        if( pCtrlTypdef->retry > JDRETRY)
        {
            pCtrlDev->retry = 0;
            return CTRL_FAIL;
        }
        
        pCtrlDev->retry++;
        Device_Send( pCtrlDev );
    }

    return CTRL_IDLE;
}

/* End of this file */