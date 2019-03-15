/**
  ******************************************************************************
  * @file    Src/user/Ctrl_JDQ.c
  * @author  mingfei tang
  * @version V1.0.0
  * @date    2018/05/09
  * @brief   JDQ ctrl interface by modbus 
  * @documents 
  ******************************************************************************
  */
/* Includes -------------------------------------------------------------------*/
#include "ctrl_Def.h"
#include "ctrl_jdq.h"
#include "Util.h"

/* Private typedef ------------------------------------------------------------*/
/* Private define -------------------------------------------------------------*/
#define RETRY                                     3

/* Private macro --------------------------------------------------------------*/
/* Private variables ----------------------------------------------------------*/
/* Private function prototypes ------------------------------------------------*/
static void vModBus_CtrolJDQ( CtrlJDQ_typedef *pJDQ_typedef, uint8_t status);
static bool bModBus_ParserJDQPacket( CtrlJDQ_typedef *pJDQ_typedef );
static CTRL_RESULT_ENUM eJDQ_SendCmd_Action( CtrlJDQ_typedef *pJDQ_typedef, uint8_t status);
static CTRL_RESULT_ENUM eJDQ_OnOffDevice( CtrlJDQ_typedef *pJDQ_typedef, 
                                          uint8_t status,  bool stopEnable );

CTRL_RESULT_ENUM eJDQ_CtrlInterface(  CtrlJDQ_typedef *pJDQ_typedef )
{
    CtrL_typedef *pCtrL_typedef = pJDQ_typedef->pCtrL_typedef;
    bool stopEnable = false;
    CTRL_RESULT_ENUM res;
    uint8_t status;

    if( pCtrL_typedef->b_ctrlres[0] == JDQ_UP )
    {
        status = JDQ_H;
    }
    else if( pCtrL_typedef->b_ctrlres[0] == JDQ_DOWN )
    {
        status = JDQ_L;
    }
    else
    {
        status = JDQ_L;
        stopEnable = true;
    }

    res = eJDQ_OnOffDevice( pJDQ_typedef, status, stopEnable);

    return res;
}

void vJDQ_ContrlReset( CtrlJDQ_typedef *pJDQ_typedef  )
{
    CtrL_typedef *pCtrL_typedef = pJDQ_typedef->pCtrL_typedef;
    
    pCtrL_typedef->step = 0;
    pCtrL_typedef->retry = 0;  
    pCtrL_typedef->addres = NULL_ADDR;
}

static void vModBus_CtrolJDQ( CtrlJDQ_typedef *pJDQ_typedef, uint8_t status)
{
    CtrL_typedef *pCtrL_typedef;
    uint8_t Cmd[8] = {0x01,  0x05,  0,  0,  0,  0,  0,  0};
    uint8_t pkt_len;
    uint16_t crc;

    pCtrL_typedef = pJDQ_typedef->pCtrL_typedef;
    pkt_len = sizeof( Cmd );
    Cmd[0] = pCtrL_typedef->addres;       //485 address 
    
    Cmd[3] = pCtrL_typedef->deviceID;     //Contrl channel
    Cmd[4] = status;
    
    //calcrute crc16
    crc = UTL_ChkCrc16( Cmd, 6);
    //refres CRC16
    Cmd[6] = ((crc >> 8)&0xff);
    Cmd[7] = crc&0xff; 

    pJDQ_typedef->pf_SendPut( Cmd, pkt_len);
}

static bool bModBus_ParserJDQPacket( CtrlJDQ_typedef *pJDQ_typedef )
{
    CtrL_typedef *pCtrL_typedef;
    uint8_t res = 0;
    uint16_t crc, calCrc;

    pCtrL_typedef = pJDQ_typedef->pCtrL_typedef;
    if( *pJDQ_typedef->length >= 8 )
    {
        *pJDQ_typedef->length = 0;
        //Check crc
        calCrc = pJDQ_typedef->datapacket[6]<<8|pJDQ_typedef->datapacket[7];
        crc = UTL_ChkCrc16( pJDQ_typedef->datapacket, 6);
        if( calCrc == crc )
        {
            if( pCtrL_typedef->b_ctrlres[0] == JDQ_UP )
            {
               res = JDQ_H;
            }
            
            if( res == pJDQ_typedef->datapacket[4] )
              return true;
            else
              return false;
        }
    }
    
    return false;
}

static CTRL_RESULT_ENUM eJDQ_SendCmd_Action( CtrlJDQ_typedef *pJDQ_typedef, uint8_t status)
{
    CtrL_typedef *pCtrL_typedef;
    
    pCtrL_typedef = pJDQ_typedef->pCtrL_typedef;
    if( bModBus_ParserJDQPacket( pJDQ_typedef ))
    {
        pCtrL_typedef->retry = 0;
        return CTRL_OK;
    }
    else
    {
        if( pCtrL_typedef->retry > RETRY)
        {
             pCtrL_typedef->retry = 0;
            return CTRL_FAIL;
        }
        vModBus_CtrolJDQ( pJDQ_typedef, status);
        pCtrL_typedef->retry++;
    }
      
    return CTRL_IDLE;
}

static CTRL_RESULT_ENUM eJDQ_OnOffDevice( CtrlJDQ_typedef *pJDQ_typedef, 
                                          uint8_t status, bool stopEnable )
{
    CtrL_typedef *pCtrL_typedef;
    uint8_t otherStatus;
    CTRL_RESULT_ENUM result = CTRL_IDLE;
    CTRL_RESULT_ENUM res = CTRL_IDLE;

    pCtrL_typedef = pJDQ_typedef->pCtrL_typedef;
    switch( pCtrL_typedef->step )
    {
        case 0:
         if(stopEnable)
             status = JDQ_L;
           
         res = eJDQ_SendCmd_Action( pJDQ_typedef, status);
         if( res == CTRL_OK)
         {
             pCtrL_typedef->step = 1;
             pCtrL_typedef->deviceID += 1;
         }
         else if( res == CTRL_FAIL )
         {
             result = CTRL_FAIL;
         }
         break;

        case 1:
         if( status == JDQ_L && (!stopEnable))
            otherStatus = JDQ_H;
         else
            otherStatus = JDQ_L;
         
         res = eJDQ_SendCmd_Action( pJDQ_typedef, otherStatus );
         if( res == CTRL_OK)
         {
            pCtrL_typedef->step = 0;
            result = CTRL_OK;
         }
         else if( res == CTRL_FAIL )
         {
            result = CTRL_FAIL;
         }
         break;
    }

    return result;
}



/* End of this file */
